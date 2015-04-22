/*
 * BcNetworkInterfaceJob.cpp
 *
 *  Created on: Jul 11, 2014
 *      Author: binhdu
 */

#include <iostream>
#include <string.h> // for all mem* routines
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "BcNetworkInterfaceJob.h"
#include "BcProcessMsgJob.h"


BcNetworkInterfaceJob::BcNetworkInterfaceJob():TCPConnection() {
	// TODO Auto-generated constructor stub

}

BcNetworkInterfaceJob::BcNetworkInterfaceJob(std::string pRootPathImage):TCPConnection() {
	// TODO Auto-generated constructor stub
	mRootPathImage = pRootPathImage ;


}

BcNetworkInterfaceJob::BcNetworkInterfaceJob(int pSocket, std::string pRootPathImage)
{
	// TODO Auto-generated constructor stub
	mSocket = pSocket;
	mListener = -1;
	mRootPathImage = pRootPathImage ;


}

BcNetworkInterfaceJob::~BcNetworkInterfaceJob()
{
	// TODO Auto-generated destructor stub
	std::cout << __FILE__ << " (" << __LINE__ << " ) [~BcNetworkInterfaceJob] :" << this  << " socket " << mSocket << std::endl;

	mListMsgMutex.lock();
	while(!mListMsg.empty())
	{
		//delete mListMsg.front();
		mListMsg.erase(mListMsg.begin()) ;
	}
	mListMsgMutex.unlock();

	Close();


};

void BcNetworkInterfaceJob::Close()
{
	if(mSocket != -1)
	{
		close(mSocket);
		mSocket = -1 ;
	}
};

