/*
 * ThreadJob.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: binhdu
 */


#include <iostream>
#include "ThreadJob.h"
#include "ThreadManager.h"

ThreadJob::ThreadJob()
{
	// TODO Auto-generated constructor stub
	isRunningFlag = true;
}

ThreadJob::~ThreadJob()
{
	// TODO Auto-generated destructor stub
	std::cout << __FILE__ << ": " << __LINE__ << " desructor of ThreadJob ["<< this << " ]"  << std::endl;
	isRunningFlag = false ;
}

void ThreadJob::AddJob(ThreadJob* job)
{
	ThreadManager::getSingletonPtr()->PostEventAddJob(job);
};


void ThreadJob::RemoveJob(ThreadJob* job)
{
	ThreadManager::getSingletonPtr()->PostEventRemoveJob(job);
};
