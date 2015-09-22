/*
 * ElcRTSPClient.cpp
 *
 *  Created on: Jul 9, 2014
 *      Author: xyz
 */

#include "ElcRTSPClient.h"
#include "DummySink.h"
#include <iostream>
#include <thread>
#include "imageoverlaytext.h"

#define RTSP_CLIENT_VERBOSITY_LEVEL 0

//====================Stream state==========================

StreamClientState::StreamClientState()
  : iter(NULL), session(NULL), subsession(NULL), streamTimerTask(NULL), duration(0.0)
{

}

StreamClientState::~StreamClientState()
{
  delete iter;
  if (session != NULL)
  {
    UsageEnvironment& env = session->envir(); // alias
    env.taskScheduler().unscheduleDelayedTask(streamTimerTask);
    Medium::close(session);
  }
}

//===================Our RTSP Client==============================


OurRTSPClient* OurRTSPClient::createNew(UsageEnvironment& env, char const* rtspURL,
					int verbosityLevel, char const* applicationName, portNumBits tunnelOverHTTPPortNum)
{
  return new OurRTSPClient(env, rtspURL, verbosityLevel, applicationName, tunnelOverHTTPPortNum);
}

OurRTSPClient::OurRTSPClient(UsageEnvironment& env, char const* rtspURL,
			     int verbosityLevel, char const* applicationName, portNumBits tunnelOverHTTPPortNum)
  : RTSPClient(env,rtspURL, verbosityLevel, applicationName, tunnelOverHTTPPortNum, -1)
{
}

OurRTSPClient::~OurRTSPClient()
{

}


//===================Elc RTSP Client==============================

ElcRTSPClient::ElcRTSPClient()
{
	scheduler = BasicTaskScheduler::createNew();
	env = BasicUsageEnvironment::createNew(*scheduler);
	eventLoopWatchVariable = 0;
	mURL = "";
	isStart = false;
	isReceivedByeFromServer = false;
	isFirstTime = true;
	hasClosed = false;
	isRetry = Config::isRetry;
	stopRetry = false;
	isReady = false;
	runningMonitor = false;
	rtspClient = NULL;
}


ElcRTSPClient::~ElcRTSPClient()
{

}

bool ElcRTSPClient::setSource(const string& url)
{
	mURL = url;
	ip = elc::getIpFromRtspUrl(url);
	isReady = true;
	return true;
}

int ElcRTSPClient::start()
{
	LOG_INFO("ElcRTSPClient::start start the client");
	eventLoopWatchVariable = 0;
	hasClosed = false;
	rtspClient = OurRTSPClient::createNew(*env, mURL.c_str(), RTSP_CLIENT_VERBOSITY_LEVEL, NULL);
	if (rtspClient == NULL)
	{
		LOG_ERROR("ElcRTSPClient::start cannot creat rtsp client with url="<<mURL);
		return voverlay_error::VOVERLAY_INIT_FAILED;
	}

	mThread = new std::thread(startThread, this);
	//mThread = std::unique_ptr<std::thread>(new std::thread(startThread, this));
	//std::unique_ptr<std::thread> mThread(new std::thread(startThread, this));
	uint32_t start = elc::GetTickCount();
	while(1)
	{
		statusLocker.lock();
		if(isStart)
		{
			statusLocker.unlock();
			break;
		}
		statusLocker.unlock();
		if(elc::GetTickCount() - start > 5000) // wait maximum 5seconds
			break;
		usleep(20*1000);
	}
	if(!isStart)
	{
		eventLoopWatchVariable = 1;
		if(mThread != NULL)
		{
			mThread->join();
			delete mThread; mThread = NULL;
		}
		return voverlay_error::VOVERLAY_INIT_FAILED;
	}
	stopRetry = false;
	if(runningMonitor == false)
		monitorThread = new std::thread(startMonitorThread, this);
	return voverlay_error::VOVERLAY_OK;
}


