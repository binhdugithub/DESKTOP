/*
 * sourcemanager.cpp
 *
 *  Created on: Jul 15, 2014
 *      Author: xyz
 */

#include "sourcemanager.h"
#include "ElcRTSPClient.h"
#include "elcrtspserver.h"
#include "imageoverlaytext.h"

SourceManager::SourceManager()
{
	//if(DBControl::getSingleton().getAllSource(inputurl, inputName, username, password, status) != 0)
		//cout<<"SourceManager -- Can not read source from database"<<endl;
	DBControl::getSingleton().getAllSource(camip, inputurl, inputname, username,
			password, outputurl, framewidth, frameheight, codec, framerate, status);
	cout<<"All source in DB"<<endl;
	for(size_t i = 0; i < camip.size(); ++i)
		cout<<"camip "<<camip[i]<<"  "<<inputurl[i]<<endl;
	createSource();

}

SourceManager::~SourceManager()
{
	DBControl::getSingleton().updateAllSourceStatus("0");
}

int SourceManager::addSource(const std::string& url, const std::string& name, std::string& outUrl)
{
	if(!checkRtspUrl(url))
		return voverlay_error::VOVERLAY_URL_INVALID;
	string ip = elc::getIpFromRtspUrl(url);
	if(ip == "")
		return voverlay_error::VOVERLAY_URL_INVALID;
	if(findSource(url) >= 0)
		return voverlay_error::VOVERLAY_SOURCE_EXIST;

	//============ case we can use sources before =================
	int pos = findReuseSource();
	if(pos >= 0)
	{
		//cout<<"=========================>> It is new source "<<endl;
		ElcRTSPClient* client = mRtspClient[pos];
		ElcRTSPServer* server = mRtspServer[pos];
		ImageOverlayText* ov = mVideoOverlay[pos];

		client->setSource(url);
		server->setSource(url, ip);
		ov->setSource(url);
		camip[pos] = ip;
		inputurl[pos] = url;
		inputname[pos] = ip;
		if(DBControl::getSingleton().addSource(ip, url, ip, "0", "0", ip, "0", "0", "MPEG-4", "0", "0") != 0)
			return voverlay_error::VOVERLAY_DB_FAILED;
		return voverlay_error::VOVERLAY_OK;
	}

	//cout<<"=========================>> Create new source "<<endl;
	//=========== case cannot use previous source, just create new ===========
	camip.push_back(ip);
	inputname.push_back(ip);
	inputurl.push_back(url);

	int res = createSource(url);
	if(res != voverlay_error::VOVERLAY_OK)
	{
		camip.erase(camip.begin() + camip.size() - 1); // remove the last added
		inputname.erase(inputname.begin() + inputname.size() - 1);
		inputurl.erase(inputurl.begin() + inputurl.size() - 1);
		return res;
	}

	frameheight.push_back("0");
	framewidth.push_back("0");
	framerate.push_back("0");
	codec.push_back("MPEG-4");
	outputurl.push_back(ip);
	username.push_back("0");
	password.push_back("0");
	status.push_back("0");

	if(DBControl::getSingleton().addSource(ip, url, ip, "0", "0", ip, "0", "0", "MPEG-4", "0", "0") != 0)
		return voverlay_error::VOVERLAY_DB_FAILED;
	return voverlay_error::VOVERLAY_OK;
}

int SourceManager::addSource(ElcRTSPClient* rtspClient)
{
	return 0;
}

