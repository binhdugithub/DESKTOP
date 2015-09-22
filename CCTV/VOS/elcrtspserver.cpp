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

	// if multicast streaming
	if(Config::isMulticast)
	{
		struct in_addr destinationAddress;
		if(Config::streamingDestinationIp == "default" || Config::streamingDestinationIp =="")
			destinationAddress.s_addr = chooseRandomIPv4SSMAddress(*mEnv);
		else
			destinationAddress.s_addr = our_inet_addr(Config::streamingDestinationIp.c_str());

		Port rtpPort(Config::rtpPortNum);
		Port rtcpPort(Config::rtcpPortNum);

		rtpGroupsock = new Groupsock(*mEnv, destinationAddress, rtpPort, 255/*Config::ttl*/);
		rtpGroupsock->multicastSendOnly(); // we're a SSM source
		rtcpGroupsock = new Groupsock(*mEnv, destinationAddress, rtcpPort, 255/*Config::ttl*/);
		rtcpGroupsock->multicastSendOnly(); // we're a SSM source

		videoSink = MPEG4ESVideoRTPSink::createNew(*mEnv, rtpGroupsock, 96);

		const unsigned estimatedSessionBandwidth = 500; // in kbps; for RTCP b/w share
		const unsigned maxCNAMElen = 100;
		unsigned char CNAME[maxCNAMElen+1];
		gethostname((char*)CNAME, maxCNAMElen);
		CNAME[maxCNAMElen] = '\0'; // just in case

		rtcp = RTCPInstance::createNew(*mEnv, rtcpGroupsock,
						estimatedSessionBandwidth, CNAME,
						videoSink, NULL /* we're a server*/ ,
						True /* we're a SSM source */);

		mediaSession->addSubsession(PassiveServerMediaSubsession::createNew(*videoSink, rtcp));
		rtspServer->addServerMediaSession(mediaSession);

		LOG_INFO("ElcRTSPServer::setSource OK");
	}
	else // unicast streaming
	{
		mediaSubSession = Mpeg4LiveServerMediaSubSession::createNew(*mEnv, reuseFirstSource, mUrl);
		mediaSession->addSubsession(mediaSubSession);
		rtspServer->addServerMediaSession(mediaSession);
		LOG_INFO("ElcRTSPServer::setSource OK");
	}

	return true;
}

int ElcRTSPServer::findSource(const string& url)
{

	return -1;
}

int ElcRTSPServer::startStreaming(const string& url, string& outurl)
{
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
//  *env << "...done reading from file\n";
//
//  videoSink->stopPlaying();
//  Medium::close(videoSource);
//  // Note that this also closes the input file that this source read from.
//
//  // Start playing once again:
//  play();
}

void ElcRTSPServer::doThread()
{
	LOG_INFO("ElcRTSPServer::doThread start thread");
	ImageOverlayText* ov = SourceManager::getSingleton().findOverlay(mUrl);
	Mpeg4Package* firstPk = NULL;
	while(/*firstImg*/firstPk == NULL)
	{
		//firstImg = ov->getImage();
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

	if(Config::isMulticast)
	{
		FramedSource* videoES = Mpeg4LiveSource::createNew(*mEnv, mUrl);
		videoSource = MPEG4VideoStreamDiscreteFramer::createNew(*mEnv, videoES);
		LOG_INFO("ElcRTSPServer::doThread Videosink start playing");
		videoSink->startPlaying(*videoSource, afterPlaying, videoSink);
	}
	if(rtspServer->setUpTunnelingOverHTTP(80) || rtspServer->setUpTunnelingOverHTTP(8080))
	{
		LOG_INFO("ElcRTSPServer In case of H264, we can streaming over http -port="<<rtspServer->httpServerPortNum());
	}

	mOutUrl = string(rtspServer->rtspURL(mediaSession));

	mEnv->taskScheduler().doEventLoop(&loopControl);
	usleep(50*1000);
	LOG_INFO("ElcRTSPServer::doThread end thread");
}



int ElcRTSPServer::stopStreaming()
{
	LOG_INFO("ElcRTSPServer::stopStreaming -url="<<mUrl);
	if(Config::isMulticast)
	{
		if(videoSink)
		{
			videoSink->stopPlaying();
			if(videoSource)
				Medium::close(videoSource);
		}
	}
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
	LOG_INFO("ElcRTSPServer::close -url="<<mUrl);
	//rtspServer->closeAllClientSessionsForServerMediaSession(mediaSession);
	loopLocker.lock();
	loopControl = 1;
	loopLocker.unlock();

	if(Config::isMulticast)
	{
		if(videoSink)
		{
			videoSink->stopPlaying();
			if(videoSource)
				Medium::close(videoSource);
		}
	}

	rtspServer->closeAllClientSessionsForServerMediaSession(mediaSession);
	mediaSession->deleteAllSubsessions();
	rtspServer->deleteServerMediaSession(mediaSession);

	if(mThread != NULL)
	{
		mThread->join();
		delete mThread; mThread = NULL;
	}
	//mEnv->reclaim();
	//Medium::close(rtspServer);
	//Groupsock* gsock = (Groupsock*)mEnv->groupsockPriv;
	//gsock->removeAllDestinations();
	//delete gsock;
	//mEnv->reclaim();
	//delete mTask;
	//delete mEnv;
	//mediaSession = NULL;
	//mediaSubSession = NULL;
	//cout<<"close ok"<<endl;
	//Medium::close(mediaSubSession);
		/*
	loopLocker.lock();
	loopControl = 1;
	loopLocker.unlock();

	rtspServer->closeAllClientSessionsForServerMediaSession(mediaSession);
	//rtspServer->removeServerMediaSession(mediaSession);
	rtspServer->deleteServerMediaSession(mediaSession);
*/
	//Medium::close(mediaSubSession);
	//Medium::close(mediaSession);


//	Medium::close(mediaSubSession);
//	Medium::close(mediaSession);
//	Medium::close(rtspServer);
	//Medium::close(rtspServer);
	//cout<<"Close rtsp server ... Env add "<<mEnv<<endl;
	//ServerMediaSession::close(mediaSession);
	//stopStreaming();
	//rtspServer->removeServerMediaSession(mediaSession);
	//Medium::close(rtspServer);
}
