/*
 * tcpconnection.h
 *
 *  Created on: Nov 7, 2012
 *      Author: hungnv
 */

#ifndef TCPCONNECTION_H_
#define TCPCONNECTION_H_

#include <thread>
#include <iostream>

class TCPConnection
{
protected:
	int mSocket;
	int mListener;
	std::thread *mMainThreadTID;
	volatile bool mRunningFlag;

	static void* MainThread(void* arg);
public:
	TCPConnection();
	TCPConnection(unsigned short port);
	TCPConnection(int copySocket);
	virtual ~TCPConnection();

	bool Create(unsigned short port);
	void Close();

	bool Listen();

	void Start();
	bool ConnectTo(const char* server_addr, unsigned short server_port);
	virtual TCPConnection* Accept(unsigned short port = 0); // default is port was selected random
	virtual int  Read(void* buffer, int buffer_len);
	virtual int  Write(const void* buffer, int buffer_len);

	virtual void OnRead(int thisSocket)  ;
	virtual void OnAccept(int thisSocket) ;
	virtual void OnClose(int thisSocket) ;
};

#endif /* TCPCONNECTION_H_ */
