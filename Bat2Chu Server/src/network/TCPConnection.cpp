/*
 * tcpconnection.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: hungnv
 */

#include "TCPConnection.h"
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

#define MAXEVENTS 64
using namespace std;

TCPConnection::TCPConnection()
	: mSocket(-1)
	, mListener(~(0))
	, mMainThreadTID(0)
	, mRunningFlag(false)
{

}

TCPConnection::TCPConnection(unsigned short port)
	: mSocket(-1)
	, mListener(~(0))
	, mMainThreadTID(0)
	, mRunningFlag(false)
{
	Create(port);
}

TCPConnection::TCPConnection(int copySocket)
	: mSocket(copySocket)
	, mListener(~(0))
{
	int flags;
	int32_t nReuse = IPTOS_LOWDELAY;

	setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&nReuse, sizeof(int32_t));
	setsockopt(mSocket, IPPROTO_TCP, IP_TOS, &nReuse, sizeof(int32_t));

	flags = fcntl (mSocket, F_GETFL, 0);
	if (flags != -1)
	{
		flags |= O_NONBLOCK;
		fcntl (mSocket, F_SETFL, flags);
	}

	mRunningFlag = true;
	mMainThreadTID = new std::thread(MainThread , this);
}

TCPConnection::~TCPConnection()
{
	Close();
}

void* TCPConnection::MainThread(void* arg)
{
#if 0

	TCPConnection* thisClass = static_cast<TCPConnection*>(arg);
	fd_set rfd; // read event
	fd_set wfd; // write event
	fd_set efd; // except event
	int retVal;
	timeval tv = { 0 };

	while(thisClass->mRunningFlag)
	{
		FD_ZERO(&rfd);
		FD_ZERO(&wfd);
		FD_ZERO(&efd);
		FD_SET(thisClass->mSocket, &rfd);
		FD_SET(thisClass->mSocket, &wfd);
		FD_SET(thisClass->mSocket, &efd);
		// do something here

		retVal = select(thisClass->mSocket + 1, &rfd, &wfd, &efd, &tv);

		if (retVal == -1 && errno == EINTR)
			continue;

		if (FD_ISSET(thisClass->mSocket, &efd))
		{
			char c;
			retVal = recv(thisClass->mSocket, &c, 1, MSG_OOB);
		}

		if (FD_ISSET(thisClass->mSocket, &rfd))
		{
			int n = 0;
			size_t sizeN = sizeof(n);

			if(getsockopt(thisClass->mSocket, SOL_SOCKET, SO_ACCEPTCONN,&n, &sizeN) < 0)
				continue;

			if(1 == n) // listening socket
			{
				thisClass->OnAccept(thisClass->mSocket);
				continue;
			}

			if(ioctl(thisClass->mSocket, FIONREAD, &n) < 0)
				continue;

			if(0 == n)
			{
				thisClass->OnClose(thisClass->mSocket);
				break;
			}
			else
			{
				thisClass->OnRead(thisClass->mSocket);
			}
		}
		else
		{
			usleep(1000);
		}
	}

#else

	TCPConnection* thisClass = static_cast<TCPConnection*>(arg);
	int efd, ret;
	struct epoll_event event;
	struct epoll_event *events;

	int wait_timeout = 1000; // 1000 milliseconds

	efd = epoll_create1 (0);
	if (efd == -1)
	{
		perror ("epoll_create");
		return NULL;
	}

	event.data.fd = thisClass->mSocket;
	event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
	ret = epoll_ctl (efd, EPOLL_CTL_ADD, thisClass->mSocket, &event);
	if (ret == -1)
	{
		perror ("epoll_ctl");
		return NULL;
	}

	/* Buffer where events are returned */
	events = (struct epoll_event *) calloc (MAXEVENTS, sizeof event);

	/* The event loop */
	while (thisClass->mRunningFlag)
	{
		int n, i;

		n = epoll_wait (efd, events, MAXEVENTS, wait_timeout);
		for (i = 0; i < n; i++)
		{
			if (thisClass->mListener == events[i].data.fd)
			{
				/* We have a notification on the listening socket, which
				means one or more incoming connections. */
				thisClass->OnAccept(thisClass->mListener);
				continue;
			}
			if (events[i].events & EPOLLIN)
			{
				if (events[i].events & EPOLLRDHUP)
				{
					/* An error has occurred on this fd, or the socket is not
					ready for reading (why were we notified then?) */
					cout << "Socket was closed. Need free it!!!" << endl;
					thisClass->OnClose(events[i].data.fd);
					thisClass->mRunningFlag = false;
					break;
				}
				else
					thisClass->OnRead(thisClass->mSocket);
			}
		}
	}

	free (events);
	close(efd);

#endif
	return NULL;
}

