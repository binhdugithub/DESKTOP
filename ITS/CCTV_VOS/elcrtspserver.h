/*
 * elcrtspserver.h
 *
 *  Created on: Jul 18, 2014
 *      Author: xyz
 */

#ifndef ELCRTSPSERVER_H_
#define ELCRTSPSERVER_H_

#include <liveMedia/liveMedia.hh>
#include <UsageEnvironment.hh>
#include <BasicUsageEnvironment.hh>
#include <Groupsock.hh>
#include <GroupsockHelper.hh>

#include "mycommon.h"
#include "sourcemanager.h"
#include "ElcRTSPClient.h"
#include "mpeg4liveservermediasubsession.h"
#include "imageoverlaytext.h"
#include "vostype.h"

class ElcRTSPServer
{
public:
	ElcRTSPServer(int ourPort = 554,
			UserAuthenticationDatabase* authDatabase = NULL, unsigned reclamationTestSeconds = 65);
	virtual ~ElcRTSPServer();
	bool setSource(const string& url, const string& iname);
	int startStreaming(const string& url, string& outurl);
	bool initServer();
	MediaSession* findMediaSession(const string& url);
	Mpeg4LiveServerMediaSubSession* findMediaSubSession(const string& url);
	RTSPServer* getCoreRTSPServer() const {return rtspServer;}
	int stopStreaming();
	void close();
	bool isReady;

protected:
	static void startThread(void* usr);
	void doThread();

private:
	// some variable here
	RTSPServer* rtspServer;
	UsageEnvironment* mEnv;
	TaskScheduler* mTask;
	std::thread* mThread;
	//std::unique_ptr<std::thread> mThread;
	std::recursive_mutex mLocker;
	std::recursive_mutex waitLocker;
	bool isWait;
	string mUrl;
	string mName;
	string mOutUrl;
	ServerMediaSession* mediaSession;
	Mpeg4LiveServerMediaSubSession* mediaSubSession;
	char loopControl;
	recursive_mutex loopLocker;
	RTPSink* videoSink;
	RTCPInstance* rtcp;
	MPEG4VideoStreamDiscreteFramer* videoSource;
	Groupsock* rtpGroupsock;
	Groupsock* rtcpGroupsock;
	UserAuthenticationDatabase* mAuthDatabase;
	unsigned mReclamationTestSeconds;
	int mOurPort;
	//vector<char> loopControl;
	int findSource(const string& url); // return the posion of media session and media subsession
};

#endif /* ELCRTSPSERVER_H_ */
