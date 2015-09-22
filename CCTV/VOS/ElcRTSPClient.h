/*
 * ElcRTSPClient.h
 *
 *  Created on: Jul 9, 2014
 *      Author: xyz
 */

#ifndef ELCRTSPCLIENT_H_
#define ELCRTSPCLIENT_H_

#include <live555/liveMedia.hh>
#include <live555/BasicUsageEnvironment.hh>
#include <string>
#include <string>
#include <deque>
#include <thread>
#include <mutex>

#include "sourcemanager.h"
#include "DummySink.h"

extern "C"
{
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
}

using namespace std;

//===============Stream Client State Calss==========================

class StreamClientState
{
public:
  StreamClientState();
  virtual ~StreamClientState();

public:
  MediaSubsessionIterator* iter;
  MediaSession* session;
  MediaSubsession* subsession;
  TaskToken streamTimerTask;
  double duration;
};

// ===============Our RTSP Client Class=============================
class OurRTSPClient: public RTSPClient
{
public:
	static OurRTSPClient* createNew(UsageEnvironment& env, char const* rtspURL, int verbosityLevel = 0,
		  char const* applicationName = NULL, portNumBits tunnelOverHTTPPortNum = 0);

protected:
	OurRTSPClient(UsageEnvironment& env, char const* rtspURL, int verbosityLevel,
			char const* applicationName, portNumBits tunnelOverHTTPPortNum);
	virtual ~OurRTSPClient();

public:
	StreamClientState scs;
};


//==============ELC RTSP Client Class============================

const unsigned int MAX_PIC_QUE = 10;

class ElcRTSPClient
{
public:
	// default constructor
	ElcRTSPClient();

	virtual ~ElcRTSPClient();

	// start
	int start();

	// stop
	void stop();

	// set source
	bool setSource(const string& url);

	// Get source
	string getSource() const
	{
		return mURL;
	}

	string getIP() const {return ip;}
	VideoFrame getVideoFrame();

	// get rtsp client
	RTSPClient* getRtspClient() const
	{
		return rtspClient;
	}

	void tryConnect(void* data); // data = pointer to be deleted which cannot delete in the other thread
	bool isStart;
	bool isReceivedByeFromServer;
	bool isFirstTime;
	bool hasClosed;
	bool isRetry;
	bool stopRetry;
	bool isReady;

protected:

	static void continueAfterDESCRIBE(RTSPClient* rtspClient, int resultCode, char* resultString);
	static void continueAfterSETUP(RTSPClient* rtspClient, int resultCode, char* resultString);
	static void continueAfterPLAY(RTSPClient* rtspClient, int resultCode, char* resultString);
	static void setupNextSubsession(RTSPClient* rtspClient);
	static void streamTimerHandler(void* clientData);
	static void subsessionAfterPlaying(void* clientData);
	static void subsessionByeHandler(void* clientData);
	static void shutdownStream(RTSPClient* rtspClient, int exitCode = 1);
	static void onDataReceived(VideoFrame videoFrame, void* userData);

	static void startThread(void* userData);
	static void startMonitorThread(void* userData);

public:
		void addVideoFrameToQue(const VideoFrame& vf);

private:
		TaskScheduler* scheduler;
		UsageEnvironment* env;
		char eventLoopWatchVariable;
		RTSPClient* rtspClient;
		string mURL;
		string ip;
		DummySink* mSink;
		//boost::recursive_mutex frameMutex;
		//boost::thread sThread;
		std::queue<VideoFrame> videoFrame;
		//std::unique_ptr<std::thread> mThread;
		std::thread* mThread;
		std::thread* monitorThread;
		bool runningMonitor;
		std::recursive_mutex frameLocker;
		std::recursive_mutex statusLocker;
		static void* userData;

};


#endif /* ELCRTSPCLIENT_H_ */