void ElcRTSPClient::stop()
{
	LOG_INFO("ElcRTSPClient::stop stop client");
	eventLoopWatchVariable = 1;
	isStart = false;
	stopRetry = true;
	runningMonitor = false;
	usleep(50*1000);
	if(mThread != NULL)
	{
		LOG_INFO("ElcRTSPClient::stop delete thread");
		mThread->join();
		delete mThread;
		mThread = NULL;
	}
	if(monitorThread != NULL)
	{
		LOG_INFO("ElcRTSPClient::stop delete monitor thread");
		monitorThread->join();
		delete monitorThread; monitorThread = NULL;
	}
	int errcode = 0;
	usleep(50*1000);
	if(!hasClosed)
		shutdownStream(rtspClient, errcode);
}

void ElcRTSPClient::continueAfterDESCRIBE(RTSPClient* rtspClient, int resultCode, char* resultString)
{
	do
	{
		UsageEnvironment& env = rtspClient->envir(); // alias
		StreamClientState& scs = ((OurRTSPClient*)rtspClient)->scs; // alias

		if (resultCode != 0)
		{
			//env << "Failed to get a SDP description: " << resultString << "\n";
			LOG_ERROR("ElcRTSPClient::continueAfterDESCRIBE cannot get SDP line: "<<resultString);
			delete[] resultString;
			break;
		}

		char* const sdpDescription = resultString;
		scs.session = MediaSession::createNew(env, sdpDescription);
		delete[] sdpDescription; // because we don't need it anymore
		if (scs.session == NULL)
		{
			//env << "Failed to create a MediaSession object from the SDP description: " << env.getResultMsg() << "\n";
			LOG_ERROR("ElcRTSPClient::continueAfterDESCRIBE Failed to create a MediaSession object from the SDP description: " << env.getResultMsg());
			break;
		}
		else if (!scs.session->hasSubsessions())
		{
			//env << "This session has no media subsessions (i.e., no \"m=\" lines)\n";
			LOG_ERROR("ElcRTSPClient::continueAfterDESCRIBE This session has no media subsessions (i.e., no \"m=\" lines)");
			break;
		}
		scs.iter = new MediaSubsessionIterator(*scs.session);
		setupNextSubsession(rtspClient);
		return;
   } while (0);

//	// retrying ... if stream has been started
//	ElcRTSPClient* elcClient = SourceManager::getSingleton().findClient(rtspClient);
//	if(Config::isRetry && !elcClient->isFirstTime)
//	{
//		sleep(5);
//		rtspClient->sendDescribeCommand(ElcRTSPClient::continueAfterDESCRIBE);
//		LOG_INFO("ElcRTSPClient::continueAfterDESCRIBE RYTRYING ... connection lost -url="<<elcClient->getIP());
//	}
//	else
	{
		shutdownStream(rtspClient);
	}

}

#define REQUEST_STREAMING_OVER_TCP False

void ElcRTSPClient::setupNextSubsession(RTSPClient* rtspClient)
{

    UsageEnvironment& env = rtspClient->envir(); // alias
    StreamClientState& scs = ((OurRTSPClient*)rtspClient)->scs; // alias

    scs.subsession = scs.iter->next();
    if (scs.subsession != NULL)
    {
      if (!scs.subsession->initiate())
      {
        env << "Failed to initiate the \"" << scs.subsession << "\" subsession: " << env.getResultMsg() << "\n";
        setupNextSubsession(rtspClient); // give up on this subsession; go to the next one
      }
      else
      {
        //env<< "Initiated the \"" << scs.subsession << "\" subsession (";
    	  LOG_INFO("ElcRTSPClient::setupNextSubsession Initiated the subsession -add="<<scs.subsession);
        if (scs.subsession->rtcpIsMuxed())
        {
    	    //env << "client port " << scs.subsession->clientPortNum();
        }
        else
        {
    	    //env << "client ports " << scs.subsession->clientPortNum() << "-" << scs.subsession->clientPortNum()+1;
        }
       // env << ")\n";

        // Continue setting up this subsession, by sending a RTSP "SETUP" command:
        rtspClient->sendSetupCommand(*scs.subsession, continueAfterSETUP, False, REQUEST_STREAMING_OVER_TCP);
      }
      return;
    }

    // We've finished setting up all of the subsessions.  Now, send a RTSP "PLAY" command to start the streaming:
    if (scs.session->absStartTime() != NULL)
    {
      // Special case: The stream is indexed by 'absolute' time, so send an appropriate "PLAY" command:
      rtspClient->sendPlayCommand(*scs.session, continueAfterPLAY, scs.session->absStartTime(), scs.session->absEndTime());
    }
    else
    {
      scs.duration = scs.session->playEndTime() - scs.session->playStartTime();
      rtspClient->sendPlayCommand(*scs.session, continueAfterPLAY);
    }
}