bool TCPConnection::Create(unsigned short port)
{
	struct sockaddr_in addr;
	int ret, flags;
	int32_t nReuse = IPTOS_LOWDELAY;

	Close();

	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if(-1 == mSocket)
		return false;

	setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&nReuse, sizeof(int32_t));
	setsockopt(mSocket, IPPROTO_TCP, IP_TOS, &nReuse, sizeof(int32_t));

	flags = fcntl (mSocket, F_GETFL, 0);
	if (flags != -1)
	{
		flags |= O_NONBLOCK;
		fcntl (mSocket, F_SETFL, flags);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(port);

	ret = bind(mSocket, (__CONST_SOCKADDR_ARG)&addr, sizeof(addr));
	if(ret < 0)
	{
		cout << __FILE__<< "(" << __LINE__ << ") Bind socket got error!" << endl;
		return false;
	}

	return true;
}

void TCPConnection::Close()
{
	if(mSocket != -1) // socket was opened
	{
		if(0 != mMainThreadTID)
		{
			mRunningFlag = false;
			mMainThreadTID->join();
			mMainThreadTID = 0;
		}

		close(mSocket);
		mSocket = -1;
	}
}

bool TCPConnection::Listen()
{
	if(listen(mSocket, 5) < 0)
		return false;

	mListener = mSocket;

	return true;
}

void TCPConnection::Start()
{
	mRunningFlag = true;
	mMainThreadTID = new std::thread(MainThread , this);
}

bool TCPConnection::ConnectTo(const char* server_addr, unsigned short server_port)
{
	struct sockaddr_in server_address;
	unsigned int l;
	memset(&server_address, 0, l = sizeof(server_address));

	server_address.sin_family = AF_INET;

	if(!inet_aton(server_addr, (struct in_addr *) &server_address.sin_addr.s_addr))
		return false;

	server_address.sin_port = htons(server_port);

	return connect(mSocket, (struct sockaddr *) &server_address, l) != -1;
}

TCPConnection* TCPConnection::Accept(unsigned short port)
{
	struct sockaddr_in client_address;
	unsigned int l;
	int ret;
	memset(&client_address, 0, l = sizeof(client_address));
	client_address.sin_port = htons(port);
	ret = accept(mSocket, (struct sockaddr *) &client_address, &l);

	if(ret < 0)
		return NULL;
	else
		return new TCPConnection(ret);

	return NULL;
}

int TCPConnection::Read(void* buffer, int buffer_len)
{
	return recv(mSocket, (char*)buffer, buffer_len, 0);
}

int TCPConnection::Write(const void* buffer, int buffer_len)
{
	//if(buffer_len < 1024)
	{
		return send(mSocket, (const char*)buffer, buffer_len, 0);
	}

	/*uint32_t total_len_sent = 0;
	uint32_t len_temp_sent = 0;
	uint32_t len_last = buffer_len;

	while(total_len_sent < buffer_len)
	{
		len_temp_sent = send(mSocket, (const char*)(buffer + total_len_sent) , len_last, 0);
		if(len_temp_sent < 0)
			return -1;
		else
		{
			total_len_sent += len_temp_sent;
			len_last -= total_len_sent;
		}
	}

	return total_len_sent;
	*/

}


void TCPConnection::OnRead(int thisSocket)
{

}
void TCPConnection::OnAccept(int thisSocket)
{

}
void TCPConnection::OnClose(int thisSocket)
{

}

