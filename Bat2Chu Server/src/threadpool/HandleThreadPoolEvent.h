/*
 * HandleThreadPoolEvent.h
 *
 *  Created on: Jul 10, 2014
 *      Author: binhdu
 */

#ifndef HandleThreadPoolEvent_H_
#define HandleThreadPoolEvent_H_



#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include "ThreadJob.h"

class ThreadPoolEvent ;

class HandleThreadPoolEvent
{

private:
	std::recursive_mutex mListEventMutex ;
	std::vector<ThreadPoolEvent*>	mListEvent ;

	std::thread *mHMainThread;
	volatile bool isRunningFlag ;

public:
	HandleThreadPoolEvent();
	virtual ~HandleThreadPoolEvent();

private:
	void (*mOnAddJob)(ThreadJob*, void*);
	void (*mOnRemoveJob)(ThreadJob *, void*);
	void *mUserData ;
	static void MainThread(void* param) ;

public:
	void SetCallBack(void (*pOnAddJob)(ThreadJob* , void*), void (*pOnRemoveJob)(ThreadJob *, void*) , void* );
	bool PostEvent(ThreadPoolEvent*);
	void Run();


};


//define message for threadjob
class ThreadPoolEvent
{

public:
enum
{
	ADD,
	REMOVE,
};

public:
	ThreadJob *mEventData ;
	int mTypeEvent ;

public:
	ThreadPoolEvent(ThreadJob *, int );
	virtual ~ThreadPoolEvent();

};


#endif /* HandleThreadPoolEvent_H_ */