bool BcNetworkInterfaceJob::StartListen(unsigned short port)
{
	struct sockaddr_in addr;
	int ret;

	Close();

	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if(-1 == mSocket)
	{
		std::cout << __FILE__<< "(" << __LINE__ << ") [StartListen] create socket error !" << std::endl;
		return false;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(port);

	ret = bind(mSocket, (const sockaddr*)&addr, sizeof(addr));
	if(ret < 0)
	{
		std::cout << __FILE__<< "(" << __LINE__ << ") [StartListen] Bind socket error!" << std::endl;
		Close();
		return false;
	};

	if(listen(mSocket, 5) < 0)
	{
		std::cout << __FILE__<< "(" << __LINE__ << ") [StartListen] Listen error !" << std::endl;
		return false;
	}

	mListener = mSocket;
	return true;

} ;


BcNetworkInterfaceJob* BcNetworkInterfaceJob::Accept()
{
	std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Entry point !" << std::endl;
	struct sockaddr_in client_address;
	int l;
	int ret;
	memset(&client_address, 0, l = sizeof(client_address));
	//client_address.sin_port = htons(port);
	ret = accept(mListener, (sockaddr *) &client_address, (unsigned int*)&l);

	if(ret < 0)
	{
		std::cout << __FILE__<< "(" << __LINE__ << ") [Accept] accept error !" << std::endl;
		return NULL;
	}
	else
		return new BcNetworkInterfaceJob(ret, mRootPathImage);

};

void BcNetworkInterfaceJob::OnAccept(int pSocket)
{
	std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Entry point !" << std::endl;

	BcNetworkInterfaceJob *InterfaceJob = Accept();
	BcProcessMsgJob *ProcessMsg = new BcProcessMsgJob(InterfaceJob) ;

	if(InterfaceJob != NULL)
	{
		ThreadManager::getSingletonPtr()->PostEventAddJob(InterfaceJob);
		ThreadManager::getSingletonPtr()->PostEventAddJob(ProcessMsg);
	}
};


void BcNetworkInterfaceJob::OnRead(uint32_t pLeng)
{
	static unsigned char *buffer;
	static int numRead = 0;
	static volatile bool isFinishedRead = true;
	static int32_t pktLength = 0;


	if(isFinishedRead)
	{
		//Read header of message
		if(pLeng < sizeof(int32_t))
			return ;
		unsigned char header[4];
		int32_t ret = Read(header, sizeof(header));
		if(ret < sizeof(header))
			return;


		if(header[0] != 3 || header[1] != 0)
		{
			std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Check header[] fail" << pktLength << std::endl;
			return;
		}

		pktLength = ((header[2] << 8) | (header[3]));
		if(pktLength < 0)
		{
			std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Leng of package less than 0" << pktLength << std::endl;
			return;
		}

		//Read data of message
		if(buffer)
		{
			delete buffer;
			buffer = NULL;
		}

		buffer = (unsigned char*)malloc(pktLength * sizeof(unsigned char));
		if(!buffer)
		{
			buffer = (unsigned char*)malloc(pktLength * sizeof(unsigned char));
			if(!buffer)
			{
				std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Init buffer to receive data fail" << numRead << std::endl;
				return;
			}
		}

		numRead = 0;
		ret = Read(buffer + numRead , pktLength - numRead);
		if(ret < 0)
		{
			isFinishedRead = false;
			std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Receiving message fail :" << numRead << std::endl;
			return;
		}

		numRead += ret;
		if(numRead == pktLength)
		{
			isFinishedRead = true;
			PushMsg((const char*)buffer);
			std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Received leng :" << numRead << std::endl;
		}
		else
		{
			isFinishedRead = false;
		}

	}
	else
	{
		int32_t ret = Read(buffer + numRead , pktLength - numRead);
		if(ret < 0)
		{
			isFinishedRead = false;
			std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Receiving message fail :" << numRead << std::endl;
			return;
		}

		numRead += ret;
		if(numRead == pktLength)
		{
			isFinishedRead = true;
			PushMsg((const char*)buffer);
			std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Received leng :" << numRead << std::endl;
		}
	}

}

void BcNetworkInterfaceJob::OnClose(int pSocket)
{
	//std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Entry point !" << std::endl;
	ThreadManager::getSingletonPtr()->PostEventRemoveJob(this);

};

bool BcNetworkInterfaceJob::PushMsg(const char* msg)
{
	mListMsgMutex.lock();
	mListMsg.push_back(msg);
	mListMsgMutex.unlock();

	return true;
};

const char* BcNetworkInterfaceJob::PopMsg()
{
	mListMsgMutex.lock();
	if(!mListMsg.empty())
	{
		const char* msg = mListMsg.front();
		mListMsg.erase(mListMsg.begin()) ;
		mListMsgMutex.unlock();

		return msg;
	};

	mListMsgMutex.unlock();
	return NULL;
};


bool BcNetworkInterfaceJob::DoJob()
{
	if(!isRunningFlag)
		return false;

	fd_set rfd; // read event
	fd_set efd; // accept event
	int retVal, nfds = 0;
	timeval tv = { 0 };
	tv.tv_usec = 1;


	FD_ZERO(&rfd);
	FD_ZERO(&efd);
	FD_SET(mSocket, &rfd);
	//nfds = std::max(nfds, mSocket);
	nfds = nfds > mSocket ? nfds : mSocket ;
	FD_SET(mSocket, &efd);
	nfds = nfds > mSocket ? nfds : mSocket ;
	// do something here

	retVal = select(nfds + 1, &rfd, NULL, & efd, &tv);

	if (retVal == -1 && errno == EINTR)
		return false;

	if (FD_ISSET(mSocket, &efd))
	{
		char c;
		retVal = recv(mSocket, &c, 1, MSG_OOB);
	}

	if (FD_ISSET(mListener, &rfd))
	{
		OnAccept(mListener);
	}
	else if (FD_ISSET(mSocket, &rfd))
	{
		unsigned long n = 0;
		if(ioctl(mSocket, FIONREAD, &n) < 0)
			return false;

		if(0 == n)
		{
			OnClose(mSocket);
		}
		else
		{
			//std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Receive message with leng: " << n << std::endl;
			OnRead(n);
		}
	}


	return true ;

};



