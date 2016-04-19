/*
 * mpeg4filemediasubsession.cpp
 *
 *  Created on: 7 Aug, 2014
 *      Author: cuonglm
 */
/*
 * h264liveserversediasession.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: xyz
 */

#include "mpeg4filemediasubsession.h"
#include <iostream>
#include "mpeg4filesource.h"

using namespace std;

Mpeg4FileMeidaSubSession* Mpeg4FileMeidaSubSession::createNew(UsageEnvironment& env, std::vector<std::string> fileList,
		                                                    std::string ts, std::string te, std::string speed, Boolean reuseFirstSource)
{
	cout<<"create new Mpeg4FileMeidaSubSession"<<endl;
    return new Mpeg4FileMeidaSubSession(env, fileList, ts, te, speed, reuseFirstSource);
}

Mpeg4FileMeidaSubSession::Mpeg4FileMeidaSubSession(UsageEnvironment& env, std::vector<std::string> fileList, std::string ts, std::string te, std::string sp, Boolean reuseFirstSource)
:FileServerMediaSubsession(env, fileList[0].c_str(), reuseFirstSource),
fAuxSDPLine(NULL), fDoneFlag(0), fDummySink(NULL)
{
	mFileList = fileList;
	timeStart = ts;
	timeStop = te;
	speed = sp;
}


Mpeg4FileMeidaSubSession::~Mpeg4FileMeidaSubSession(void)
{
    delete[] fAuxSDPLine;
}


static void afterPlayingDummy(void* clientData)
{
	Mpeg4FileMeidaSubSession *session = (Mpeg4FileMeidaSubSession*)clientData;
    session->afterPlayingDummy1();
}

void Mpeg4FileMeidaSubSession::afterPlayingDummy1()
{
    envir().taskScheduler().unscheduleDelayedTask(nextTask());
    setDoneFlag();
}

static void checkForAuxSDPLine(void* clientData)
{
	Mpeg4FileMeidaSubSession* session = (Mpeg4FileMeidaSubSession*)clientData;
    session->checkForAuxSDPLine1();
}

void Mpeg4FileMeidaSubSession::checkForAuxSDPLine1()
{
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

char const* Mpeg4FileMeidaSubSession::getAuxSDPLine(RTPSink* rtpSink, FramedSource* inputSource)
{
    if(fAuxSDPLine != NULL) {
    	std::cout<<fAuxSDPLine<<std::endl;
		return fAuxSDPLine;
	}
    if(fDummySink == NULL) {
        fDummySink = rtpSink;
        Boolean result = fDummySink->startPlaying(*inputSource, afterPlayingDummy, this);
        checkForAuxSDPLine(this);
    }

    std::cout<<fAuxSDPLine<<std::endl;
    envir().taskScheduler().doEventLoop(&fDoneFlag);
    return fAuxSDPLine;
}

FramedSource* Mpeg4FileMeidaSubSession::createNewStreamSource(unsigned clientSessionID, unsigned& estBitRate)
{
    // Based on encoder configuration i kept it 90000
    estBitRate = 90000;
    Mpeg4FileSource *source = Mpeg4FileSource::createNew(envir(), mFileList, timeStart, timeStop, speed);
    //ManageFileSource::getSingleton()->addFileSource(source);
    // are you trying to keep the reference of the source somewhere? you shouldn't.
    // Live555 will create and delete this class object many times. if you store it somewhere
    // you will get memory access violation. instead you should configure you source to always read from your data source
    return MPEG4VideoStreamDiscreteFramer::createNew(envir(),source);
}

RTPSink* Mpeg4FileMeidaSubSession::createNewRTPSink(Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource)
{
    return MPEG4ESVideoRTPSink::createNew(envir(), rtpGroupsock, 96);
}

//void Mpeg4FileMeidaSubSession::pauseStream(unsigned clientSessionId, void* streamToken)
//{
//	Mpeg4FileSource* fileSource = (Mpeg4FileSource*) streamToken;
//	//fileSource->pauseStream();
//}

//void Mpeg4FileMeidaSubSession::closeStreamSource(FramedSource* inputSource)
//{
//	//std::cout<<"call closeStreamSource:   "<<inputSource<<std::endl;
//	Mpeg4FileSource* fileSource = (Mpeg4FileSource*) inputSource;
//	//fileSource->closeStream();
//	//ManageFileSource::getSingleton()->removeFileSource(inputSource);
//	OnDemandServerMediaSubsession::closeStreamSource(inputSource);
//}



