/*
 * mpeg4filesource.cpp
 *
 *  Created on: 7 Aug, 2014
 *      Author: cuonglm
 */

#include "mpeg4filesource.h"
#include <iostream>
#include "commondef.h"



//EventTriggerId Mpeg4FileSource::eventTriggerId = 0;
extern TaskScheduler* scheduler;

Mpeg4FileSource* Mpeg4FileSource::createNew(UsageEnvironment& env, std::vector<std::string> listFile, std::string ts, std::string te, std::string speed)
{
    return new Mpeg4FileSource(env, listFile, ts, te, speed);
}

Mpeg4FileSource::Mpeg4FileSource(UsageEnvironment& env, std::vector<std::string> listFile, std::string ts, std::string te, std::string speed)
:FramedSource(env)
{
	LOG_INFO("call Mpeg4FileSource::Mpeg4FileSource()");
	eventTriggerId = 0;
    mCurrentPacket = NULL;
    mTimeStartTransmit = mTimeLastTransmit = mDurationCheck = 0;
    mFPS = frameNumber = numFrameLast = 0;
    mListFile = listFile;
    timeStart = ts;
    timeStop = te;
    mSpeed = speed;
    isExit = false;
    fileNumber = 0;

    mAddr = getAddrPoint((void*)this);
    std::cout<<"mAddr " <<mAddr<<std::endl;
    init();

    if(pthread_create(&mThread, NULL, triggerEvent, (void*)this )) {
    	LOG_ERROR("ERROR: init thread triggerEvent error");
    	return;
    }
    LOG_INFO("init thread triggerEvent sucess");
}

Mpeg4FileSource::~Mpeg4FileSource(void)
{
	LOG_INFO(mAddr<<"call ~Mpeg4FileSource()");
	isExit = true;
	pthread_join(mThread, NULL);
	LOG_INFO(mAddr<<"Finish call joint thread trigger");
    envir().taskScheduler().deleteEventTrigger(eventTriggerId);
    eventTriggerId = 0;
//    while(!mFileHandlerList.empty()) {
//    	delete mFileHandlerList.front();
//    	mFileHandlerList.erase(mFileHandlerList.begin());
//    }
    if(mFileReader) {
    	delete mFileReader;
    	mFileReader = NULL;
    }

    while(!dataQueue.empty()) {
    	delete dataQueue.front()->data;
    	dataQueue.front()->data = NULL;
        delete dataQueue.front();
        dataQueue.pop();
    }

}

void Mpeg4FileSource::init()
{
//	for(mListFileItorator = mListFile.begin(); mListFileItorator != mListFile.end() ; mListFileItorator++) {
//		mFileReader = new FileHandler();
//		std::string filePath = (*mListFileItorator);
//		if(mFileReader->OpenFile(filePath.c_str()) == 0) {
//			LOG_ERROR(mAddr<<" open error in FileSource: "<<filePath);
//			continue;
//		}
//		mFileHandlerList.push_back(mFileReader);
//	}
//
//	if(mFileHandlerList.size() == 0)
//		return;
//	mFileHandlerItorator = mFileHandlerList.begin();
//	mFileReader = *mFileHandlerItorator;

	mFileReader = new FileHandler();
	mFileReader->OpenFile(mListFile[0].c_str());
    if(mListFile.size() == 1)
    	isEndFile = true;
	if(mSpeed !="")  {
		int sp = getSpeed();
		if(sp<0)
			speed = 1/double(abs(sp));
		else if(sp>0)
			speed = sp;
		else
			speed = 1;
	}
	else
		speed = 1;
	LOG_INFO(mAddr<<" Speed : "<<int2string(speed));

	mFPS = mFileReader->getFPS();
	timeCheck = (1000/mFPS) /speed;
	//seek pointFile to time start
	durationStart = getPosStart();
	LOG_INFO(mAddr<<" durationStart : "<<int2string(durationStart));
	durationStop = getPosStop();
	LOG_INFO(mAddr<<" durationStop : "<<int2string(durationStop));
	if(durationStart > 0)
		mFileReader->seekToFrame(durationStart * 1000000);


    if(durationStop > 0)  {
    	if(mListFile.size()==1)
    		numFrameLast = mFPS * (durationStop - durationStart);
    	else
			numFrameLast = mFPS * durationStop;

    	LOG_INFO("NumberFrameLast = "<<int2string(numFrameLast));
    }
    else
    	numFrameLast = -1;
	if(eventTriggerId == 0) {
		eventTriggerId = envir().taskScheduler().createEventTrigger(deliverFrame0);
	}
}


int Mpeg4FileSource::getPosStart() {
	char firtName[200];
	strcpy(firtName, mListFile[0].c_str());
	splitvt = split(firtName, "/");

	std::string tfirt = splitvt[splitvt.size() -1];
	char hourf[10], minusf[10], secondf[10];
	char hours[10], minuss[10], seconds[10];

	splitvt.clear();
	splitvt = split((char*)tfirt.c_str(), "-." );
	std::string t = splitvt[2];
	t.copy(hourf, 2,0);
	t.copy(minusf, 2,2);
	t.copy(secondf, 2,4);
	unsigned int tFisrt = atoi(hourf)*3600 + atoi(minusf)*60 + atoi(secondf);

	splitvt.clear();
	t.clear();
	char buffer[20];
	strcpy(buffer, timeStart.c_str());
	splitvt = split(buffer, "=-");
	t = splitvt[2];
	t.copy(hours, 2,0);
	t.copy(minuss, 2,2);
	t.copy(seconds, 2,4);
	unsigned int tStart = atoi(hours)*3600 + atoi(minuss)*60 + atoi(seconds);
	int durationStart = tStart - tFisrt;
	return durationStart;

}