int SourceManager::removeSource(const string& url)
{
	int pos = findSource(url);
	if(pos < 0)
	{
		LOG_ERROR("SourceManager::removeSource Source not found");
		return voverlay_error::VOVERLAY_SOURCE_NOT_FOUND;
	}
	string ip = elc::getIpFromRtspUrl(url);
	ElcRTSPClient* client = mRtspClient[pos];
	ElcRTSPServer* server = mRtspServer[pos];
	ImageOverlayText* ov = mVideoOverlay[pos];

	if(status[pos] == "1")
	{
		server->close();
		client->stop();
	}

	usleep(200*1000);
	//cout<<"close overlay"<<endl;
	ov->close();
	usleep(200*1000);
	delete ov; ov = NULL;
//	delete server; server = NULL;
//	delete client; client = NULL;
	//cout<<"close all thread successfully"<<endl;

	// init empty source for the next time
	inputurl[pos] = "";
	camip[pos] = "";
	inputname[pos] = "";
	status[pos] = "0";
	ImageOverlayText* newOv = new ImageOverlayText();
	//newOv->setSource("");
	mVideoOverlay[pos] = newOv;

//	cout<<"Removeing source url = "<<ip<<endl;
//	cout<<"Before: size = "<<mRtspServer.size()<<"  "<<mRtspClient.size()<<endl;
//	for(size_t i = 0; i < inputurl.size(); ++i)
//		cout<<inputurl[i]<<endl;

//	mRtspClient.erase(mRtspClient.begin() + pos);
//	mRtspServer.erase(mRtspServer.begin() + pos);
//	mVideoOverlay.erase(mVideoOverlay.begin() + pos);
//	//serverPort.erase(serverPort.begin() + pos);
//	camip.erase(camip.begin() + pos);
//	inputurl.erase(inputurl.begin() + pos);
//	inputname.erase(inputname.begin() + pos);
//	username.erase(username.begin() + pos);
//	password.erase(password.begin() + pos);
//	outputurl.erase(outputurl.begin() + pos);
//	framewidth.erase(framewidth.begin() + pos);
//	frameheight.erase(frameheight.begin() + pos);
//	codec.erase(codec.begin() + pos);
//	framerate.erase(framerate.begin() + pos);
//	status.erase(status.begin() + pos);

//	cout<<"after source..."<<endl;
//	cout<<"after: size = "<<mRtspServer.size()<<"  "<<mRtspClient.size()<<endl;
//	for(size_t i = 0; i < inputurl.size(); ++i)
//		cout<<inputurl[i]<<endl;

//	cout<<"OK"<<endl;

	if(DBControl::getSingleton().removeSource(ip) != 0)
	{
		writeCurrentStatus();
		return voverlay_error::VOVERLAY_DB_FAILED;
	}
	return voverlay_error::VOVERLAY_OK;

}

int SourceManager::removeSource(ElcRTSPClient* rtspClient)
{
	int pos = 0;
	std::vector<ElcRTSPClient*>::iterator it;
	for(it = mRtspClient.begin(); it != mRtspClient.end(); ++it, ++pos)
	{
		if(*it == rtspClient)
		{
			mRtspClient.erase(mRtspClient.begin() + pos);
			return true;
		}
	}
	return false;
}

ElcRTSPClient* SourceManager::findClient(const std::string& url)
{
	ElcRTSPClient* client = NULL;
	std::vector<ElcRTSPClient*>::iterator it;
	for(it = mRtspClient.begin(); it != mRtspClient.end(); ++it)
	{
		if((*it)->getSource() == url)
		{
			client = (*it);
			break;
		}
	}
	return  client;
}


ElcRTSPClient* SourceManager::findClient(void* rtspClient)
{
	RTSPClient* client = (RTSPClient*)rtspClient;
	vector<ElcRTSPClient*>::iterator it;
	for(it = mRtspClient.begin(); it != mRtspClient.end(); ++it)
	{
		if((*it)->getRtspClient() == client)
			return *it;
	}
	return NULL;
}

ImageOverlayText* SourceManager::findOverlay(const std::string& ip)
{
	string mip = elc::getIpFromRtspUrl(ip);
	ImageOverlayText* overlay = NULL;
	std::vector<ImageOverlayText*>::iterator it;
	for(it = mVideoOverlay.begin(); it != mVideoOverlay.end(); ++it)
	{
		if((*it)->getIP() == mip)
		{
			overlay = (*it);
			break;
		}
	}
	return  overlay;
}

