/*
 * ELCRTSPServer.cpp
 *
 *  Created on: 26 Jul, 2014
 *      Author: cuonglm
 */


#include "elcrtspserver.h"
#include "h264filesource.h"
#include "h264filemediasubsession.h"
#include "mpeg4filemediasubsession.h"
#include "RTSPCommon.hh"
#include <iostream>
#include <sys/stat.h>
#include "commondef.h"
#include "filehandler.h"

extern UsageEnvironment* env;

ELCRTSPServer* ELCRTSPServer::createNew(UsageEnvironment& env, Port ourPort,
	      UserAuthenticationDatabase* authDatabase,
	      unsigned reclamationTestSeconds)
{
	int ourSocket = setUpOurSocket(env, ourPort);
	if (ourSocket == -1) return NULL;

	return new ELCRTSPServer(env, ourSocket, ourPort, authDatabase, reclamationTestSeconds);
}



ELCRTSPServer::ELCRTSPServer(UsageEnvironment& env, int ourSocket, Port ourPort,
						  UserAuthenticationDatabase* authDatabase,
						  unsigned reclamationTestSeconds)
:RTSPServer(env, ourSocket, ourPort, authDatabase, reclamationTestSeconds)
{

}

ELCRTSPServer::~ELCRTSPServer()
{

}


RTSPServer::RTSPClientConnection*  ELCRTSPServer::createNewClientConnection(int clientSocket, struct sockaddr_in clientAddr)
{

	return new NvrRTSPClientConnection(*this, clientSocket, clientAddr);
}


/////////////////////////////////////////////////////////////////////////////
// myrtspserver::NvrRTSPClientConnection class
/////////////////////////////////////////////////////////////////////////////

ELCRTSPServer::NvrRTSPClientConnection::NvrRTSPClientConnection(RTSPServer& ourServer,
		int clientSocket, struct sockaddr_in clientAddr)
:RTSPServer::RTSPClientConnection(ourServer, clientSocket, clientAddr)
{
	LOG_INFO("New NvrRTSPClientConnection socket " << int2string(clientSocket));
}

ELCRTSPServer::NvrRTSPClientConnection::~NvrRTSPClientConnection()
{
}

