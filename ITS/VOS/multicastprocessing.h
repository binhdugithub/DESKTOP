/*
 * multicastprocessing.h
 *
 *  Created on: Jul 15, 2014
 *      Author: xyz
 */

#ifndef MULTICASTPROCESSING_H_
#define MULTICASTPROCESSING_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <iostream>
#include <thread>

#include "TollMessage.pb.h"
#include "mycommon.h"
#include "sourcemanager.h"
#include "imageoverlaytext.h"
#include "vostype.h"

class MulticastProcessing
{
public:
	MulticastProcessing();
	virtual ~MulticastProcessing();

	bool initMulticast(const std::string& ip, uint16_t port, int waitTime = 10000);
	void startListenning();

protected:
	static void startThread(void* userData);
	void doListenning();
	// process message
	void processMsg(const MulticastMsg& msg);
	// we only send msg if msg really change the contents.
	bool isNewMsg(const MulticastMsg& msg);

private:
	int fd;
	int timeOut;
	char* msgbuf;
	struct sockaddr_in addr;
	struct ip_mreq mreq;
	struct epoll_event event;
	struct epoll_event *events;
	std::thread* mThread;
	bool initOk;
	int nEvent;
	TollMessage tollMsg;
	vector<MulticastMsg*> multicastMsg;
	//MulticastMsg* mMsg;

};

#endif /* MULTICASTPROCESSING_H_ */