int SourceManager::start(const std::string& url, string& output)
{

	LOG_INFO("SourceManager::start -url="<<url);
	int pos = findSource(url);
	if(pos < 0)
	{
		LOG_ERROR("SourceManager::start  source not found");
		return voverlay_error::VOVERLAY_SOURCE_NOT_FOUND;
	}

	ElcRTSPClient* client = mRtspClient[pos];
	ElcRTSPServer* server = mRtspServer[pos];

	if(!server->isReady)
	{
		server->initServer();
		LOG_INFO("SourceManager::start server is not ready, try later");
		return voverlay_error::VOVERLAY_INIT_FAILED;
	}
	if(client->isStart)
	{
		LOG_ERROR("SourceManager::start  source has already started");
		return voverlay_error::VOVERLAY_OK;
	}

	LOG_INFO("SourceManager::start start client");
	if(client->start() != voverlay_error::VOVERLAY_OK)
	{
		LOG_ERROR("SourceManager::start cannot start rtsp client (ie. camera connection, cannot get sdp ...");
		return voverlay_error::VOVERLAY_INIT_FAILED;
	}

	LOG_INFO("SourceManager::start start server");
	if(server->startStreaming(url, output) != voverlay_error::VOVERLAY_OK)
	{
		LOG_ERROR("SourceManager::start cannot start streaming");
		return voverlay_error::VOVERLAY_INIT_FAILED;
	}

	status[pos] = "1";
	outputurl[pos] = output;

	cout<<"Play video using url: "<<output<<endl;
	if(DBControl::getSingleton().updateSource(camip[pos], output, "0", "0", "MPEG-4", "0", "1") == 0)
		return voverlay_error::VOVERLAY_OK;
	else
	{
		writeCurrentStatus();
		return voverlay_error::VOVERLAY_DB_FAILED;
	}
}

int SourceManager::stop(const std::string& url)
{
	LOG_INFO("SourceManager::stop -url="<<url);
	int pos = findSource(url);
	if(pos < 0)
	{
		LOG_INFO("SourceManager::stop source not found");
		return voverlay_error::VOVERLAY_SOURCE_NOT_FOUND;
	}

	ElcRTSPClient* client = mRtspClient[pos];
	ElcRTSPServer* server = mRtspServer[pos];

	server->stopStreaming();
	if(client->isStart)
		client->stop();

	string ip = elc::getIpFromRtspUrl(url);
	if(DBControl::getSingleton().updateSourceStatus(ip, "0") == 0)
		return voverlay_error::VOVERLAY_OK;
	else
	{
		writeCurrentStatus();
		LOG_ERROR("SourceManager::stop working with DB failed");
		return voverlay_error::VOVERLAY_DB_FAILED;
	}
}

int SourceManager::stopAllSource()
{
	if(inputurl.empty())
		return voverlay_error::VOVERLAY_OK;
	for(size_t i = 0; i < inputurl.size(); ++i)
	{
		string url = inputurl[i];
		stop(url);
	}
	return voverlay_error::VOVERLAY_OK;
}

int SourceManager::startAllSource()
{
//	if(inputurl.empty())
//		return voverlay_error::VOVERLAY_SOURCE_NOT_FOUND;
//	for(int i = 0; i < inputurl.size(); ++i)
//	{
//		string url = inputurl[i];
//		string outurl;
//		start(url, outurl);
//	}
//	return voverlay_error::VOVERLAY_OK;
//	vector<string> iurl;
//	vector<string> iname;
//	vector<string> iuser;
//	vector<string> ipass;
//	vector<string> istatus;

//	if(DBControl::getSingleton().getAllSource(iurl, iname, iuser,ipass, istatus) != 0)
//		return voverlay_error::VOVERLAY_DB_FAILED;
//
//	for(int i = 0; i < iurl.size(); ++i)
//	{
//		if(istatus[i] == "1")
//			continue;
//		string url = iurl[i];
//		string outurl;
//		start(url, outurl);
//	}
	return voverlay_error::VOVERLAY_OK;
}

int SourceManager::restartAllSource()
{
	stopAllSource();
	startAllSource();
	return voverlay_error::VOVERLAY_OK;
}


int SourceManager::removeAllSource()
{
	return -1;
}