void ELCRTSPServer::NvrRTSPClientConnection::handleCmd_DESCRIBE(char const* urlPreSuffix,
		char const* urlSuffix, char const* fullRequestStr)
{
	// my process
	LOG_INFO("***REQUEST*** DESCRIBE  urlPreSuffix: "<< std::string(urlPreSuffix) <<"\n urlSuffix: "<<std::string(urlSuffix));

	char* sdpDescription = NULL;
	char* rtspURL = NULL;
	do {
		char urlTotalSuffix[200];
		if (strlen(urlPreSuffix) + strlen(urlSuffix) + 2 > sizeof urlTotalSuffix)
		{
		  handleCmd_bad();
		  break;
		}

		urlTotalSuffix[0] = '\0';

		if (urlPreSuffix[0] != '\0')
		{
		  strcat(urlTotalSuffix, urlPreSuffix);
		  strcat(urlTotalSuffix, "/");
		}

		strcat(urlTotalSuffix, urlSuffix);

		if (!authenticationOK("DESCRIBE", urlTotalSuffix, fullRequestStr))
		{
			LOG_INFO("***RESPOND*** CmdDESCRIBE error authentication ");
			setRTSPResponse("error authentication");
			break;
		}

		//get ID camera
		char* url = new char[200];
		strcpy(url, urlSuffix);
		std::vector<std::string> dataURL = split(url, "?&");

		if(dataURL.size()<3)
		{
			LOG_INFO("***RESPOND*** CmdDESCRIBE url uncorrect format");
			handleCmd_notFound();
			break;
		}
		std::string ip = dataURL[0];
		std::string ts = dataURL[1];
		std::string te = dataURL[2];
		if(ts.length() >18 || te.length() >18)
		{
			LOG_INFO("***RESPOND*** CmdDESCRIBE url uncorrect format");
			handleCmd_notFound();
			break;
		}

		std::string speed = "";
		if(dataURL.size() == 4)
			speed = dataURL[3];

		// comment this block incase of using ID instead of IP
		std::cout<<"speed : "  <<speed<<std::endl;
		std::string cmd = "SELECT id FROM its_cam WHERE ip='" + ip + "';";
		LOG_INFO("query:  "<<cmd);
		std::string ID = DBWoker::getSingleton()->getData(cmd);
		std::cout<<"get ID = "<<ID<<std::endl;
		LOG_INFO("get ID = "<<ID);
		if(ID=="")
		{
			LOG_INFO("***RESPOND*** CmdDESCRIBE Don't exist ID of Ip");
			handleCmd_notFound();
			break;
		}

		//----------------------------------------------
		// string ID = ip; // if using id, uncomment this

		//check storage has contained file
		std::vector<std::string> mListFile;
		int codec;
		mListFile = getFileDirectory(ID, ts, te, codec);
		if(mListFile.size()==0)
		{
			LOG_INFO("***RESPOND*** CmdDESCRIBE: 404 File Not Found, Or In Incorrect Format");
			handleCmd_notFound();
			break;
		}

		if(codec != AV_CODEC_ID_MPEG4 && codec !=AV_CODEC_ID_H264)
		{
			LOG_INFO("***RESPOND*** CmdDESCRIBE: Codec of File don't Correct");
			handleCmd_notSupported();
			break;
		}

		delete[] url;

		//search session
		ServerMediaSession* session = fOurServer.lookupServerMediaSession(urlSuffix);
		if(session==NULL)
		{
			LOG_INFO("Session don't exist, creat new session");
			session = ServerMediaSession::createNew(*env, urlSuffix, urlSuffix, "file.mp4");

			if(codec == AV_CODEC_ID_MPEG4)
			{
				LOG_INFO("Creat MPEG-4 subsession");
				Mpeg4FileMeidaSubSession* mpeg4subsession = Mpeg4FileMeidaSubSession::createNew(*env, mListFile, ts, te, speed, false);
				session->addSubsession(mpeg4subsession);
			}
			else
			{
				LOG_INFO("Creat H264 subsession");
				H264FileMediaSubsession *h264subsession = H264FileMediaSubsession::createNew(*env, mListFile, ts, te, speed, false);
				session->addSubsession(h264subsession);
			}

			fOurServer.addServerMediaSession(session);
		}//end session == NUL


		// Then, assemble a SDP description for this session:
		sdpDescription = session->generateSDPDescription();
		if (sdpDescription == NULL)
		{
			handleCmd_sessionNotFound();
			break;
		}


		unsigned sdpDescriptionSize = strlen(sdpDescription);
		std::cout<<"sdp description "<<sdpDescription<<std::endl;
		LOG_INFO("sdp description: " << sdpDescription);

		// Also, generate our RTSP URL, for the "Content-Base:" header
		// (which is necessary to ensure that the correct URL gets used in subsequent "SETUP" requests).
		//rtspURL = fOurServer.rtspURL(session, fClientInputSocket);
		rtspURL = fOurRTSPServer.rtspURL(session, fClientInputSocket);

		snprintf((char*)fResponseBuffer, sizeof fResponseBuffer,
			 "RTSP/1.0 200 OK\r\nCSeq: %s\r\n"
			 "%s"
			 "Content-Base: %s/\r\n"
			 "Content-Type: application/sdp\r\n"
			 "Content-Length: %d\r\n\r\n"
			 "%s",
			 fCurrentCSeq,
			 dateHeader(),
			 rtspURL,
			 sdpDescriptionSize,
			 sdpDescription);

		LOG_INFO("***RESPOND*** CmdDESCRIBE: \n"<< std::string((char*)fResponseBuffer));

	} while (0);

	delete[] sdpDescription;
	delete[] rtspURL;
}


char* ELCRTSPServer::NvrRTSPClientConnection::getBufferRespond()
{
	return (char*)fResponseBuffer;
}

/////////////////////////////////////////////////////////////////////////////
// myrtspserver::NvrRTSPClientSession class
/////////////////////////////////////////////////////////////////////////////
ELCRTSPServer::NvrRTSPClientSession::NvrRTSPClientSession(RTSPServer& ourServer, u_int32_t sessionId)
:RTSPClientSession(ourServer, sessionId)
{
	LOG_INFO("Creat Client Session ID "<<int2string(sessionId));
}

ELCRTSPServer::NvrRTSPClientSession::~NvrRTSPClientSession()
{

}

RTSPServer::RTSPClientSession* ELCRTSPServer::createNewClientSession(u_int32_t sessionId)
{
	return new NvrRTSPClientSession(*this, sessionId);
}

