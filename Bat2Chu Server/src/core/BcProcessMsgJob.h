/*
 * BcProcessMsgJob.h
 *
 *  Created on: Jul 12, 2014
 *      Author: binhdu
 */

#ifndef BcProcessMsgJob_H_
#define BcProcessMsgJob_H_

//#include "BcMsg.h"
#include "../threadpool/ThreadJob.h"
#include "../network/TCPConnection.h"
#include "BcNetworkInterfaceJob.h"
#include "BcDataManager.h"

#include "M_if.h"


#include <iostream>
#include <string.h>

class BcNetworkInterfaceJob;

class BcProcessMsgJob : public ThreadJob
{

private:
	BcNetworkInterfaceJob *mNetInterface;
	BcDataManager *mDataManager ;

public:
	BcProcessMsgJob();
	BcProcessMsgJob(BcNetworkInterfaceJob *p);
	virtual ~BcProcessMsgJob();

public:
	virtual bool DoJob();
	void ProcessMsg(const char*) ;
	void ProcessRequestMsg(const char*);
	void ProcessResponseMsg(const char*);
	void SetDataManager(BcDataManager* pDaMng);

	bool DoRequestNextLevel(const char*);
	bool DoRequestGetImage(const char*);
	void DoUnknowMsg(const char*);
	bool DoRequestCreateUser();

	void AddBytes2Buffer(const void*, uint32_t,unsigned char[], uint32_t&);

};

#endif /* BcProcessMsgJob_H_ */