void ElcRTSPClient::continueAfterSETUP(RTSPClient* rtspClient, int resultCode, char* resultString)
{
	ElcRTSPClient* thisClient = SourceManager::getSingletonPtr()->findClient(rtspClient);
	ImageOverlayText* pthis = SourceManager::getSingletonPtr()->findOverlay(thisClient->getSource());

	if (pthis== NULL)
	{
		LOG_ERROR("ElcRTSPClient::continueAfterSETUP faild to get overlay");
	}
	do
	{
		UsageEnvironment& env = rtspClient->envir(); // alias
		StreamClientState& scs = ((OurRTSPClient*)rtspClient)->scs; // alias

		if (resultCode != 0)
		{
		  //env<< "Failed to set up the \"" <<scs.subsession << "\" subsession: " << resultString << "\n";
		  LOG_ERROR("Failed to set up the subsession -add="<<scs.subsession<<" -desciption=" << resultString);
		  break;
		}

		//env<< "Set up the \"" <<scs.subsession << "\" subsession (";
		if (scs.subsession->rtcpIsMuxed())
		{
		  //env << "client port " << scs.subsession->clientPortNum();
		}
		else
		{
		 // env << "client ports " << scs.subsession->clientPortNum() << "-" << scs.subsession->clientPortNum()+1;
		}
		//env << ")\n";

		thisClient->mSink = DummySink::createNew(env, *scs.subsession, ImageOverlayText::onDataReceived, pthis, rtspClient->url());
		scs.subsession->sink = thisClient->mSink;

		if (scs.subsession->sink == NULL)
		{
			//env<< "Failed to create a data sink for the \"" <<scs.subsession
					//<< "\" subsession: " << env.getResultMsg() << "\n";
			LOG_ERROR("ElcRTSPClient::continueAfterSETUP Failed to create a data sink for subsession -add="<<scs.subsession<<" -description="<<env.getResultMsg());
			break;
		}

		// now, we can say that connection to camera is OK and we can get SDP from cam
		// and that start is ok, just leave the rest code to client, return ... hehe
		thisClient->statusLocker.lock();
		thisClient->isStart = true;
		thisClient->statusLocker.unlock();
		thisClient->isFirstTime = false;
		LOG_INFO("ElcRTSPClient::continueAfterSETUP -OK");
		//env<< "Created a data sink for the \"" <<scs.subsession << "\" subsession\n";
		scs.subsession->miscPtr = rtspClient; // a hack to let subsession handle functions get the "RTSPClient" from the subsession
		scs.subsession->sink->startPlaying(*(scs.subsession->readSource()),
						   subsessionAfterPlaying, scs.subsession);
		// Also set a handler to be called if a RTCP "BYE" arrives for this subsession:
		if (scs.subsession->rtcpInstance() != NULL)
		{
		    scs.subsession->rtcpInstance()->setByeHandler(subsessionByeHandler, scs.subsession);
		}

	} while (0);

  delete[] resultString;
  // Set up the next subsession, if any:
  setupNextSubsession(rtspClient);

}
void ElcRTSPClient::continueAfterPLAY(RTSPClient* rtspClient, int resultCode, char* resultString)
{
	LOG_INFO("ElcRTSPClient::continueAfterPLAY ---> called");
	Boolean success = False;
	do
	{
		UsageEnvironment& env = rtspClient->envir(); // alias
		StreamClientState& scs = ((OurRTSPClient*)rtspClient)->scs; // alias

		if (resultCode != 0)
		{
			env<< "Failed to start playing session: " << resultString << "\n";
			LOG_ERROR("ElcRTSPClient::continueAfterPLAY Failed to start playing session: " << resultString);
			break;
		}

		// Set a timer to be handled at the end of the stream's expected duration (if the stream does not already signal its end
		// using a RTCP "BYE").  This is optional.  If, instead, you want to keep the stream active - e.g., so you can later
		// 'seek' back within it and do another RTSP "PLAY" - then you can omit this code.
		// (Alternatively, if you don't want to receive the entire stream, you could set this timer for some shorter value.)
		if (scs.duration > 0)
		{
		   unsigned const delaySlop = 2; // number of seconds extra to delay, after the stream's expected duration.  (This is optional.)
		   scs.duration += delaySlop;
		   unsigned uSecsToDelay = (unsigned)(scs.duration*1000000);
		   scs.streamTimerTask = env.taskScheduler().scheduleDelayedTask(uSecsToDelay, (TaskFunc*)streamTimerHandler, rtspClient);
		}
		//env<< "Started playing session";
		if (scs.duration > 0)
		{
			env << " (for up to " << scs.duration << " seconds)";
		}
		//env << "...\n";

		success = True;
  } while (0);

  delete[] resultString;
  if(!success)
  {
     // An unrecoverable error occurred with this stream.
	 LOG_INFO("ElcRTSPClient::continueAfterPLAY shutdown stream");
     shutdownStream(rtspClient);
  }

}
// Other event handler functions:
void ElcRTSPClient::subsessionAfterPlaying(void* clientData) // called when a stream's subsession (e.g., audio or video substream) ends
{

	LOG_INFO("ElcRTSPClient::subsessionAfterPlaying ---> called");

	MediaSubsession* subsession = (MediaSubsession*)clientData;
	RTSPClient* rtspClient = (RTSPClient*)(subsession->miscPtr);

	// retrying ...
	ElcRTSPClient* elcClient = SourceManager::getSingleton().findClient(rtspClient);
	if(Config::isRetry && !elcClient->isFirstTime)
	{

		sleep(2);
		LOG_INFO("RETRYING ....");
		rtspClient->sendDescribeCommand(ElcRTSPClient::continueAfterDESCRIBE);
	}
	return;
	// Begin by closing this subsession's stream:
	Medium::close(subsession->sink);
	subsession->sink = NULL;

	// Next, check whether *all* subsessions' streams have now been closed:
	MediaSession& session = subsession->parentSession();
	MediaSubsessionIterator iter(session);
    while ((subsession = iter.next()) != NULL)
    {
    	if (subsession->sink != NULL) return; // this subsession is still active
    }

	// All subsessions' streams have now been closed, so shutdown the client:
	shutdownStream(rtspClient);

}

