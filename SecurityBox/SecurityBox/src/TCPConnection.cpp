/*
 * tcpconnection.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: hungnv
 */

#include "TCPConnection.h"




#define FILE_CONFIG 	"./Resources/config.xml"
#define MAXEVENTS 64
using namespace std;

TCPConnection::TCPConnection()
	: mSocketListener(-1)
	, mSocketDataloger(-1)
	, mSocketWIM(-1)
	, mHThreadListen(0)
	, mRunningListenFlag(false)
	, PortDatalogerConfig(~(0))
{
	LoadConfig();
	Create(PortDatalogerConfig);
	mHandleSecurity = new HandleMACAddressTable();
	mHandleSecurity->Start();
}



TCPConnection::~TCPConnection()
{
	Close();
}


void TCPConnection::TransmitDataWIM()
{


	while(1)
	{
		char bufferWIM[64000];
		char bufferDataloger[64000];

		memset(bufferWIM, 0, 64000);
		memset(bufferDataloger, 0, 64000);

		bool doneHeaderWIM = false;
		bool doneHeaderDataloger = false;

		int  currentByteWIM = 0;
		int  contentLengWIM = -1;

		int  currentByteDataloger = 0;
		int  contentLengDataloger = -1;

		fd_set rfd; // read event
		fd_set efd; // accept event
		timeval tv = { 0 };
		tv.tv_usec = 1;


		FD_ZERO(&rfd);
		FD_ZERO(&efd);
		FD_SET(mSocketWIM, &rfd);
		//nfds = nfds > mSocketWIM ? nfds : mSocketWIM ;
		FD_SET(mSocketWIM, &efd);
		//nfds = nfds > mSocketWIM ? nfds : mSocketWIM ;

		int retVal = select(mSocketWIM + 1, &rfd, NULL, & efd, &tv);

		if (retVal == -1 && errno == EINTR)
		{
			Close2Socket();
			break;
		}

		if (FD_ISSET(mSocketWIM, &efd))
		{
			char c;
			retVal = recv(mSocketWIM, &c, 1, MSG_OOB);
		}


		if (FD_ISSET(mSocketWIM, &rfd))
		{
			unsigned long n = 0;
			if(ioctl(mSocketWIM, FIONREAD, &n) < 0)
			{
				printf("FIONREAD WIM fail\n");
				Close2Socket();
				break ;
			}

			if(n == 0)
			{
				Close2Socket();
				break;
			}



			if(n > 0)
			{
				if(doneHeaderWIM == false)
				{
					while(1)
					{
						ReadPc(bufferWIM + currentByteWIM, 1);
						if(bufferWIM[currentByteWIM] == '\n' && currentByteWIM >= 3)
						{
							if(bufferWIM[currentByteWIM -1] == '\r'&&
									bufferWIM[currentByteWIM -2] == '\n'&&
									bufferWIM[currentByteWIM -3] == '\r')
							{
								currentByteWIM++;
								bufferWIM[currentByteWIM] = '\0';
								contentLengWIM = GetContentLeng(bufferWIM);

								if(contentLengWIM == 0)
								{
									if(CheckRequest(bufferWIM))
									{
										int retSend = WriteDataloger(bufferWIM, currentByteWIM );
										if(retSend < 0)
										{
											Close2Socket();
											break;
										}
										//this_thread::sleep_for(std::chrono::milliseconds(10));
									}
									else
									{
										printf("Check WIM request fail\n");
									}

									doneHeaderWIM = false;
									contentLengWIM = -1;
									currentByteWIM = 0;
									break;
								}

								doneHeaderWIM = true;
								break;
							}
						}

						currentByteWIM++;

					}//end While

					if(doneHeaderWIM == true)
					{
						while(contentLengWIM > 0)
						{
							int ret = ReadPc(bufferWIM + currentByteWIM, contentLengWIM);
							if(ret > 0)
							{
								contentLengWIM -= ret;
								currentByteWIM += ret;
							}
							else if(ret < 0)
							{
								this_thread::sleep_for(std::chrono::milliseconds(2));
							}
						}

						int retSend = WriteDataloger(bufferWIM, currentByteWIM);
						doneHeaderWIM = false;
						contentLengWIM = -1;
						currentByteWIM = 0;
						if(retSend < 0)
						{
							Close2Socket();
							break;
						}

					}

				}//end if doneHeaderWIM = false
			}//end if n > 0
		}//if (FD_ISSET(mSocketWIM, &rfd))


		//Dataloger

		fd_set rfd2; // read event
		fd_set efd2; // accept event
		timeval tv2 = { 0 };
		tv2.tv_usec = 1;


		FD_ZERO(&rfd2);
		FD_ZERO(&efd2);
		FD_SET(mSocketDataloger, &rfd2);
		FD_SET(mSocketDataloger, &efd2);

		int retVal2 = select(mSocketDataloger + 1, &rfd2, NULL, & efd2, &tv2);
		if (retVal2 == -1 && errno == EINTR)
		{
			Close2Socket();
			break;
		}

		if (FD_ISSET(mSocketDataloger, &efd2))
		{
			char c;
			retVal2 = recv(mSocketDataloger, &c, 1, MSG_OOB);
		}



		if (FD_ISSET(mSocketDataloger, &rfd2))
		{
			unsigned long n = 0;
			if(ioctl(mSocketDataloger, FIONREAD, &n) < 0)
			{
				printf("FIONREAD WIM fail\n");
				Close2Socket();
				break ;
			}

			if(n == 0)
			{
				Close2Socket();
				break;
			}

			if(n > 0)
			{
				//printf("13\n");
				if(doneHeaderDataloger == false)
				{
					while(1)
					{
						ReadDataloger(bufferDataloger + currentByteDataloger, 1);
						if(bufferDataloger[currentByteDataloger] == '\n' && currentByteDataloger >= 3)
						{
							if(bufferDataloger[currentByteDataloger -1] == '\r'&&
									bufferDataloger[currentByteDataloger -2] == '\n'&&
									bufferDataloger[currentByteDataloger -3] == '\r')
							{
								currentByteDataloger++;
								contentLengDataloger = GetContentLeng(bufferDataloger);

								if(contentLengDataloger == 0)
								{
									int retSend = WritePc(bufferDataloger, currentByteDataloger );
									if(retSend < 0)
									{
										Close2Socket();
										break;
									}

									doneHeaderDataloger = false;
									contentLengDataloger = -1;
									currentByteDataloger = 0;
									break;
								}

								doneHeaderDataloger = true;
								break;
							}
						}

						currentByteDataloger++;

					}//end While

					if(doneHeaderDataloger == true)
					{
						while(contentLengDataloger > 0)
						{
							int ret = ReadDataloger(bufferDataloger + currentByteDataloger, contentLengDataloger);
							if(ret > 0)
							{
								contentLengDataloger -= ret;
								currentByteDataloger += ret;
							}
							else if(ret < 0)
							{
								this_thread::sleep_for(std::chrono::milliseconds(2));
							}
						}

						int retSend = WritePc(bufferDataloger, currentByteDataloger);
						doneHeaderDataloger = false;
						contentLengDataloger = -1;
						currentByteDataloger = 0;
						if(retSend < 0)
						{
							Close2Socket();
							break;
						}

					}

				}//end if doneHeaderWIM = false
			}//end if n > 0
		}//if (FD_ISSET(mSocketWIM, &rfd))

		//end dataloger

	}//end while

	printf("-------------------------Full Transmit----------------------------\n");
	return;
}

