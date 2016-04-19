/*
 * h264liveservermediasession.h
 *
 *  Created on: Jul 17, 2014
 *      Author: xyz
 */

#ifndef H264LIVESERVERMEDIASESSION_H_
#define H264LIVESERVERMEDIASESSION_H_

#include <liveMedia.hh>
#include <string>
#include <vector>

class H264FileMediaSubsession:public FileServerMediaSubsession
{
public:
	static H264FileMediaSubsession*	 createNew(UsageEnvironment& env, std::vector<std::string> fileList,
			                                   std::string timeStart, std::string timeStop, std::string speed, Boolean reuseFirstSource);

    void checkForAuxSDPLine1();
    void afterPlayingDummy1();
protected:
    H264FileMediaSubsession(UsageEnvironment& env, std::vector<std::string> fileList,
    		                std::string timeStart, std::string timeStop, std::string speed,Boolean reuseFirstSource);
    virtual ~H264FileMediaSubsession(void);
    void setDoneFlag() { fDoneFlag = ~0; }
protected:
    virtual char const* getAuxSDPLine(RTPSink* rtpSink, FramedSource* inputSource);
    virtual FramedSource* createNewStreamSource(unsigned clientSessionId, unsigned& estBitrate);
    virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource);
private:
    char* fAuxSDPLine;
    char fDoneFlag;
    RTPSink* fDummySink;
    std::vector<std::string> mFileList;
    std::string timeStart, timeStop, speed;
};

#endif /* H264LIVESERVERMEDIASESSION_H_ */
