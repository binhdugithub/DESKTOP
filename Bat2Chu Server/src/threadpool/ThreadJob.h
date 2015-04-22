/*
 * ThreadJob.h
 *
 *  Created on: Jul 8, 2014
 *      Author: binhdu
 */

#ifndef THREADJOB_H_
#define THREADJOB_H_

class ThreadJob
{
public:
	ThreadJob();
	virtual ~ThreadJob();
	virtual bool DoJob() = 0;
	virtual void AddJob(ThreadJob*);
	virtual void RemoveJob(ThreadJob*);

public:
	volatile bool isRunningFlag ;
};

#endif /* THREADJOB_H_ */
