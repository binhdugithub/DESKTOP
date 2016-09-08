/*
 * elcrtspserver.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: xyz
 */

#include "elcrtspserver.h"

ElcRTSPServer::ElcRTSPServer(int ourPort,
		UserAuthenticationDatabase* authDatabase, unsigned reclamationTestSeconds)
{
	std::cout << "ElcRTSPServer port:" << ourPort << std::endl;
	mTask = BasicTaskScheduler::createNew();
	mEnv = BasicUsageEnvironment::createNew(*mTask);
	mAuthDatabase = authDatabase;
	mReclamationTestSeconds = reclamationTestSeconds;
	mOurPort = ourPort;
	rtspServer = NULL;
	loopControl = 0;
	mediaSession = NULL;
	mediaSubSession = NULL;
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
		return false;
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
	std::cout <<"url:" << url << std::endl;
	std::cout <<"iname:" << iname << std::endl;
	LOG_INFO("ElcRTSPServer::setSource -url="<<url<<" -name="<<iname);
	mUrl = url;
	mName = iname;
	Boolean reuseFirstSource = true;
	if(!rtspServer)
	{
		LOG_ERROR("ElcRTSPServer::setSource failed! Rtspserver does not created propertly");
		return false;
	}
	mediaSession = ServerMediaSession::createNew(*mEnv, mName.c_str(), mName.c_str(), "ELC");
	if(!mediaSession)
		return false;


	mediaSubSession = Mpeg4LiveServerMediaSubSession::createNew(*mEnv, reuseFirstSource, mUrl);
	mediaSession->addSubsession(mediaSubSession);
	rtspServer->addServerMediaSession(mediaSession);

	std::cout << "setsource" << url << "ok" << std::endl;
	LOG_INFO("ElcRTSPServer::setSource OK");


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
	mUrl = url;
	mOutUrl = "";

	mThread = new std::thread(startThread, this);
	//mThread = std::unique_ptr<std::thread>(new std::thread(startThread, this));
	//std::unique_ptr<std::thread> mThread(new std::thread(startThread, this));
	uint32_t start = elc::GetTickCount();
	while(1)
	{
		mLocker.lock();
		if(mOutUrl != "")
		{
			mLocker.unlock();
			break;
		}
		mLocker.unlock();
		if(elc::GetTickCount() - start > 5000) // wait for 5 second
			break;
		usleep(1000*10);
	}
	outurl = mOutUrl;
	if(mOutUrl == "")
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

void ElcRTSPServer::startThread(void* usr)
{
	ElcRTSPServer* pthis = (ElcRTSPServer*)usr;
	pthis->doThread();
}

static void afterPlaying(void* clientData)
{
	LOG_INFO("Stop playing ...");

}

void ElcRTSPServer::doThread()
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;
	LOG_INFO("ElcRTSPServer::doThread start thread");
	ImageOverlayText* ov = SourceManager::getSingleton().findOverlay(mUrl);
	Mpeg4Package* firstPk = NULL;
	while(firstPk == NULL)
	{
		firstPk = ov->getEncodeData();
		usleep(100*1000);
		waitLocker.lock();
		if(isWait == false)
		{
			waitLocker.unlock();
			return;
		}
		waitLocker.unlock();

	}

	delete firstPk; firstPk = NULL;
	loopControl = 0;


	if(rtspServer->setUpTunnelingOverHTTP(80) || rtspServer->setUpTunnelingOverHTTP(8080))
	{
		LOG_INFO("ElcRTSPServer In case of H264, we can streaming over http -port="<<rtspServer->httpServerPortNum());
		std::cout << "ElcRTSPServer In case of H264, we can streaming over http -port=" <<rtspServer->httpServerPortNum() << std::endl;
	}

	std::cout << "ElcRTSPServer::doThread -> Toi day chua" << std::endl;
	mOutUrl = string(rtspServer->rtspURL(mediaSession));

	mEnv->taskScheduler().doEventLoop(&loopControl);
	usleep(50*1000);
	LOG_INFO("ElcRTSPServer::doThread end thread");
}



int ElcRTSPServer::stopStreaming()
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;
	LOG_INFO("ElcRTSPServer::stopStreaming -url="<<mUrl);

	rtspServer->closeAllClientSessionsForServerMediaSession(mediaSession);
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

void ElcRTSPServer::close()
{
	std::cout << __FILE__ << ":" << __FUNCTION__ << std::endl;
	LOG_INFO("ElcRTSPServer::close -url="<<mUrl);
	//rtspServer->closeAllClientSessionsForServerMediaSession(mediaSession);
	loopLocker.lock();
	loopControl = 1;
	loopLocker.unlock();


	rtspServer->closeAllClientSessionsForServerMediaSession(mediaSession);
	mediaSession->deleteAllSubsessions();
	rtspServer->deleteServerMediaSession(mediaSession);

	if(mThread != NULL)
	{
		mThread->join();
		delete mThread; mThread = NULL;
	}

}
