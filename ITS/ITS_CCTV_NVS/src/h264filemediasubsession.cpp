/*
 * h264liveserversediasession.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: xyz
 */

#include "h264filemediasubsession.h"
#include <iostream>
#include  "h264filesource.h"

using namespace std;


static void afterPlayingDummy(void* clientData)
{
	std::cout<<"afterPlayingDummy"<<std::endl;
	LOG_INFO("afterPlayingDummy");

	H264FileMediaSubsession *session = (H264FileMediaSubsession*)clientData;
    session->afterPlayingDummy1();
}

void H264FileMediaSubsession::afterPlayingDummy1()
{
	std::cout<<"afterPlayingDummy1"<<std::endl;
	LOG_INFO("afterPlayingDummy1");

    envir().taskScheduler().unscheduleDelayedTask(nextTask());
    setDoneFlag();
}

static void checkForAuxSDPLine(void* clientData)
{
	std::cout<<"checkForAuxSDPLine"<<std::endl;
	LOG_INFO("checkForAuxSDPLine");

	H264FileMediaSubsession* session = (H264FileMediaSubsession*)clientData;
    session->checkForAuxSDPLine1();
}

void H264FileMediaSubsession::checkForAuxSDPLine1()
{
	std::cout<<"checkForAuxSDPLine1"<<std::endl;
	LOG_INFO("checkForAuxSDPLine1");

    char const* dasl;
    if(fAuxSDPLine != NULL) {
        setDoneFlag();
    }
    else if(fDummySink != NULL && (dasl = fDummySink->auxSDPLine()) != NULL) {
        fAuxSDPLine = strDup(dasl);
        fDummySink = NULL;
        setDoneFlag();
    }
    else {
        int uSecsDelay = 100000;
        nextTask() = envir().taskScheduler().scheduleDelayedTask(uSecsDelay, (TaskFunc*)checkForAuxSDPLine, this);
    }
}


H264FileMediaSubsession::H264FileMediaSubsession(UsageEnvironment& env, std::vector<std::string> fileList, std::string ts, std::string te, std::string sp, Boolean reuseFirstSource)
:FileServerMediaSubsession(env, fileList[0].c_str(), reuseFirstSource),
fAuxSDPLine(NULL), fDoneFlag(0), fDummySink(NULL)
{
	mFileList = fileList;
	timeStart = ts;
	timeStop = te;
	speed = sp;
}


H264FileMediaSubsession::~H264FileMediaSubsession(void)
{
    delete[] fAuxSDPLine;
}


H264FileMediaSubsession* H264FileMediaSubsession::createNew(UsageEnvironment& env, std::vector<std::string> fileList,
		                                                    std::string ts, std::string te, std::string speed, Boolean reuseFirstSource)
{
	cout<<"Create new H264FileMediaSubsession"<<endl;
	LOG_INFO("Create new H264FileMediaSubsession");

    return new H264FileMediaSubsession(env, fileList, ts, te, speed, reuseFirstSource);
}


RTPSink* H264FileMediaSubsession::createNewRTPSink(Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource)
{
	std::cout<<"createNewRTPSink"<<std::endl;
	LOG_INFO("createNewRTPSink");

    return H264VideoRTPSink::createNew(envir(), rtpGroupsock, 96);
}


char const* H264FileMediaSubsession::getAuxSDPLine(RTPSink* rtpSink, FramedSource* inputSource)
{
	std::cout<<"getAuxSDPLine"<<std::endl;
	LOG_INFO("getAuxSDPLine");

    if(fAuxSDPLine != NULL) {
    	std::cout<<fAuxSDPLine<<std::endl;
		return fAuxSDPLine;
	}
    if(fDummySink == NULL) {
        fDummySink = rtpSink;
        fDummySink->startPlaying(*inputSource, afterPlayingDummy, this);
        checkForAuxSDPLine(this);
    }

    envir().taskScheduler().doEventLoop(&fDoneFlag);
    std::cout<<"fAuxSDPLine"<<fAuxSDPLine<<std::endl;
    return fAuxSDPLine;
}



FramedSource* H264FileMediaSubsession::createNewStreamSource(unsigned clientSessionID, unsigned& estBitRate)
{
	cout<<"createNewStreamSource"<<endl;
	LOG_INFO("createNewStreamSource");

    // Based on encoder configuration i kept it 90000
    estBitRate = 90000;
    H264FileSource *source = H264FileSource::createNew(envir(), mFileList, timeStart, timeStop, speed);
    // are you trying to keep the reference of the source somewhere? you shouldn't.
    // rLive555 will create and delete this class object many times. if you store it somewhere
    // you will get memory access violation. instead you should configure you source to always read from your data source
    return H264VideoStreamDiscreteFramer::createNew(envir(),source);
}


