/*
 * main.cpp
 *
 *  Created on: Jul 9, 2014
 *      Author: xyz
 */

#include "mycommon.h"
#include "ElcRTSPClient.h"
#include "sourcemanager.h"
#include "elcrtspserver.h"
#include "soapvideooverlayService.h"
#include "videooverlay.nsmap"
#include "soapStub.h"
#include "dbcontrol.h"
#include "config.h"
#include "MyRESTServer.h"
char* getErrDesc(int errCode); // forward

/// check for rtsp url's validation
bool checkRtspUrl(const string& url); // forward

int main(int argc, char *argv[])
{
	//QCoreApplication a(argc, argv);
	QApplication a(argc, argv);
 	std::cout<<"============== START PROGRAM =========="<<std::endl;
	InitLogger(true);
	LOG_INFO("\n");
	LOG_INFO("============== START PROGRAM ==========");

	if(!Config::readConfig("/opt/vos/etc/configvos.xml"))
	{
		cout<<"Cannot read config file, program is terminated!"<<endl;
		LOG_ERROR("Cannot read config file, program is terminated!");
		return -1;
	}


	// update all status in source,
	DBControl::create();
	LOG_INFO("Reset all sources status to 'stop' when start programe");
	DBControl::getSingleton().updateAllSourceStatus("0");

	OutPacketBuffer::maxSize = 4000000;

	//sourcemanger
	SourceManager::create();
	int port = Config::svrport;
	cout<<"RUNGING SERVER USING PORT "<<port<<endl;
	LOG_INFO("Running server use port "<<port);


	//
	//start REST Server
	//
	std::cout << "Start REST Server:" << Config::m_restport << "/" << Config::m_restroot << std::endl;
	LOG_INFO("Start REST Server");

	MyRESTServer *ServerREST = new MyRESTServer("0.0.0.0",
		 Config::m_restport,
		 Config::m_restroot);
	ServerREST->StartListen();

	//soap
	videooverlayService videoOverlaySvr;
	while (1)
	{
		if(videoOverlaySvr.run(port))
		{
			videoOverlaySvr.soap_stream_fault(std::cerr);
		}
		sleep(2);
	}

	return a.exec();
}


/// Web service operation 'addsource' (returns error code or SOAP_OK)
int videooverlayService::addsource(char *sourceurl, char *sourcename, struct voverlay_add_source_result *result)
{
	cout<<"WebService::addsource -url="<<sourceurl<<endl;
	LOG_INFO("\n");
	LOG_INFO("WebService::addSource -url="<<sourceurl<<" -name="<<sourcename);
	string url = string(sourceurl);
	string name = "";
	string outurl;
	int errCode = SourceManager::getSingleton().addSource(url, name, outurl);
	result->output_url = (char*)outurl.c_str();
	result->state.errorid = errCode;
	result->state.errordesc = getErrDesc(errCode);
	return SOAP_OK;
}

/// Web service operation 'delsource' (returns error code or SOAP_OK)
int videooverlayService::delsource(char *sourceurl, struct soap_overlay_status *result)
{
	cout<<"WebService::delSource -url="<<sourceurl<<endl;
	LOG_INFO("\n");
	LOG_INFO("WebService::delSource -url="<<sourceurl);
	string url = string(sourceurl);
	int errCode = SourceManager::getSingleton().removeSource(sourceurl);
	result->errorid = errCode;
	result->errordesc = getErrDesc(errCode);
	return SOAP_OK;
}

/// Web service operation 'runsource' (returns error code or SOAP_OK)
int videooverlayService::runsource(int command, char *sourceurl, struct soap_overlay_status *result)
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;
	cout<<"WebService::runSource -command="<<command<<" -url="<<sourceurl<<endl;
	LOG_INFO("\n");
	LOG_INFO("WebService::runSource -command="<<command<<" -url="<<sourceurl);
	string ip = elc::getIpFromRtspUrl(string(sourceurl));
	int errCode = 0;
	string errDes = "OK";
	string output = "";
	switch(command)
	{
	case 0: // stop
		errCode = SourceManager::getSingleton().stop(ip);
		break;
	case 1: // start
		errCode = SourceManager::getSingleton().start(ip, output);
		break;
	case 2: // restart
		errCode = SourceManager::getSingleton().stop(ip);
		if(errCode != 0)
			break;
		usleep(100*1000);
		errCode = SourceManager::getSingleton().start(ip, output);
		break;
	default:
		errCode = 100;
		errDes = "Command not valid, user command = 0 for stop, 1 for start and 2 for restart";
		break;
	}
	result->errorid = errCode;
	result->errordesc = getErrDesc(errCode);

	return SOAP_OK;
}

/// Web service operation 'runserver' (returns error code or SOAP_OK)
int videooverlayService::runserver(int command, struct soap_overlay_status *result)
{
	// we do not use this case
	LOG_INFO("\n");
	LOG_INFO("videooverlayService::runserver -command="<<command);
	result->errorid = 100;
	result->errordesc = getErrDesc(result->errorid);
	return SOAP_OK;

	int errCode = 0;
	switch(command)
	{
	case 0: // stop
		cout<<"Stop server"<<endl;
		errCode = SourceManager::getSingleton().stopAllSource();
		break;
	case 1: // start
		cout<<"Start server"<<endl;
		errCode = SourceManager::getSingleton().startAllSource();
		break;
	case 2: // restart
		cout<<"Restart all source"<<endl;
		errCode = SourceManager::getSingleton().restartAllSource();
		break;
	default:
		errCode = 100;
		break;
	}

	result->errorid = errCode;
	result->errordesc = getErrDesc(errCode);

	return SOAP_OK;
}

/// Web service operation 'settextposition' (returns error code or SOAP_OK)
int videooverlayService::settextposition(int lanepos, int staffpos, int classpos, int licensenumberpos, int pricepos, int timestamppos, struct soap_overlay_status *result)
{
	cout<<"videooverlayService::settextposition"<<endl;
	LOG_INFO("\n");
	LOG_INFO("WebService::setTextPosition -lanepos="<<lanepos<<" -staffpos="<<staffpos<<" -classpos="<<classpos
			<<" -licensepos="<<licensenumberpos<<" -pricepos="<<pricepos<<" -timestamp="<<timestamppos);
	int errCode = 0;
	if(DBControl::getSingleton().addLayout(lanepos, staffpos, classpos, licensenumberpos, pricepos, timestamppos) == 0)
	{
		errCode = 0;
		// TODO force overlay reload new position
	}
	else
	{
		errCode = 7;
	}

	result->errorid = errCode;
	result->errordesc = getErrDesc(errCode);
	return SOAP_OK;
}

char* getErrDesc(int errCode)
{
	string result;
	switch(errCode)
	{
	case 0:
		result = "OK";
		break;
	case 1:
		result = "Source does not exist";
		break;
	case 2:
		result = "Source has existed";
		break;
	case 3:
		result = "Dont support HD1080 resolution";
		break;
	case 4:
		result = "Server is out of load";
		break;
	case 5:
		result = "Url input is invalid";
		break;
	case 6:
		result = "Server init failed";
		break;
	case 7:
		result = "Error while working with database";
		break;
	default:
		result = "Unkown Error";
		break;
	}

	return (char*)result.c_str();
}

bool checkRtspUrl(const string& url)
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
