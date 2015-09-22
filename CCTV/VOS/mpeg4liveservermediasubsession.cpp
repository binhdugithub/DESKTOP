/*
 * mpeg4liveservermediasubsession.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: xyz
 */

#include "mpeg4liveservermediasubsession.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

Mpeg4LiveServerMediaSubSession* Mpeg4LiveServerMediaSubSession::createNew(UsageEnvironment& env, Boolean reuseFirstSource, const string& url)
{
	//cout<<"create new Mpeg4LiveServerMediaSubSession: env = "<<&env<<endl;
	LOG_INFO("Mpeg4LiveServerMediaSubSession::createNew -env="<<&env);
    return new Mpeg4LiveServerMediaSubSession(env, reuseFirstSource, url);
}

Mpeg4LiveServerMediaSubSession::Mpeg4LiveServerMediaSubSession(UsageEnvironment& env, bool reuseFirstSource, const string& url):OnDemandServerMediaSubsession(env,reuseFirstSource),fAuxSDPLine(NULL), fDoneFlag(0), fDummySink(NULL)
{
	socketConnection = vector<int>();
	mUrl = url;
	mSource = NULL;
}


Mpeg4LiveServerMediaSubSession::~Mpeg4LiveServerMediaSubSession(void)
{
	afterPlayingDummy1();
	usleep(200*1000);
	//mySink->stopPlaying();
	if(!socketConnection.empty()) // shutdown all socket
	{
		for(size_t i = 0; i< socketConnection.size(); ++i)
		{
			//cout<<"shoutdown socket "<<i<<endl;
			shutdown(socketConnection[i], SHUTDOWN_DEFAULT);
		}
	}
	//Medium::close(mySink);
	//mSource->closeSource();
	//Medium::close(mSource);
    delete[] fAuxSDPLine;
    //Medium::close(mSource);
    //cout<<"======================= I am end of constructor ..."<<endl;
    //MPEG4ESVideoRTPSink::close(envir(), );
}


static void afterPlayingDummy(void* clientData)
{
	Mpeg4LiveServerMediaSubSession *session = (Mpeg4LiveServerMediaSubSession*)clientData;
    session->afterPlayingDummy1();
}

void Mpeg4LiveServerMediaSubSession::afterPlayingDummy1()
{
	LOG_INFO("Mpeg4LiveServerMediaSubSession::afterPlayingDummy1 OK");
    envir().taskScheduler().unscheduleDelayedTask(nextTask());
    setDoneFlag();
}

static void checkForAuxSDPLine(void* clientData)
{
	Mpeg4LiveServerMediaSubSession* session = (Mpeg4LiveServerMediaSubSession*)clientData;
    session->checkForAuxSDPLine1();
}

void Mpeg4LiveServerMediaSubSession::checkForAuxSDPLine1()
{
    char const* dasl;
    if(fAuxSDPLine != NULL)
    {
        setDoneFlag();
    }
    else if(fDummySink != NULL && (dasl = fDummySink->auxSDPLine()) != NULL)
    {
        fAuxSDPLine = strDup(dasl);
        fDummySink = NULL;
        setDoneFlag();
    }
    else
    {
        int uSecsDelay = 100000;
        nextTask() = envir().taskScheduler().scheduleDelayedTask(uSecsDelay, (TaskFunc*)checkForAuxSDPLine, this);
    }
}

char const* Mpeg4LiveServerMediaSubSession::getAuxSDPLine(RTPSink* rtpSink, FramedSource* inputSource)
{
	LOG_INFO("Mpeg4LiveServerMediaSubSession::getAuxSDPLine -rtpSink="<<rtpSink<<" -sdpline="<<fAuxSDPLine);
    if(fAuxSDPLine != NULL) return fAuxSDPLine;
    if(fDummySink == NULL)
    {
        fDummySink = rtpSink;
        fDummySink->startPlaying(*inputSource, afterPlayingDummy, this);
        checkForAuxSDPLine(this);
    }

    envir().taskScheduler().doEventLoop(&fDoneFlag);
    return fAuxSDPLine;
}

FramedSource* Mpeg4LiveServerMediaSubSession::createNewStreamSource(unsigned clientSessionID, unsigned& estBitRate)
{
 	//cout<<"createNewStreamSource"<<endl;
	LOG_INFO("Mpeg4LiveServerMediaSubSession::createNewStreamSource -sessionID="<<clientSessionID);
    //estBitRate = 1024*1000/2 + 100*1024/2;
	estBitRate = 1024*1000;
    mSource = Mpeg4LiveSource::createNew(envir(), mUrl);
    Boolean leavePresentationTimesUnmodified = false;
    FramedSource *source = MPEG4VideoStreamDiscreteFramer::createNew(envir(), mSource, leavePresentationTimesUnmodified);
    return source;

}

RTPSink* Mpeg4LiveServerMediaSubSession::createNewRTPSink(Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource)
{
	//cout<<"createNewRTPSink"<<endl;
	LOG_INFO("Mpeg4LiveServerMediaSubSession::createNewRTPSink -socketnumber="<<rtpGroupsock->socketNum()<<" -clientport="<<rtpGroupsock->port().num());
	socketConnection.push_back(rtpGroupsock->socketNum());
	//rtpGroupsock->ttl()
	//cout<<"Socket number: "<<rtpGroupsock->socketNum()<<" Client IP: "<<inet_ntoa(rtpGroupsock->sourceFilterAddress())<<" Client port: "<<rtpGroupsock->port().num()<<endl;
    return mySink = MPEG4ESVideoRTPSink::createNew(envir(), rtpGroupsock, 96/*rtpPayloadTypeIfDynamic*/);
}