bool TCPConnection::CheckRequest(const char *p_request)
{
	std::string reboot("/api/$/system/reboot");
	std::string getCrossings("/api/$/database/getCrossings");
	std::string auth("/api/auth/user");
	std::string request(p_request);

	std::size_t found_reboot = request.find(reboot);
	std::size_t found_getCrossings = request.find(getCrossings);
	std::size_t found_auth = request.find(auth);

	if(found_reboot != std::string::npos ||
	   found_getCrossings != std::string::npos ||
	   found_auth != std::string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;


}

void TCPConnection::ThreadListen(void* arg)
{
	//printf("ThreadListe\n");
	TCPConnection *MyClass = static_cast<TCPConnection*>(arg);

	while(MyClass->mRunningListenFlag)
	{
		fd_set rfd; // read event
		fd_set efd; // accept event
		int retVal, nfds = 0;
		timeval tv = { 0 };
		tv.tv_usec = 1;


		FD_ZERO(&rfd);
		FD_ZERO(&efd);

		FD_SET(MyClass->mSocketListener, &rfd);
		nfds = nfds > MyClass->mSocketListener ? nfds : MyClass->mSocketListener;
		FD_SET(MyClass->mSocketListener, &efd);
		nfds = nfds > MyClass->mSocketListener ? nfds : MyClass->mSocketListener;

		retVal = select(nfds + 1, &rfd, NULL, & efd, &tv);

		if (retVal == -1 && errno == EINTR)
			return ;

		if (FD_ISSET(MyClass->mSocketListener, &efd))
		{
			char c;
			retVal = recv(MyClass->mSocketListener, &c, 1, MSG_OOB);
		}

		if (FD_ISSET(MyClass->mSocketListener, &rfd))
		{
			//if(MyClass->mSocketPc == -1)
				MyClass->OnAccept(MyClass->mSocketListener);
			//else
				//printf("Reject connection from PC !!!!\n");

		}

	}
}



bool TCPConnection::ConnectToServer()
{
	struct sockaddr_in server_address;
	unsigned int l;


	memset(&server_address, 0, l = sizeof(server_address));
	int SocketDataloger = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(IPDatalogerConfig);
	server_address.sin_port = htons(PortDatalogerConfig);

	if(connect(SocketDataloger, (struct sockaddr *) &server_address, l) != -1)
	{
		//printf("Connected Server with socket: %d\n", mSocketDataloger);
		int32_t nReuse = IPTOS_LOWDELAY;
		setsockopt(SocketDataloger, SOL_SOCKET, SO_REUSEADDR, (char*)&nReuse, sizeof(int32_t));
		setsockopt(SocketDataloger, IPPROTO_TCP, IP_TOS, &nReuse, sizeof(int32_t));
		setsockopt(SocketDataloger,SOL_SOCKET, SO_SNDBUF, &nReuse, 64000);
		setsockopt(SocketDataloger,SOL_SOCKET, SO_RCVBUF, &nReuse, 64000);
		int flags = fcntl (SocketDataloger, F_GETFL, 0);
		if (flags != -1)
		{
			flags |= O_NONBLOCK;
			fcntl (SocketDataloger, F_SETFL, flags);
		}


		this_thread::sleep_for(std::chrono::milliseconds(10));
		if(!mHandleSecurity->PassSecurityDatalogerIP(IPDatalogerConfig))
		{
				mSocketDataloger = SocketDataloger;
				return true;
		}
		else
		{
			close(SocketDataloger);
			SocketDataloger = -1;

			return false;
		}

	}
	else
	{
		printf("Connect to server fail\n");
		return false;
	}

	return false;
}

bool TCPConnection::Accept(int p_socket)
{
	struct sockaddr_in client_address;
	unsigned int l;
	memset(&client_address, 0, l = sizeof(client_address));

	CloseSocketWIM();
	int SocketWIM = accept(p_socket, (struct sockaddr *) &client_address, &l);

	if(SocketWIM < 0)
	{
		printf("Accept error!\n");
		return false;
	}
	else
	{
		char ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &client_address.sin_addr.s_addr, ip, INET_ADDRSTRLEN);

		if(mHandleSecurity->PassSecurityWIMIP(ip))
		{
			//printf("Have a socket: %d from ip: %s\n",SocketWIM, ip);
			//printf("------------------------------------------------------------\n");
			int32_t nReuse = IPTOS_LOWDELAY;
			setsockopt(SocketWIM, SOL_SOCKET, SO_REUSEADDR, (char*)&nReuse, sizeof(int32_t));
			setsockopt(SocketWIM, IPPROTO_TCP, IP_TOS, &nReuse, sizeof(int32_t));
			setsockopt(SocketWIM,SOL_SOCKET, SO_SNDBUF, &nReuse, 64000);
			setsockopt(SocketWIM,SOL_SOCKET, SO_RCVBUF, &nReuse, 64000);
			int flags = fcntl (SocketWIM, F_GETFL, 0);
			if (flags != -1)
			{
				flags |= O_NONBLOCK;
				fcntl (SocketWIM, F_SETFL, flags);
			}

			CloseSocketDataloger();
			if(ConnectToServer())
			{
				mSocketWIM = SocketWIM;
				TransmitDataWIM();
				return true;
			}
			else
			{
				close(SocketWIM);
				printf("Dont pass security Dataloger:%s\n", mHandleSecurity->mIPDataloger);

				return false;
			}

		}
		else
		{
			close(SocketWIM);
			printf("Dont pass security WIM\n");
			return false;

		}

	}
	return false;
}