int SourceManager::findSource(const std::string& url)
{
	string ip = elc::getIpFromRtspUrl(url);
	LOG_INFO("SourceManager::findSource -url="<<url<<" -ip="<<ip);
	if(camip.empty())
		return -1;
	for(size_t i = 0; i < camip.size(); ++i)
	{
		if(camip[i] == ip)
			return i;
	}
	return -1;
}

int SourceManager::autoSellectPort()
{
	// TODO increase port number logically and automtically
	int port = 8554;
	std::sort(serverPort.begin(), serverPort.end(), [](int p1, int p2){return p1 < p2;});
	for(size_t i = 0; i < serverPort.size(); ++i) // use !odd port
	{
		if(port != serverPort[i])
		{
			if(checkAvailablePort(port))
			{
				//serverPort.push_back(port);
				return port;
			}
		}
		port += 2;
	}
	// continue search in serverport.end() to limited port (8600)
	for(; port < 8600; port += 2)
	{
		if(checkAvailablePort(port))
		{
			//serverPort.push_back(port);
			return port;
		}
	}

	return -1;

}

void SourceManager::createSource()
{
	LOG_INFO("SourceManager::createSource All");
	if(inputurl.empty())
		return;
	for(size_t i = 0; i < inputurl.size(); ++i)
	{
		createSource(inputurl[i]);
	}
}

int SourceManager::createSource(const string& url)
{
	LOG_INFO("SourceManager::createSource -url="<<url);
	int port = autoSellectPort();
	if(port < 0)
	{
		LOG_ERROR("SourceManager::createSource  Failed to get available port");
		return -1;
	}
	int pos = findSource(url);
	if(pos < 0)
		return -1;
	ElcRTSPServer* server = new ElcRTSPServer(port, NULL);
	if(!server->initServer())
	{
		LOG_ERROR("SourceManager::createSource Failed to create server");
		return voverlay_error::VOVERLAY_INIT_FAILED; // cannot init server
	}

	if(!server->setSource(url, inputname[pos]))
	{
		LOG_ERROR("SourceManager::createSource Failed to set source");
		return voverlay_error::VOVERLAY_INIT_FAILED; // cannot init server
	}

	ElcRTSPClient* client = new ElcRTSPClient();
	client->setSource(url);

	ImageOverlayText* ov = new ImageOverlayText();
	ov->setSource(url);

	mRtspServer.push_back(server);
	mRtspClient.push_back(client);
	mVideoOverlay.push_back(ov);
	serverPort.push_back(port);

	LOG_INFO("SourceManager::createSource OK");

	return voverlay_error::VOVERLAY_OK;
}

bool SourceManager::checkAvailablePort(int port)
{

	return true;
}

bool SourceManager::checkRtspUrl(const string& url)
{
	// at least 14 character: rtsp://x.x.x.x
	if(url.length() < 14)
		return false;
	// url must start with "rtsp://"
	if(url.substr(0, 7) != "rtsp://")
		return false;
	// check for something here

	return true;
}

void SourceManager::writeCurrentStatus()
{
	ofstream of;
	of.open(dbfile, std::ofstream::out);
	//of.open(dbfile, std::ofstream::out);
	if(!of.is_open())
		return;
	of<<"1"<<endl; // header 0 = ok, 1 = error
	//write db
	size_t dbrow = camip.size();
	for(size_t i = 0; i < dbrow; ++i)
	{
		of<<"source="<<camip[i]<<";"<<inputurl[i]<<";"<<inputname[i]<<";"<<username[i]<<";"<<password[i]<<
				";"<<outputurl[i]<<";"<<framewidth[i]<<";"<<frameheight[i]<<";"<<codec[i]<<";"<<framerate[i]<<";"<<status[i]<<endl;
	}
	of.close();
}

int SourceManager::findReuseSource()
{
	if(camip.empty())
		return -1;
	for(size_t i = 0; i < camip.size(); ++i)
	{
		if(camip[i] == "")
			return i;
	}
	return -1;
}

RTSPServer* SourceManager::getGlobalRtspServerTest()
{
	if(mRtspServer.empty())
		return NULL;
	else
		return mRtspServer[0]->getCoreRTSPServer();
}
