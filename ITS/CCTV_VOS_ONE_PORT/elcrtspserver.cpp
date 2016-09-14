/*
 * elcrtspserver.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: xyz
 */

#include "elcrtspserver.h"

extern UsageEnvironment* mEnv;
extern TaskScheduler* mTask;

ElcRTSPServer::ElcRTSPServer(int ourPort,
		UserAuthenticationDatabase* authDatabase, unsigned reclamationTestSeconds)
{
	std::cout << "ElcRTSPServer port:" << ourPort << std::endl;
	//mTask = BasicTaskScheduler::createNew();
	//mEnv = BasicUsageEnvironment::createNew(*mTask);
	mAuthDatabase = authDatabase;
	mReclamationTestSeconds = reclamationTestSeconds;
	mOurPort = ourPort;
	rtspServer = NULL;
	loopControl = 0;

	videoSink = NULL;
	rtcp = NULL;
	videoSource = NULL;
	isWait = true;
	isReady = false;

}


bool ElcRTSPServer::initServer()
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;
	rtspServer = RTSPServer::createNew(*mEnv, mOurPort, mAuthDatabase, mReclamationTestSeconds);
	if(rtspServer == NULL)
	{
		return false;
	}

	isReady = true;
	return true;
}

ElcRTSPServer::~ElcRTSPServer()
{
	// TODO Auto-generated destructor stub
	//Medium::close(rtspServer);
}

bool ElcRTSPServer::setSource(const string& url, const string& iname)
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;
	std::cout << "url: " << url << std::endl;
	std::cout << "name:" << iname << std::endl;

	Boolean reuseFirstSource = true;
	if(!rtspServer)
	{
		std::cout << "rtspServer is NULL" << std::endl;
		return false;
	}
	ServerMediaSession *mediaSession = ServerMediaSession::createNew(*mEnv, iname.c_str(), iname.c_str(), "ELC");
	if(!mediaSession)
	{
		std::cout << "mediaSession is NULL" << std::endl;
		return false;
	}

	Mpeg4LiveServerMediaSubSession *mediaSubSession = Mpeg4LiveServerMediaSubSession::createNew(*mEnv, reuseFirstSource, url);
	mediaSession->addSubsession(mediaSubSession);
	rtspServer->addServerMediaSession(mediaSession);

	return true;
}

int ElcRTSPServer::findSource(const string& url)
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;

	return -1;
}

int ElcRTSPServer::startStreaming(const string& url, string& outurl)
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;
	std::cout <<"stream:" << url << std::endl;

	LOG_INFO("ElcRTSPServer::startStreaming url="<<url);

	ImageOverlayText* ov = SourceManager::getSingleton().findOverlay(url);
	Mpeg4Package* firstPk = NULL;
	while(firstPk == NULL)
	{
		firstPk = ov->getEncodeData();
		usleep(100*1000);
		waitLocker.lock();
		if(isWait == false)
		{
			waitLocker.unlock();
			break;
		}
		waitLocker.unlock();

	}

	delete firstPk; firstPk = NULL;

	if(rtspServer->setUpTunnelingOverHTTP(80) || rtspServer->setUpTunnelingOverHTTP(8080))
	{
		LOG_INFO("ElcRTSPServer In case of H264, we can streaming over http -port="<<rtspServer->httpServerPortNum());
		std::cout << "ElcRTSPServer In case of H264, we can streaming over http -port=" <<rtspServer->httpServerPortNum() << std::endl;
	}

	std::string l_ip = elc::getIpFromRtspUrl(url);
	std::cout << "Start stream ip:" << l_ip << std::endl;
	ServerMediaSession *l_mdas = rtspServer->lookupServerMediaSession(l_ip.c_str());
	outurl = string(rtspServer->rtspURL(l_mdas));
	if(outurl == "")
	{
		waitLocker.lock();
		isWait = false;
		waitLocker.unlock();
		LOG_ERROR("ElcRTSPServer::startStreaming cannot start streaming");
		return voverlay_error::VOVERLAY_INIT_FAILED;
	}

	LOG_INFO("ElcRTSPServer::startStreaming start successfully -outputurl="<<outurl);
	return voverlay_error::VOVERLAY_OK;
}

static void afterPlaying(void* clientData)
{
	LOG_INFO("Stop playing ...");

}


int ElcRTSPServer::stopStreaming(const std::string &p_ip)
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;
	LOG_INFO("ElcRTSPServer::stopStreaming ip=" << p_ip);

	ServerMediaSession *l_mdas = rtspServer->lookupServerMediaSession(p_ip.c_str());
	rtspServer->closeAllClientSessionsForServerMediaSession(l_mdas);
	loopLocker.lock();
	loopControl = 1;
	loopLocker.unlock();

	if(mThread != NULL)
	{
		mThread->join();
		delete mThread; mThread = NULL;
	}
	return voverlay_error::VOVERLAY_OK;

}

void ElcRTSPServer::close(const std::string &p_ip)
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;
	LOG_INFO("ElcRTSPServer::close ip="<< p_ip.c_str());
	//rtspServer->closeAllClientSessionsForServerMediaSession(mediaSession);
	loopLocker.lock();
	loopControl = 1;
	loopLocker.unlock();

	ServerMediaSession *l_mdas = rtspServer->lookupServerMediaSession(p_ip.c_str());
	rtspServer->closeAllClientSessionsForServerMediaSession(l_mdas);
	l_mdas->deleteAllSubsessions();
	rtspServer->deleteServerMediaSession(l_mdas);

	if(mThread != NULL)
	{
		mThread->join();
		delete mThread; mThread = NULL;
	}

}