bool TCPConnection::Create(unsigned short port)
{
	struct sockaddr_in addr;
	int ret, flags;
	int32_t nReuse = IPTOS_LOWDELAY;

	Close();

	mSocketListener = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if(-1 == mSocketListener)
		return false;

	setsockopt(mSocketListener, SOL_SOCKET, SO_REUSEADDR, (char*)&nReuse, sizeof(int32_t));
	setsockopt(mSocketListener, IPPROTO_TCP, IP_TOS, &nReuse, sizeof(int32_t));

	flags = fcntl (mSocketListener, F_GETFL, 0);
	if (flags != -1)
	{
		flags |= O_NONBLOCK;
		fcntl (mSocketListener, F_SETFL, flags);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(port);

	ret = bind(mSocketListener, (__CONST_SOCKADDR_ARG)&addr, sizeof(addr));
	if(ret < 0)
	{
		cout << __FILE__<< "(" << __LINE__ << ") Bind socket got error!" << endl;
		return false;
	}

	return true;
}


void TCPConnection::Close2Socket()
{
	if(mSocketDataloger != 1)
	{
		close(mSocketDataloger);
		mSocketDataloger = -1;
	}

	if(mSocketWIM != -1)
	{
		close(mSocketWIM);
		mSocketWIM = -1;
	}
}
void TCPConnection::Close()
{
	if(0 != mHThreadListen)
	{
		mRunningListenFlag = false;
		mHThreadListen->join();
		delete mHThreadListen;
		mHThreadListen = 0;
	}

	Close2Socket();
}

bool TCPConnection::Listen()
{
	if(listen(mSocketListener, 5) < 0)
		return false;

	return true;
}

void TCPConnection::Start()
{
	mRunningListenFlag = true;
	mHThreadListen = new std::thread(ThreadListen , this);
}



void TCPConnection::LoadConfig()
{
	memset(IPDatalogerConfig,0,20);
	memset(MACDatalogerConfig,0,20);
	memset(MACPcConfig,0,20);

	TiXmlDocument doc("config.xml");

	if(!doc.LoadFile())
	{
		std::cout << __FILE__<< "(" << __LINE__ << ") " << __func__ << " load fail" << endl;
		doc.Clear();
		return;
	}

	TiXmlElement *eRoot = doc.RootElement(); // Bat2Chu
	TiXmlElement *eSetting = eRoot->FirstChildElement("Setting");

	TiXmlElement *eDataLoger = eSetting->FirstChildElement("datalogger");
	TiXmlElement *ePC = eSetting->FirstChildElement("pc");


	const char* temp1 = eDataLoger->Attribute("ip");
	const char* temp2 = eDataLoger->Attribute("port");
	const char* temp3 = eDataLoger->Attribute("MAC");
	const char* temp4 = eDataLoger->Attribute("MAC");

	strcpy(IPDatalogerConfig,temp1);
	strcpy(MACDatalogerConfig,temp3);
	strcpy(MACPcConfig,temp4);
	PortDatalogerConfig = atoi(temp2);

	printf("IPDatalogerConfig: %s\n", IPDatalogerConfig);
	printf("MACDatalogerConfig: %s\n", MACDatalogerConfig);
	printf("MACPcConfig: %s\n", MACPcConfig);
	printf("PortDatalogerConfig: %d\n", PortDatalogerConfig);


	doc.Clear();
	return;
}


int TCPConnection::ReadPc( void* buffer, int buffer_len)
{
	int ret = recv(mSocketWIM, (char*)buffer, buffer_len, 0);
	return ret;
}

int TCPConnection::ReadDataloger( void* buffer, int buffer_len)
{
	int ret = recv(mSocketDataloger, (char*)buffer, buffer_len, 0);
	return ret;
}

int TCPConnection::WritePc(const void* buffer, int buffer_len)
{
	int l_len = send(mSocketWIM, (const char*)buffer, buffer_len, 0);
	//printf("++++++++++++++++++++++ 2 WIM ++++++++++++++++++++++++++++\n");
	//printf("%s\n",buffer );
	//printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

	return l_len;
}

int TCPConnection::WriteDataloger(const void* buffer, int buffer_len)
{
#if 0
	std::string modified((const char*)buffer);

	size_t poss = modified.find("Host:");
	if (poss != std::string::npos)
	{
		size_t possLast = modified.find("\r\n", poss);
		modified.replace(poss, possLast - poss, "Host: 192.168.7.185:12345");
	}

	int l_len = send(mSocketDataloger, modified.c_str(), modified.size(), 0);

	//printf("++++++++++++++++++++++ 2 Dataloger ++++++++++++++++++++++++++++\n");
	//printf("%s\n",modified.c_str() );
	//printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	return l_len;
#else
	int l_len = send(mSocketDataloger, buffer, buffer_len, 0);

	//printf("++++++++++++++++++++++ 2 Dataloger ++++++++++++++++++++++++++++\n");
	//printf("%s\n", buffer );
	//printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	return l_len;
#endif
}


void TCPConnection::OnAccept(int thisSocket)
{
	Accept(thisSocket);
}


void TCPConnection::OnClose(int &thisSocket)
{
	close(thisSocket);
	thisSocket = -1;
}


