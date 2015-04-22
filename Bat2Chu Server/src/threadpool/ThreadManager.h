/*
 * ThreadManager.h
 *
 *  Created on: Jul 8, 2014
 *      Author: binhdu
 */

#ifndef THREADMANAGER_H_
#define THREADMANAGER_H_




#include <thread>
#include <vector>
#include <mutex>

#include "ThreadObject.h"
#include "ThreadJob.h"
#include "../designparttern/ElcSingleton.h"
#include "HandleThreadPoolEvent.h"



class ThreadManager : public ElcSingleton<ThreadManager>
{

private:
	std::vector<ThreadObject*> mListThreadObject ;
	HandleThreadPoolEvent *mHandleThreadPoolEvent ;


public:
	ThreadManager();
	virtual ~ThreadManager();


public:
	bool AddObject(ThreadObject*) ;
	bool InitDefault();
	bool RemoveInstance() ;
	static unsigned int NumCPU() ;

private:
	static void OnAddJob(ThreadJob*, void*);
	static void OnRemoveJob(ThreadJob*, void*);

public:
	//add job now
	bool AddJob(ThreadJob*);
	bool RemoveJob(ThreadJob*);

public:
	//add job via handlethreadpoolevent
	void PostEventAddJob(ThreadJob*);
	void PostEventRemoveJob(ThreadJob*);

};

#endif /* THREADMANAGER_H_ */