int Mpeg4FileSource::getPosStop() {
	char lastName[200];
	strcpy(lastName, mListFile[mListFile.size() -1].c_str());
	splitvt = split(lastName, "/");

	std::string tlast = splitvt[splitvt.size() -1];
	//std::cout<<"firtName:               "<<firtName<<std::endl;
	char hourf[10], minusf[10], secondf[10];
	char hours[10], minuss[10], seconds[10];

	splitvt.clear();
	splitvt = split((char*)tlast.c_str(), "-." );
	std::string t = splitvt[2];
	t.copy(hourf, 2,0);
	t.copy(minusf, 2,2);
	t.copy(secondf, 2,4);
	unsigned int tLast = atoi(hourf)*3600 + atoi(minusf)*60 + atoi(secondf);

	splitvt.clear();
	t.clear();
	char buffer[20];
	strcpy(buffer, timeStop.c_str());
	splitvt = split(buffer, "=-");
	t = splitvt[2];
	t.copy(hours, 2,0);
	t.copy(minuss, 2,2);
	t.copy(seconds, 2,4);
	unsigned int tStop = atoi(hours)*3600 + atoi(minuss)*60 + atoi(seconds);
	int durationStop = tStop - tLast;
    return durationStop;
}

int Mpeg4FileSource::getSpeed()
{
	char* buffer = new char[20];
	strcpy(buffer, mSpeed.c_str());
	splitvt.clear();
    splitvt = split(buffer, "=");
    int speed = atoi(splitvt[1].c_str());
    delete[] buffer;
    return speed;
}
double Mpeg4FileSource::get_microsecond()
{
	struct timeval tv;
	gettimeofday(&tv, (struct timezone*)0);
	double ret = tv.tv_usec;
	ret += ((unsigned)tv.tv_sec)*1000000;
	return ret;
}


void Mpeg4FileSource::fragment()
{
	if (mTimeStartTransmit == 0)
		mTimeStartTransmit = get_microsecond();

	if (!mCurrentPacket) {
		mCurrentPacket = mFileReader->ReadFrame();
		if((fileNumber == mListFile.size()-1) && numFrameLast > 0) {
			frameNumber++;
			if(frameNumber > numFrameLast)  {
				LOG_INFO("Catch pos stop, teardown session");
				isExit = true;
				return;
			}
		}
		if (!mCurrentPacket) {
			fileNumber++;
			if(fileNumber >mListFile.size()-1)
				return;
			if(mFileReader) {
				delete mFileReader;
				mFileReader = NULL;
			}
			mFileReader = new FileHandler();
			mFileReader->OpenFile(mListFile[fileNumber].c_str());
//			if(mFileHandlerItorator != mFileHandlerList.end())	{
//				mFileReader = *mFileHandlerItorator;
			mCurrentPacket = mFileReader->ReadFrame();
			if(!mCurrentPacket)
				return;
			mTimeLastTransmit = 0;
		}
	}

	if((get_microsecond() - mTimeStartTransmit)/1000 >= mDurationCheck) {
		AVPacket* mData = new AVPacket;
		mData->size = mCurrentPacket->size;
		mData->data = new uint8_t[mData->size];
		memcpy(mData->data , mCurrentPacket->data, mCurrentPacket->size);
		dataQueue.push(mData);
		mTimeLastTransmit = get_microsecond();
		mCurrentPacket = NULL;
		mDurationCheck += timeCheck;
	}
}


void Mpeg4FileSource::deliverFrame0(void* clientData)
{
    ((Mpeg4FileSource*)clientData)->doGetNextFrame();
}

void Mpeg4FileSource::doGetNextFrame()
{
    if(dataQueue.empty() == true) {
		fragment();
		if(isExit==true) {
			LOG_INFO(mAddr<<" close source and send TearDown");
			handleClosure();
			return;
		}
		if(dataQueue.empty() == true) {
			return;
		}

		deliverFrame();
    }
    else {
    	deliverFrame();
    }
}

void Mpeg4FileSource::deliverFrame()
{
	if (!isCurrentlyAwaitingData())
		return; // we're not ready for the data yet
	AVPacket* pkt = dataQueue.front();
	u_int8_t* newFrameDataStart = pkt->data;
	unsigned newFrameSize = pkt->size;

	// Deliver the data here:
	if (newFrameSize > fMaxSize) {
		fFrameSize = fMaxSize;
		fNumTruncatedBytes = newFrameSize - fMaxSize;
	} else {
		fFrameSize = newFrameSize;
	}

	gettimeofday(&fPresentationTime, NULL); // If you have a more accurate time - e.g., from an encoder - then use that instead.
	// If the device is *not* a 'live source' (e.g., it comes instead from a file or buffer), then set "fDurationInMicroseconds" here.

	memmove(fTo, newFrameDataStart, fFrameSize);
	dataQueue.pop();
	delete pkt->data;
	pkt->data = NULL;
	delete pkt;
	//static int pktcount=0;
	//fprintf(stderr, "*********Deliver frame %d len=%d     timestamp: %d  \n", ++pktcount, fFrameSize, get_microsecond()/1000);

	// After delivering the data, inform the reader that it is now available:
	FramedSource::afterGetting(this);

}

void* Mpeg4FileSource::triggerEvent(void* pVoid)
{
	Mpeg4FileSource* pThis = (Mpeg4FileSource*)pVoid;
	while(pThis->isExit==false)  {
		if(scheduler!= NULL)  {
			scheduler->triggerEvent(pThis->eventTriggerId, pThis);
		}
		usleep(1000);
	}
}