void ELCRTSPServer::NvrRTSPClientSession::handleCmd_SETUP(RTSPServer::RTSPClientConnection* ourClientConnection,
													 char const* urlPreSuffix, char const* urlSuffix, char const* fullRequestStr)
{
	LOG_INFO("***REQUEST*** SETUP Session ID: " <<int2string(fOurSessionId));
	RTSPServer::RTSPClientSession::handleCmd_SETUP(ourClientConnection, urlPreSuffix, urlSuffix, fullRequestStr);
    NvrRTSPClientConnection* rtspConection = (NvrRTSPClientConnection*)ourClientConnection;
    LOG_INFO("***RESPOND*** SETUP: "<<int2string(fOurSessionId)<<"\n"<<rtspConection->getBufferRespond());
}


void ELCRTSPServer::NvrRTSPClientSession::handleCmd_PLAY(RTSPClientConnection* ourClientConnection,
													ServerMediaSubsession* subsession, char const* fullRequestStr)
{
	LOG_INFO("***REQUEST*** PLAY Session ID: "<<int2string(fOurSessionId));
    RTSPServer::RTSPClientSession::handleCmd_PLAY(ourClientConnection, subsession, fullRequestStr);
    NvrRTSPClientConnection* rtspConection = (NvrRTSPClientConnection*)ourClientConnection;
    LOG_INFO("***RESPOND*** PLAY: "<<int2string(fOurSessionId)<<"\n"<<rtspConection->getBufferRespond());
}

void ELCRTSPServer::NvrRTSPClientSession::handleCmd_PAUSE(RTSPClientConnection* ourClientConnection,
													 ServerMediaSubsession* subsession)
{
	LOG_INFO("***REQUEST*** PAUSE Session ID = "<<int2string(fOurSessionId));
    RTSPServer::RTSPClientSession::handleCmd_PAUSE(ourClientConnection, subsession);
    NvrRTSPClientConnection* rtspConection = (NvrRTSPClientConnection*)ourClientConnection;
    LOG_INFO("***RESPOND*** PAUSE: "<<int2string(fOurSessionId)<<"\n"<<rtspConection->getBufferRespond());

}

void ELCRTSPServer::NvrRTSPClientSession::handleCmd_TEARDOWN(RTSPClientConnection* ourClientConnection,
														ServerMediaSubsession* subsession)
{
	LOG_INFO("***REQUEST*** TEARDOWN Session ID = "<<int2string(fOurSessionId));
	RTSPServer::RTSPClientSession::handleCmd_TEARDOWN(ourClientConnection, subsession);
    NvrRTSPClientConnection* rtspConection = (NvrRTSPClientConnection*)ourClientConnection;
    LOG_INFO("***RESPOND*** TEARDOWN: "<<int2string(fOurSessionId)<<"\n"<<rtspConection->getBufferRespond());
}

