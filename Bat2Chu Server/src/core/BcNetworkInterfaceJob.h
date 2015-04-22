/*
 * BcNetworkInterfaceJob.h
 *
 *  Created on: Jul 11, 2014
 *      Author: binhdu
 */

#ifndef BcNetworkInterfaceJob_H_
#define BcNetworkInterfaceJob_H_

#include <iostream>
#include <vector>
#include <mutex>

#include "../network/TCPConnection.h"
#include "../threadpool/ThreadJob.h"
#include "../threadpool/ThreadManager.h"
#include "BcProcessMsgJob.h"


#define PORT 1111


class BcNetworkInterfaceJob : public TCPConnection , public ThreadJob
{

public:
	std::string mRootPathImage ;
private:
	std::vector<const char*> mListMsg ;
	std::recursive_mutex mListMsgMutex;


public:
	BcNetworkInterfaceJob();
	BcNetworkInterfaceJob(std::string);
	BcNetworkInterfaceJob(int, std::string);
	virtual ~BcNetworkInterfaceJob();

public:
	bool StartListen(unsigned short port = PORT) ;
	BcNetworkInterfaceJob* Accept();
	virtual void OnAccept(int);
	virtual void OnRead(uint32_t);
	virtual void OnClose(int);
	virtual void Close();

	virtual bool DoJob();

	const char* PopMsg();
	bool PushMsg(const char* msg);

};

#endif /* BcNetworkInterfaceJob_H_ */
