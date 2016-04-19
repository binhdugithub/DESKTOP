/*
 * x264livesource.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: xyz
 */

#include "h264filesource.h"
#include <iostream>
#include "commondef.h"



//EventTriggerId H264FileSource::eventTriggerId = 0;
extern TaskScheduler* scheduler;
#define H323_H264_MTU 1402

H264FileSource* H264FileSource::createNew(UsageEnvironment& env, std::vector<std::string> listFile, std::string ts, std::string te, std::string speed)
{
	std::cout<<"createNew H264FileSource"<<std::endl;
    return new H264FileSource(env, listFile, ts, te, speed);
}

H264FileSource::H264FileSource(UsageEnvironment& env, std::vector<std::string> listFile, std::string ts, std::string te, std::string speed)
:FramedSource(env)
{
	eventTriggerId = 0;
    mCurrentPacket = NULL;
    mTimeLastReceive = mTimeStartReceive = mDurationCheck = 0;
    mTimeStartTransmit = mTimeLastTransmit = 0;
    mFPS = frameNumber = numFrameLast = 0;
    mListFile = listFile;
    timeStart = ts;
    timeStop = te;
    mSpeed = speed;
    count = 0;
    fileNumber = 0;
    isExit = false;
    mAddr = getAddrPoint((void*)this);
    std::cout<<"mAddr " <<mAddr<<std::endl;
	mRTPDataToSend = new unsigned char[H323_H264_MTU];
	fMaxSize = H323_H264_MTU;
    init();

    if(pthread_create(&mThread, NULL, triggerEvent, (void*)this))  {
    	std::cout<<"ERROR: init thread triggerEvent error"<<std::endl;
    	LOG_INFO("ERROR: init thread triggerEvent error");
    	return;
    }
}


H264FileSource::~H264FileSource(void)
{
    isExit = true;
    pthread_join(mThread, NULL);
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

    if(mRTPDataToSend) {
    	delete[] mRTPDataToSend;
    	mRTPDataToSend = NULL;
    }
    LOG_INFO(mAddr<<" Finish Decontructor H264FileSource");
}