void ElcRTSPClient::subsessionByeHandler(void* clientData) // called when a RTCP "BYE" is received for a subsession
{
	LOG_INFO("ElcRTSPClient::subsessionByeHandler ---> called");
	MediaSubsession* subsession = (MediaSubsession*)clientData;
	RTSPClient* rtspClient = (RTSPClient*)subsession->miscPtr;
	UsageEnvironment& env = rtspClient->envir(); // alias

	env<< "Received RTCP \"BYE\" on \"" <<subsession << "\" subsession\n";

	// Now act as if the subsession had closed:
	subsessionAfterPlaying(subsession);

}

// Used to shut down and close a stream (including its "RTSPClient" object):
void ElcRTSPClient::shutdownStream(RTSPClient* rtspClient, int resultCode)
{
	LOG_INFO("ElcRTSPClient::shutdownStream");
	UsageEnvironment& env = rtspClient->envir(); // alias
	StreamClientState& scs = ((OurRTSPClient*)rtspClient)->scs; // alias

	// First, check whether any subsessions have still to be closed:
	if (scs.session != NULL)
	{
		Boolean someSubsessionsWereActive = False;
		MediaSubsessionIterator iter(*scs.session);
		MediaSubsession* subsession;

		while ((subsession = iter.next()) != NULL)
		{
		  if (subsession->sink != NULL)
		  {
			Medium::close(subsession->sink);
			subsession->sink = NULL;

			if (subsession->rtcpInstance() != NULL)
			{
				subsession->rtcpInstance()->setByeHandler(NULL, NULL); // in case the server sends a RTCP "BYE" while handling "TEARDOWN"
			}

			someSubsessionsWereActive = True;
		  }
		}

    if (someSubsessionsWereActive)
    {
      // Send a RTSP "TEARDOWN" command, to tell the server to shutdown the stream.
      // Don't bother handling the response to the "TEARDOWN".
      rtspClient->sendTeardownCommand(*scs.session, NULL);
    }
  }

  //env<< "Closing the stream.\n";
  Medium::close(rtspClient);
  SourceManager::getSingleton().findClient(rtspClient)->hasClosed = true;
}

