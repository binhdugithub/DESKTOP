/*
 * ThreadObject.h
 *
 *  Created on: Jul 8, 2014
 *      Author: binhdu
 */

#ifndef THREADOBJECT_H_
#define THREADOBJECT_H_


#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#include "ThreadJob.h"



class ThreadObject
{
public:
	ThreadObject();
	virtual ~ThreadObject();
	std::size_t	GetSize();
	virtual bool AddJob(ThreadJob*) ;
	virtual bool ReMoveJob(ThreadJob*) ;

private:
	std::vector<ThreadJob*> mListJob;
	std::recursive_mutex mListJobMutex;
	std::thread *mHMainThread;
	bool volatile isRunningFlag ;
	static void MainThread(void *param);
};





#endif /* THREADOBJECT_H_ */