void H264FileSource::init()
{

	mFileReader = new FileHandler();
	mFileReader->OpenFile(mListFile[0].c_str());
    if(mListFile.size() == 1)
    	isEndFile = true;

    if(mSpeed !="")
	{
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
	timeCheck = (1000000/mFPS) /speed;
	//std::cout<<"timeCheck="<<timeCheck<<std::endl;
	//seek pointFile to time start
	durationStart = getPosStart();
	LOG_INFO(mAddr<<" durationStart : "<<int2string(durationStart));
	durationStop = getPosStop();
	LOG_INFO(mAddr <<" durationStop : "<<int2string(durationStop));
	if(durationStart > 0) {
		mFileReader->SeekTo(durationStart * 1000000);
	}

    if(durationStop > 0)
    {
    	if(mListFile.size()==1)
			numFrameLast = mFPS * (durationStop - durationStart + 2) ;  // tam thoi fix de test
    	else
			numFrameLast = mFPS * (durationStop + 2);

		LOG_INFO("NumberFrameLast = "<<int2string(numFrameLast));
    }
    else
    	numFrameLast = -1;

	if(eventTriggerId == 0) {
		eventTriggerId = envir().taskScheduler().createEventTrigger(deliverFrame0);
	}
}


int H264FileSource::getPosStart()
{
	char firtName[200];
	strcpy(firtName, mListFile[0].c_str());
	splitvt = split(firtName, "/");

	std::string tfirt = splitvt[splitvt.size() -1];
	//std::cout<<"firtName:               "<<firtName<<std::endl;
	std::cout << "tfirt:" << tfirt << std::endl;
	LOG_INFO("tfirt: " << tfirt);
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

	std::cout <<"timstart:" << timeStart << std::endl;
	std::cout <<"First time =" << atoi(hourf) << ":" << atoi(minusf) << ":" << atoi(secondf) << " Start time =" << atoi(hours) <<":" << atoi(minuss) << ":" << atoi(seconds) << std::endl;
	LOG_INFO("First time =" << atoi(hourf) << ":" << atoi(minusf) << ":" << atoi(secondf) << " Start time =" << atoi(hours) <<":" << atoi(minuss) << ":" << atoi(seconds));

	unsigned int tStart = atoi(hours)*3600 + atoi(minuss)*60 + atoi(seconds);
	int durationStart = tStart - tFisrt;
	return durationStart;

}

int H264FileSource::getPosStop() {
	char lastName[200];
	strcpy(lastName, mListFile[mListFile.size() -1].c_str());
	splitvt = split(lastName, "/");

	std::string tlast = splitvt[splitvt.size() -1];
	std::cout<<"tlast:    "<<tlast<<std::endl;
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

	std::cout <<"timstop:" << timeStop << std::endl;
	std::cout <<"Stop time =" << atoi(hourf) << ":" << atoi(minusf) << ":" << atoi(secondf) << " Start time =" << atoi(hours) <<":" << atoi(minuss) << ":" << atoi(seconds) << std::endl;
	LOG_INFO("Stop time =" << atoi(hourf) << ":" << atoi(minusf) << ":" << atoi(secondf) << " Start time =" << atoi(hours) <<":" << atoi(minuss) << ":" << atoi(seconds) );

	unsigned int tStop = atoi(hours)*3600 + atoi(minuss)*60 + atoi(seconds);
	int durationStop = tStop - tLast;
    return durationStop;

}

int H264FileSource::getSpeed()
{
	char* buffer = new char[20];
	strcpy(buffer, mSpeed.c_str());
	splitvt.clear();
    splitvt = split(buffer, "=");
    int speed = atoi(splitvt[1].c_str());
    delete[] buffer;
    return speed;
}

double H264FileSource::get_microsecond()
{
	struct timeval tv;
	gettimeofday(&tv, (struct timezone*)0);
	double ret = tv.tv_usec;
	ret += ((unsigned)tv.tv_sec)*1000000;
	return ret;
}


void H264FileSource::fragment()
{
	if (mTimeStartTransmit == 0)
		mTimeStartTransmit = get_microsecond();

	if (!mCurrentPacket)
	{
		mCurrentPacket = mFileReader->ReadFrame();
		if((fileNumber == mListFile.size()-1) && numFrameLast > 0)
		{
			frameNumber++;
			if(frameNumber > numFrameLast)
			{
				LOG_INFO("Catch pos stop, teardown session");
				isExit = true;
				return;
			}
		}

		if (!mCurrentPacket)
		{
			fileNumber++;
			if(fileNumber >mListFile.size()-1)
				return;
			if(mFileReader)
			{
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
			mTimeLastReceive = mTimeLastTransmit = 0;
		}
	}

	if((get_microsecond() - mTimeStartTransmit) >= mDurationCheck)
	{

		if (mFileReader->IsVideoStream(mCurrentPacket->stream_index))
		{

			//std::cout << "Time to send frame. mTimeStartTransmit = " << mTimeStartTransmit << " current = " << get_microsecond() << " duration check = " << mDurationCheck <<std::endl;
			if(mCurrentPacket->flags & 0x0001)
			{
				//std::cout<<"push sps & pps"<<std::endl;
				AVPacket* mSPS = new AVPacket ;
				AVPacket* mPPS = new AVPacket;
				mSPS->size = mFileReader->GetSPSLen();
				mSPS->data = new uint8_t[mSPS->size];
				memcpy(mSPS->data, mFileReader->GetSPS(),mFileReader->GetSPSLen());
				dataQueue.push(mSPS);

				mPPS->size = mFileReader->GetPPSLen();
				mPPS->data = new uint8_t[mPPS->size];
				memcpy(mPPS->data, mFileReader->GetPPS(),mFileReader->GetPPSLen());
				dataQueue.push(mPPS);
			}

			if((mCurrentPacket->size - 4) <= H323_H264_MTU)
			{
				AVPacket* mData = new AVPacket;
				mData->size = mCurrentPacket->size -4;
				mData->data = new uint8_t[mData->size];
				memcpy(mData->data , mCurrentPacket->data + 4, mCurrentPacket->size -4);
				//LOG_INFO("push data < 1402 to queue");
				dataQueue.push(mData);
			}
			else if((mCurrentPacket->size - 4) > H323_H264_MTU)
			{   //std::cout << "Need fragment" << std::endl;
				const unsigned long i_count = (mCurrentPacket->size - 4 - 1 + H323_H264_MTU - 2 - 1) / (H323_H264_MTU - 2);
				unsigned long i;

				const unsigned char* p_data = mCurrentPacket->data + 4;
				int i_data = mCurrentPacket->size - 4;

				unsigned char i_nal_hdr = p_data[0];
				unsigned char i_nal_type = i_nal_hdr & 0x1F;

				p_data += 1;
				i_data -= 1;

				for(i=0; i < i_count; i++)
				{
					const int i_payload = (i_data > H323_H264_MTU - 2) ? (H323_H264_MTU - 2) : i_data;
					// FU indicator
					mRTPDataToSend[0] = 0x00 | (i_nal_hdr & 0x60) | 28;
					// FU header
					mRTPDataToSend[1] = (i==0?0x80:0x00)|((i==i_count-1)?0x40:0x00)|i_nal_type;
					memcpy(mRTPDataToSend+2, p_data, i_payload);

					AVPacket* mData = new AVPacket;
					mData->size = i_payload + 2;
					mData->data = new uint8_t[mData->size];

					memcpy(mData->data, mRTPDataToSend, i_payload + 2);
					//LOG_INFO("push data > 1402 to queue");
					dataQueue.push(mData);

					i_data -= i_payload;
					p_data += i_payload;
				}
			}
			//mTimeLastReceive = mCurrentPacket->pts;
			mDurationCheck +=timeCheck;

		}

		mCurrentPacket = NULL;
	}
}


void H264FileSource::deliverFrame0(void* clientData)
{
    ((H264FileSource*)clientData)->doGetNextFrame();
}

void H264FileSource::doGetNextFrame()
{
	if(dataQueue.empty() == true)
	{
		fragment();
		if(isExit==true)
		{
			LOG_INFO(mAddr<<" close source and send TearDown");
			handleClosure();
			return;
		}

		if(dataQueue.empty() == true)
		{
			return;
		}

		deliverFrame();
	}
	else
	{
		deliverFrame();
	}

}

void H264FileSource::deliverFrame()
{
	if (!isCurrentlyAwaitingData())
		return; // we're not ready for the data yet

	AVPacket* pkt = dataQueue.front();
	u_int8_t* newFrameDataStart = pkt->data;
	unsigned newFrameSize = pkt->size;

	//std::cout << "Deliver frame time =" << get_microsecond() << std::endl;
	// Deliver the data here:
	if (newFrameSize > fMaxSize)
	{
		std::cout << "Framesize = " << newFrameSize << " FrameMax: " << fMaxSize << std::endl;
		fFrameSize = fMaxSize;
		fNumTruncatedBytes = newFrameSize - fMaxSize;
	}
	else
	{
		fFrameSize = newFrameSize;
	}

	gettimeofday(&fPresentationTime, NULL); // If you have a more accurate time - e.g., from an encoder - then use that instead.
	// If the device is *not* a 'live source' (e.g., it comes instead from a file or buffer), then set "fDurationInMicroseconds" here.

	memmove(fTo, newFrameDataStart, fFrameSize);
	dataQueue.pop();
	delete pkt->data;
	pkt->data = NULL;
	delete pkt;
	static double pktcount = 0;

	// After delivering the data, inform the reader that it is now available:
	FramedSource::afterGetting(this);
	//mTimeLastTransmit = get_microsecond();
}

void* H264FileSource::triggerEvent(void* pVoid)
{
	H264FileSource* pThis = (H264FileSource*)pVoid;
	while(pThis->isExit ==false)
	{
		if(scheduler !=NULL) {
			scheduler->triggerEvent(pThis->eventTriggerId , pThis);
		}
		usleep(1000);
	}
}
