/*
 * mpeg4filemediasubsession.h
 *
 *  Created on: 7 Aug, 2014
 *      Author: cuonglm
 */

#ifndef MPEG4FILEMEDIASUBSESSION_H_
#define MPEG4FILEMEDIASUBSESSION_H_

#include <liveMedia.hh>
#include <string>
#include <vector>

class Mpeg4FileMeidaSubSession:public FileServerMediaSubsession
{
public:
	static Mpeg4FileMeidaSubSession*	 createNew(UsageEnvironment& env, std::vector<std::string> fileList,
			                                   std::string timeStart, std::string timeStop, std::string speed, Boolean reuseFirstSource);

    void checkForAuxSDPLine1();
    void afterPlayingDummy1();
protected:
    Mpeg4FileMeidaSubSession(UsageEnvironment& env, std::vector<std::string> fileList,
    		                std::string timeStart, std::string timeStop, std::string speed,Boolean reuseFirstSource);
    virtual ~Mpeg4FileMeidaSubSession(void);
    void setDoneFlag() { fDoneFlag = ~0; }
    virtual char const* getAuxSDPLine(RTPSink* rtpSink, FramedSource* inputSource);
    virtual FramedSource* createNewStreamSource(unsigned clientSessionId, unsigned& estBitrate);
    virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource);
//    virtual void pauseStream(unsigned clientSessionId, void* streamToken);
//    virtual void closeStreamSource(FramedSource* inputSource);
private:
    char* fAuxSDPLine;
    char fDoneFlag;
    RTPSink* fDummySink;
    std::vector<std::string> mFileList;
    std::string timeStart, timeStop, speed;


};



#endif /* MPEG4FILEMEDIASUBSESSION_H_ */
