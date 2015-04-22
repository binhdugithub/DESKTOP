/*
 * ThreadObject.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: binhdu
 */

#include "ThreadObject.h"
#include <chrono>

void ThreadObject::MainThread(void *param)
{

	ThreadObject *MyObj = (ThreadObject*)param;
	std::cout << __FILE__ << " (" << __LINE__ << " ) In ThreadJobject :" << MyObj  << std::endl;

	bool needSleep ;
	while(MyObj->isRunningFlag)
	{
		needSleep = true;

		MyObj->mListJobMutex.lock();
		for(auto it = MyObj->mListJob.begin(); it != MyObj->mListJob.end(); it++)
		{
			needSleep &=(!(*it)->DoJob());
		}
		MyObj->mListJobMutex.unlock();

		if(needSleep)
			std::this_thread::sleep_for(std::chrono::milliseconds(1));

	}

	//std::cout << __FILE__ << " (" << __LINE__ << " ) Out ThreadJobject :" << MyObj  << std::endl;
	//std::cout << __FILE__ << __LINE__ <<":" << "Out MainThread" << std::endl;
}

ThreadObject::ThreadObject()
{
	// TODO Auto-generated constructor stub
	isRunningFlag = true;
	mHMainThread = new std::thread(MainThread,this);
}

ThreadObject::~ThreadObject()
{
	// TODO Auto-generated destructor stub

	std::cout << __FILE__ << " (" << __LINE__ << " ) Destructor ThreadObject :" << this  << std::endl;
	isRunningFlag = false;
	mHMainThread->join();

	delete mHMainThread;
	mHMainThread = NULL;

	while(!mListJob.empty())
	{
		// ThreadJob *tempThreadJob = mListJob.front();
		 delete mListJob.front() ;
		 mListJob.erase(mListJob.begin());

	}
}

std::size_t	ThreadObject::GetSize()
{
	return mListJob.size();
};


bool ThreadObject::AddJob(ThreadJob* pJob)
{
	if(pJob)
	{
		mListJobMutex.lock();
		for(auto it = mListJob.begin(); it != mListJob.end(); it++)
		{
			if((*it) == pJob)
			{
				mListJobMutex.unlock();
				return false;
			}
		}

		mListJob.push_back(pJob);
		mListJobMutex.unlock();

		return true;
	}

	return false;
} ;


bool ThreadObject::ReMoveJob(ThreadJob* pJob)
{

	//std::cout << __FILE__ << " (" << __LINE__ << " ) [ReMoveJob] Remove job :" << pJob  << std::endl;
	if(pJob)
	{
		mListJobMutex.lock();
		for(auto it = mListJob.begin(); it != mListJob.end(); it++)
		{

			if((*it) == pJob)
			{
				//std::cout << __FILE__ << " (" << __LINE__ << " ) [ReMoveJob] job :" << *it << " ok 1"  << std::endl;
				delete (pJob);
				pJob = NULL ;

				mListJob.erase(it);

				mListJobMutex.unlock();

				//std::cout << __FILE__ << " (" << __LINE__ << " ) [ReMoveJob] job :" << *it << " ok 2"  << std::endl;
				return true;
			}
		}

		mListJobMutex.unlock();
		return false;
	}


	return false;
} ;

