/*
 * HandleThreadPoolEvent.cpp
 *
 *  Created on: Jul 10, 2014
 *      Author: binhdu
 */

#include "HandleThreadPoolEvent.h"

HandleThreadPoolEvent::HandleThreadPoolEvent()
{
	// TODO Auto-generated constructor stub
	mHMainThread = NULL ;
	mUserData = NULL ;
	isRunningFlag = false ;

}

HandleThreadPoolEvent::~HandleThreadPoolEvent()
{
	// TODO Auto-generated destructor stub
	isRunningFlag = false ;
	mHMainThread->join();

	if(mHMainThread)
	{
		delete mHMainThread;
		mHMainThread = NULL;
	}

	if(mUserData)
	{
		//delete mUserData ;
		mUserData = NULL;
	}

	if(mOnAddJob)
		mOnAddJob = NULL;

	if(mOnRemoveJob)
		mOnRemoveJob = NULL;

}




bool HandleThreadPoolEvent::PostEvent(ThreadPoolEvent* pThreadPoolEvent)
{
	mListEventMutex.lock();
	mListEvent.push_back(pThreadPoolEvent);
	mListEventMutex.unlock();

	return true ;
};

void HandleThreadPoolEvent::Run()
{
	isRunningFlag = true;
	mHMainThread = new std::thread(MainThread , this) ;
}

void HandleThreadPoolEvent::SetCallBack(void (*pOnAddJob)(ThreadJob * , void*), void (*pOnRemoveJob)(ThreadJob *, void*) , void* pUserData )
{
	mOnAddJob = pOnAddJob ;
	mOnRemoveJob = pOnRemoveJob ;
	mUserData = pUserData ;
};


void HandleThreadPoolEvent::MainThread(void* param)
{
	HandleThreadPoolEvent *MyClass = (HandleThreadPoolEvent*)param;
	while(MyClass->isRunningFlag)
	{
		if(MyClass->mListEvent.empty())
		{
			//sleep 1 millisecond
			std::this_thread::sleep_for(std::chrono::milliseconds(1)) ;
			//std::this_thread::sleep_for(std::chrono::milliseconds(1));

		}
		else
		{
			ThreadPoolEvent *event = MyClass->mListEvent.front();
			MyClass->mListEvent.erase(MyClass->mListEvent.begin()) ;

			ThreadJob *job = event->mEventData ;

			switch(event->mTypeEvent)
			{

			case ThreadPoolEvent::ADD :
				//std::cout << __FILE__ << "(" <<__LINE__ << ") [MainThread] add job:" << job << std::endl ;
				MyClass->mOnAddJob(job , MyClass->mUserData);
				break;

			case ThreadPoolEvent::REMOVE :
				//std::cout << __FILE__ << "(" <<__LINE__ << ") [MainThread] remove job:" << job << std::endl ;
				MyClass->mOnRemoveJob(job, MyClass->mUserData);
				break;
			default:
				break;

			}
		}
	}

	std::cout << __FILE__ << "(" <<__LINE__ << ") [MainThread] Out :" << MyClass << std::endl ;
};



ThreadPoolEvent::ThreadPoolEvent(ThreadJob *pEventData, int pTypeEvent):mEventData(pEventData)
{
	//std::cout << __FILE__ << "(" <<__LINE__ << ") [ThreadPoolEvent] job :" << mEventData << std::endl ;
	mTypeEvent = pTypeEvent ;
};


ThreadPoolEvent::~ThreadPoolEvent()
{
	std::cout << __FILE__ << "(" <<__LINE__ << ") [~ThreadPoolEvent] :" << this << std::endl ;
	if(mEventData != NULL)
	{
		delete mEventData ;
		mEventData = NULL ;
	}

	mTypeEvent = -1 ;
};
