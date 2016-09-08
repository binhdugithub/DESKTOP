/*
 * sourcemanager.h
 *
 *  Created on: Jul 15, 2014
 *      Author: xyz
 */

#ifndef SOURCEMANAGER_H_
#define SOURCEMANAGER_H_

#include <liveMedia/liveMedia.hh>
#include <UsageEnvironment.hh>
#include <BasicUsageEnvironment.hh>
#include "vostype.h"
#include "mycommon.h"
#include "dp/yo_singleton.h"

class ElcRTSPClient;
class ElcRTSPServer;
class ImageOverlayText;
class MulticastProcessing;

const string dbfile = "./dbbackup.txt";

class SourceManager : public yo::common::YoSingleton<SourceManager>
{

public:


	SourceManager();
	virtual ~SourceManager();


	int addSource(const std::string& url, const std::string& name, std::string& outUrl);
	int addSource(ElcRTSPClient* rtspClient);
	int removeSource(const std::string& url);
	int removeSource(ElcRTSPClient* rtspClient);
	int start(const std::string& url, string& output);
	int stop(const std::string& url);
	int findSource(const std::string& url);
	ElcRTSPClient* findClient(const std::string& url);
	ElcRTSPClient* findClient(void* rtspClient);
	ImageOverlayText* findOverlay(const std::string& ip);

	int removeAllSource();
	int stopAllSource();
	int startAllSource();
	int restartAllSource();
	int loadSource();

	// write current status to file when DB error
	void writeCurrentStatus();
	// notify to all overlay when change text position

	RTSPServer* getGlobalRtspServerTest();

protected:
	// auto-generate port, from 8554-8600 :)
	int autoSellectPort();
	void createSource();
	int createSource(const string& url);
	bool checkAvailablePort(int port);

	bool checkRtspUrl(const string& url);
	int findReuseSource();

private:
	std::vector<ElcRTSPClient*> mRtspClient;
	std::vector<ElcRTSPServer*> mRtspServer;
	ElcRTSPServer *mRTSPServer;
	std::vector<ImageOverlayText*> mVideoOverlay;
	std::vector<int> serverPort;
	// from database
	std::vector<string> camip;
	std::vector<string> inputurl; // = inputurl
	std::vector<string> inputname;
	std::vector<string> username;
	std::vector<string> password;
	std::vector<string> status;
	std::vector<string> framewidth;
	std::vector<string> frameheight;
	std::vector<string> framerate;
	std::vector<string> codec;
	std::vector<string> outputurl;
	MulticastProcessing* multicastProc;

};

#endif /* SOURCEMANAGER_H_ */