void ElcRTSPClient::streamTimerHandler(void* clientData)
{
  OurRTSPClient* rtspClient = (OurRTSPClient*)clientData;
  StreamClientState& scs = rtspClient->scs; // alias

  scs.streamTimerTask = NULL;

  // Shut down the stream:
  shutdownStream(rtspClient);
}

void ElcRTSPClient::onDataReceived(VideoFrame videoFrame, void* userData)
{
	ElcRTSPClient* client = (ElcRTSPClient*)userData;
	client->addVideoFrameToQue(videoFrame);

}


VideoFrame ElcRTSPClient::getVideoFrame()
{
	//cout<<"rtsp client -- getVideoFrame"<<endl;
	//cout<<"   ++ videoFrame size = "<<videoFrame.size()<<endl;
	VideoFrame vf = VideoFrame();
	if(videoFrame.empty())
		return vf;
	frameLocker.lock();
	vf = videoFrame.front();
	videoFrame.pop();
	frameLocker.unlock();
	return vf;
}


//void *ElcRTSPClient::startThread(void* userData)
void ElcRTSPClient::startThread(void* userData)
{
	ElcRTSPClient* pThis = (ElcRTSPClient*)userData;
	pThis->rtspClient->sendDescribeCommand(ElcRTSPClient::continueAfterDESCRIBE);
	pThis->env->taskScheduler().doEventLoop(&(pThis->eventLoopWatchVariable));
}

void ElcRTSPClient::addVideoFrameToQue(const VideoFrame& vf)
{
	frameLocker.lock();
	videoFrame.push(vf);
	if (videoFrame.size() > MAX_PIC_QUE)
	    videoFrame.pop();
	frameLocker.unlock();
}

void ElcRTSPClient::tryConnect(void* data)
{
	LOG_INFO("ElcRTSPClient::tryConnect -start");
	int startResult = -1;
	if(isRetry)
	{
		while(startResult != VOVERLAY_OK && stopRetry == false)
		{
			sleep(10); // retrying every 10 second
			LOG_INFO("ElcRTSPClient::tryConnect Retrying ...");
			eventLoopWatchVariable = 1;
			isStart = false;
			usleep(50*1000);
			if(mThread != NULL)
			{
				mThread->join();
				delete mThread;
				mThread = NULL;
			}
			int errcode = 0;
			usleep(50*1000);
			if(!hasClosed)
				shutdownStream(rtspClient, errcode);
			usleep(50*1000);
			startResult = start();
		}
	}
	if(startResult == VOVERLAY_OK)
	{
		SourceManager::getSingleton().findOverlay(mURL)->setNoSignal(false);
		LOG_INFO("ElcRTSPClient::tryConnect OK");
	}
}

void ElcRTSPClient::startMonitorThread(void* userData)
{
	ElcRTSPClient* client = (ElcRTSPClient*)userData;
	ImageOverlayText* ov = SourceManager::getSingleton().findOverlay(client->mURL);
	LOG_INFO("ElcRTSPClient try connecting thread conversion OK");
	client->runningMonitor = true;
	while(true)
	{
		if(client->runningMonitor == false)
			break;
		uint32_t t = client->mSink->getLastDataTime();
		uint32_t cur = elc::GetTickCount();
		if(cur - t > 5*1000 && t > 0)
		{
			if(client->isStart)
			{
				LOG_INFO("ElcRTSPClient detect connection lost, retrying ...");
				ov->setNoSignal(true);
				client->tryConnect(NULL);
			}
		}
		sleep(1);
	}
}
