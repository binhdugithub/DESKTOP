/*
 * mpeg4liveservermediasubsession.h
 *
 *  Created on: Jul 21, 2014
 *      Author: xyz
 */

#ifndef MPEG4LIVESERVERMEDIASUBSESSION_H_
#define MPEG4LIVESERVERMEDIASUBSESSION_H_

#include <live555/liveMedia.hh>
#include <live555/OnDemandServerMediaSubsession.hh>
#include  "mpeg4livesource.h"
#include "mycommon.h"

class Mpeg4LiveServerMediaSubSession:public OnDemandServerMediaSubsession
{
public:
    static Mpeg4LiveServerMediaSubSession* createNew(UsageEnvironment& env, Boolean reuseFirstSource, const string& url);
    void checkForAuxSDPLine1();
    void afterPlayingDummy1();
    void setSource(const string& url){ mUrl = url;}
    string getSource() const {return mUrl;}
protected:
    Mpeg4LiveServerMediaSubSession(UsageEnvironment& env, bool reuseFirstSource, const string& url);
    virtual ~Mpeg4LiveServerMediaSubSession(void);
    void setDoneFlag() { fDoneFlag = ~0; }
protected:
    virtual char const* getAuxSDPLine(RTPSink* rtpSink, FramedSource* inputSource);
    virtual FramedSource* createNewStreamSource(unsigned clientSessionId, unsigned& estBitrate);
    virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource);
private:
    char* fAuxSDPLine;
    char fDoneFlag;
    RTPSink* fDummySink;
    RTPSink* mySink;
    Mpeg4LiveSource* mSource;

    string mUrl;
    vector<int> socketConnection;
};

#endif /* MPEG4LIVESERVERMEDIASUBSESSION_H_ */