std::vector<std::string> ELCRTSPServer::getFileDirectory(std::string ID, std::string mts, std::string mte, int &codec)     //ip?t1=yyyymmdd-hhmmss&t2=yyyymmdd-hhmmss&speed
{
	codec = -1;
	char ts[20];
	strcpy(ts, mts.c_str());
	char te[20];
	strcpy(te, mte.c_str());
	struct stat st;
	std::string pathHour, pathID, fileNameBefor, fileNameAfter;
	std::string yBegin, mBegin, dBegin, hBegin, mnBegin, sBegin, timeBegin, dateBegin;
	std::string yEnd, mEnd, dEnd, hEnd, mnEnd, sEnd, timeEnd, dateEnd;
	fileNameAfter = fileNameBefor = "";

    std::vector<std::string> listAllHourFiles, listSelectedFile, listAllHour, vt;
    std::vector<std::string>::iterator it, it2;
	//get date start
    vt = split(ts, "=-");
    if(vt.size()!=3)
    	return listSelectedFile;
    dateBegin = vt[1];
    timeBegin = vt[2];
    //get date end
    vt.clear();
    vt = split(te, "=-");
    if(vt.size()!=3)
    	return listSelectedFile;
    dateEnd = vt[1];
    timeEnd = vt[2];
    if(dateBegin.length()!=8 || dateEnd.length()!=8 || timeBegin.length()!=6 || timeEnd.length()!=6)
    	return listSelectedFile;

    yBegin = dateBegin.substr(0, 4);
    mBegin = dateBegin.substr(4,2);
    dBegin = dateBegin.substr(6);
    hBegin = timeBegin.substr(0,2);
    mnBegin = timeBegin.substr(2,2);
    sBegin = timeBegin.substr(4);

    yEnd = dateEnd.substr(0, 4);
    mEnd = dateEnd.substr(4,2);
    dEnd = dateEnd.substr(6);
    hEnd = timeEnd.substr(0,2);
    mnEnd = timeEnd.substr(2,2);
    sEnd = timeEnd.substr(4);
    if(atoi(yBegin.c_str()) > atoi(yEnd.c_str()) || atoi(mBegin.c_str()) > atoi(mEnd.c_str())
    		|| atoi(dBegin.c_str()) > atoi(dEnd.c_str()) /*||  atoi(hBegin.c_str()) > atoi(hEnd.c_str())*/)
    {
    	LOG_INFO("Time Begin and Time End uncorrect");
    	return listSelectedFile;
    }
    //get list file in folder
    pathHour = getStoragePath() + "/" + ID + "/" + yBegin + "/" + mBegin + "/" + dBegin;
	if ((stat(pathHour.c_str(), &st) == 0 && S_ISDIR(st.st_mode))==false)
	{
		LOG_INFO("Not Exist folder file");
		return listSelectedFile;
	}

    getdir(pathHour, listAllHour);
    if(dateBegin != dateEnd)
    {
     //pending
    }


    LOG_INFO("pathHour:" << pathHour);


    if(listAllHour.size() == 0)
    {
    	LOG_INFO("Folder don't have file");
    	return listSelectedFile;
    }

    int ihBegin = atoi(hBegin.c_str());
    int ihEnd = atoi(hEnd.c_str());
    int imnBegin = atoi(mnBegin.c_str());
    int imnEnd = atoi(mnEnd.c_str());
    int isBegin = atoi(sBegin.c_str());
    int isEnd = atoi(sEnd.c_str());


	FileHandler* mFileHandler;
    if(ihBegin == ihEnd)
    {
    	LOG_INFO("ihBegin == ihEnd");
    	bool isFileContainTimeBegin = false;
    	std::string pathFile = pathHour + "/" + hBegin;
    	LOG_INFO("pathFile:" << pathFile);

    	getdir(pathFile, listAllHourFiles);
		char* splitName = new char[100];
		for(it=listAllHourFiles.begin(); it!=listAllHourFiles.end(); it++)
		{
			vt.clear();
			memset(splitName, 0, sizeof(splitName));
			strcpy(splitName, (*it).c_str());
			vt = split(splitName, "-.");
			if(vt.size()<4)
				continue;
			std::string ts = vt[vt.size() - 2];
			int minus = atoi(ts.substr(2,2).c_str());
			int second = atoi(ts.substr(4,2).c_str());

			std::string filePath = pathFile + "/" + (*it);
			if(minus*60 + second >= imnEnd*60 + isEnd)
				continue;
			else  {
				mFileHandler = new FileHandler();
				if(mFileHandler->OpenFile(filePath.c_str())==false)
				{
					if(mFileHandler)
					{
						delete mFileHandler;
						mFileHandler = NULL;
					}
					continue;
				}
				int duration = mFileHandler->GetDuration()/1000000;
				if((minus*60 + second + duration)>(imnBegin* 60 + isBegin)>(minus*60 + second))
				{
					isFileContainTimeBegin = true;
				}

				if((imnBegin*60 + isBegin)<=(minus*60 + second + duration))
					listSelectedFile.push_back(filePath);
				if(mFileHandler) {
					delete mFileHandler;
					mFileHandler = NULL;
				}
			}
		}

		if(isFileContainTimeBegin == false)
		{
			std::string h;
			if(ihBegin <11)
				h = "0" + int2string(ihBegin -1);
			else
				h = int2string(ihBegin -1);
			pathFile = pathHour + "/" + h;
			std::string oldestFile = getOldestItem(pathFile);
			std::string pathOldestFile = pathFile + "/" + oldestFile;
			LOG_INFO("oldestFile: "<<oldestFile);
			mFileHandler = new FileHandler();
			if(mFileHandler->OpenFile(pathOldestFile.c_str())==false)
			{
				if(mFileHandler) {
					delete mFileHandler;
					mFileHandler = NULL;
				}
			}

			if(mFileHandler)
			{
				vt.clear();
				memset(splitName, 0, sizeof(splitName));
				strcpy(splitName, oldestFile.c_str());
				vt = split(splitName, "-.");
				std::string ts = vt[vt.size() - 2];
				int minus = atoi(ts.substr(2,2).c_str());
				int second = atoi(ts.substr(4,2).c_str());
				int duration = mFileHandler->GetDuration()/1000000;
				LOG_INFO("minus, second, duration: "<<minus<<"  "<<second<<"  "<<duration);
				if(minus* 60 + second + duration > imnBegin*60 + isBegin + 3600)
					listSelectedFile.push_back(pathOldestFile);
				if(mFileHandler) {
					delete mFileHandler;
					mFileHandler = NULL;
				}
			}
		}//end isFileContainTimeBegin == false
    }//end ihBegin == ihEnd
    else
    {
    	LOG_INFO("ihBegin != ihEnd");
		bool isFileContainTimeBegin = false;
		for(it = listAllHour.begin(); it != listAllHour.end(); it++)
		{
			listAllHourFiles.clear();
			int i = atoi((*it).c_str());
			std::string p = pathHour + "/" + (*it);

			if(ihBegin < i && i < ihEnd)
			{
				getdir(p, listAllHourFiles);
				for(it2=listAllHourFiles.begin(); it2!=listAllHourFiles.end(); it2++)
				{
					listSelectedFile.push_back(p + "/" + (*it2));
					LOG_INFO("File:" << p << "/" << (*it2));
				}
			}
			else if (ihBegin == i)
			{
				getdir(p, listAllHourFiles);
				char* splitName = new char[100];
				for(it2=listAllHourFiles.begin(); it2!=listAllHourFiles.end(); it2++)
				{
					vt.clear();
					memset(splitName, 0, sizeof(splitName));
					strcpy(splitName, (*it2).c_str());
					vt = split(splitName, "-.");
					if(vt.size()<4)
						continue;
					std::string ts = vt[vt.size() - 2];
					int minus = atoi(ts.substr(2,2).c_str());
					int second = atoi(ts.substr(4,2).c_str());
					std::string filePath = p + "/" + (*it2);
					if(minus > imnBegin)
						listSelectedFile.push_back(filePath);
					else
					{
						mFileHandler = new FileHandler();
						if(mFileHandler->OpenFile(filePath.c_str())==false)
						{
							if(mFileHandler)
							{
								delete mFileHandler;
								mFileHandler = NULL;
							}

							continue;
						}

						int duration = mFileHandler->GetDuration()/1000000;
						if((minus*60 + second + duration) >= (imnBegin* 60 + isBegin))
							listSelectedFile.push_back(filePath);
						if((minus*60 + second + duration)>(imnBegin* 60 + isBegin)>(minus*60 + second))
						{
							isFileContainTimeBegin = true;
						}

						if(mFileHandler)
						{
							delete mFileHandler;
							mFileHandler = NULL;
						}
					}
				}


				if(isFileContainTimeBegin == false)
				{
					std::string h;
					if(ihBegin <11)
						h = "0" + int2string(ihBegin -1);
					else
						h = int2string(ihBegin -1);

					std::string pathFile = pathHour + "/" + h;
					std::string oldestFile = getOldestItem(pathFile);

					LOG_INFO("pathFile:" << pathFile);
					LOG_INFO("oldestFile:"<< oldestFile);
					std::string pathOldestFile = pathFile + "/" + oldestFile;
					mFileHandler = new FileHandler();
					if(mFileHandler->OpenFile(pathOldestFile.c_str())==false)
					{
						if(mFileHandler)
						{
							delete mFileHandler;
							mFileHandler = NULL;
						}

						LOG_ERROR("open file error: "<<pathOldestFile);
						continue;
					}

					vt.clear();
					memset(splitName, 0, sizeof(splitName));
					strcpy(splitName, oldestFile.c_str());
					vt = split(splitName, "-.");
					if(vt.size()<4)
					{
						continue;
					}

					std::string ts = vt[vt.size() - 2];
					int minus = atoi(ts.substr(2,2).c_str());
					int second = atoi(ts.substr(4,2).c_str());
					int duration = mFileHandler->GetDuration()/1000000;
					if(minus* 60 + second + duration > imnBegin*60 + isBegin + 3600)
					{
						listSelectedFile.push_back(pathOldestFile);
					}

					if(mFileHandler)
					{
						delete mFileHandler;
						mFileHandler = NULL;
					}
				}


				delete[] splitName;
			}//end isFileContainTimeBegin == false
			else if (ihEnd == i)
			{
				getdir(p, listAllHourFiles);
				char* splitName = new char[100];
				for(it2=listAllHourFiles.begin(); it2!=listAllHourFiles.end(); it2++)
				{
					vt.clear();
					memset(splitName, 0, sizeof(splitName));
					strcpy(splitName, (*it2).c_str());
					vt = split(splitName, "-.");
					if(vt.size()<4)
						continue;
					std::string ts = vt[vt.size() - 2];
					int minus = atoi(ts.substr(2,2).c_str());
					int second = atoi(ts.substr(4,2).c_str());
					std::string filePath = p + "/" + (*it2);
					if(minus > imnEnd)
					{
						continue;
					}
					else
					{
						listSelectedFile.push_back(filePath);
					}
				}
				delete[] splitName;
			}//end if ihEnd == i

		}//end for
    }

    if(listSelectedFile.size() == 0)
    	return listSelectedFile;
    //get codec file
    mFileHandler = new FileHandler();
	if(mFileHandler->OpenFile(listSelectedFile[0].c_str())) {
		codec = mFileHandler->getCodec();
	}
	if(mFileHandler) {
		delete mFileHandler;
		mFileHandler = NULL;
	}
	LOG_INFO("codec = "<<codec);

    //arrange list file name
    int t1, t2, dt1, dt2 = 0;
    std::string name;
	char* splitName = new char[100];
    for(int i = 0; i< listSelectedFile.size() -1; i++) {
    	for(int ii = i+1; ii <listSelectedFile.size() ; ii++) {
			vt.clear();
			std::string filePath = listSelectedFile[i];
			memset(splitName, 0, sizeof(splitName));
			strcpy(splitName, filePath.c_str());
			vt = split(splitName, "/");
			std::string fileName = vt[vt.size() -1];
			vt.clear();
			vt = split((char*)fileName.c_str(), "-.");
			t1 = atoi(vt[2].c_str());
			dt1 = atoi(vt[1].c_str());

			vt.clear();
			filePath = listSelectedFile[ii];
			memset(splitName, 0, sizeof(splitName));
			strcpy(splitName, filePath.c_str());
			vt = split(splitName, "/");
			fileName = vt[vt.size() -1];
			vt.clear();
			vt = split((char*)fileName.c_str(), "-.");
			t2 = atoi(vt[2].c_str());
			dt2 = atoi(vt[1].c_str());
            if(dt2<dt1) {
            	name = listSelectedFile[i];
				listSelectedFile[i] = listSelectedFile[ii];
				listSelectedFile[ii] = name;
            }
            else if (dt2>dt1) {
				continue;
			}
            else  {
            	if(t2 <t1) {
					name = listSelectedFile[i];
					listSelectedFile[i] = listSelectedFile[ii];
					listSelectedFile[ii] = name;
				}
            }
        }
    }
    delete[] splitName;
    LOG_INFO("List file selected: ");
    for(int i = 0; i< listSelectedFile.size(); i++) {
    	LOG_INFO(listSelectedFile[i]);
    }
    LOG_INFO("finish arrange file");
    return listSelectedFile;
}


std::string ELCRTSPServer::getOldestItem(std::string path) {
	std::string oldestItem, item;
	std::vector<std::string> listItem, vt;
	std::vector<std::string>::iterator it;
	char* splitName = new char[100];
	int time = 0;
	getdir(path, listItem);
	if(listItem.size()<1)
		return "";
	for(it=listItem.begin(); it!=listItem.end(); it++) {
		int temp;
		memset(splitName, 0, sizeof(splitName));
		strcpy(splitName, (*it).c_str());
		vt.clear();
		vt = split(splitName, "-.");
		temp = atoi(vt[2].c_str());
		if(time==0) {
			time = atoi(vt[2].c_str());
			oldestItem = (*it);
		}

        if(temp > time) {
        	time = temp;
        	oldestItem = (*it);
        }
	}
	delete[] splitName;
	return oldestItem;
}
