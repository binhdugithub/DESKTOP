/*
 * ThreadManager.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: binhdu
 */

#include "ThreadManager.h"
#include "unistd.h"
#include <iostream>



ThreadManager::ThreadManager()
{
	// TODO Auto-generated constructor stub
	mHandleThreadPoolEvent = new HandleThreadPoolEvent();
	mHandleThreadPoolEvent->SetCallBack(&OnAddJob, &OnRemoveJob, this) ;
	mHandleThreadPoolEvent->Run();
}

ThreadManager::~ThreadManager()
{
	// TODO Auto-generated destructor stub
	std::cout << __FILE__ << ": " << __LINE__ << " Destroycontructor of ThreadManager"  << std::endl;
	while(!mListThreadObject.empty())
	{
		delete mListThreadObject.front();
		mListThreadObject.erase(mListThreadObject.begin());
	}

	if(mHandleThreadPoolEvent)
	{
		delete mHandleThreadPoolEvent;
		mHandleThreadPoolEvent = NULL ;
	}
}


unsigned int ThreadManager::NumCPU()
{
	unsigned concurrentThreadSupported = std::thread::hardware_concurrency();
	if(!concurrentThreadSupported)
		return sysconf(_SC_NPROCESSORS_ONLN) * 2 ;
	else
		return concurrentThreadSupported;
};

bool ThreadManager::InitDefault()
{
	int lCpu = NumCPU();
	std::cout << __FILE__ << __LINE__ << " Value of NumCPU :" << lCpu << std::endl;

	if(lCpu <= 0)
	{
		assert(0);
		return false ;
	}

	for(int i= 0 ; i < lCpu ; i++)
	{
		//mListThreadObject.push_back(new ThreadObject()) ;
		AddObject(new ThreadObject());
	}

	return true;
};


bool ThreadManager::AddObject(ThreadObject* pObj)
{
	mListThreadObject.push_back(pObj) ;
	return true;
}

bool ThreadManager::AddJob(ThreadJob* pJob)
{
	if(mListThreadObject.empty())
	{
		std::cout << __FILE__ << "(" <<__LINE__ << ") mListeThreadObject empty !" << std::endl ;
		return false ;
	}

	ThreadObject *tempThreadObject = NULL;
	std::size_t tempSize = std::string::npos ;

	for(auto it = mListThreadObject.begin() ; it != mListThreadObject.end() ; it++)
	{
		if(tempSize > (*it)->GetSize())
		{
			tempSize = (*it)->GetSize();
			tempThreadObject = *it ;
		}
	}

	if(tempThreadObject == NULL)
	{
		std::cout << __FILE__ << "(" <<__LINE__ << ") Add job fail !" << std::endl ;
		return false ;
	}
	else
	{
		std::cout << __FILE__ << " (" << __LINE__ << " ) Add job :" << pJob  << std::endl;
		pJob->isRunningFlag = true;
		tempThreadObject->AddJob(pJob);
	}


	return true;
};

bool ThreadManager::RemoveJob(ThreadJob* pJob)
{
	pJob->isRunningFlag = false;
	for(auto it = mListThreadObject.begin() ; it != mListThreadObject.end() ; it++)
	{
		if((*it)->ReMoveJob(pJob))
		{
			std::cout << __FILE__ << " (" << __LINE__ << " ) [RemoveJob] Remove job :" << pJob  << std::endl;
			return true;
		}
	}

	std::cout << __FILE__ << "(" <<__LINE__ << ") Remove fail job :"<< pJob << std::endl ;
	return false;
};


void ThreadManager::OnAddJob(ThreadJob* job, void* param)
{

	ThreadManager *MyThreadManager = (ThreadManager*)param;
	MyThreadManager->AddJob(job);
};


void ThreadManager::OnRemoveJob(ThreadJob* job, void* param)
{
	ThreadManager *MyThreadManager = (ThreadManager*)param;
	MyThreadManager->RemoveJob(job);
};



//add job via handlethreadpoolevent
void ThreadManager::PostEventAddJob(ThreadJob* job)
{
	//std::cout << __FILE__ << "(" <<__LINE__ << ") [PostEventAddJob] job :" << job << std::endl ;
	ThreadPoolEvent *event = new ThreadPoolEvent(job, ThreadPoolEvent::ADD) ;
	mHandleThreadPoolEvent->PostEvent(event) ;
};

void ThreadManager::PostEventRemoveJob(ThreadJob* job)
{
	job->isRunningFlag = false;
	ThreadPoolEvent *event = new ThreadPoolEvent(job, ThreadPoolEvent::REMOVE) ;
	mHandleThreadPoolEvent->PostEvent(event) ;
};

