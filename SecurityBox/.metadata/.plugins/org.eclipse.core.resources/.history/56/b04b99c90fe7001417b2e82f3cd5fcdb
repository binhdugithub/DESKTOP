/*
 * HandleMACAddressTable.h
 *
 *  Created on: Apr 16, 2015
 *      Author: binhdu
 */

#ifndef HANDLEMACADDRESSTABLE_H_
#define HANDLEMACADDRESSTABLE_H_

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <ctype.h>
#include <iostream>
#include <string.h>
#include <netinet/ip.h>
#include <vector>
#include <thread>
#include "tinystr.h"
#include "tinyxml.h"
#include <mutex>
#include <netinet/ether.h>
using namespace std;


class HandleMACAddressTable
{
public:

	volatile bool mRunningFlag;
	std::thread *mHMainThread;


	std::recursive_mutex mIPWIMMutex;
	std::recursive_mutex mIPDatalogerMutex;

	char mMACWIM[20];
	char mMACDataloger[20];
	char mIPWIM[20];
	char mIPDataloger[20];

	static void Another_Callback(u_char *arg, const struct pcap_pkthdr* pkthdr, const u_char* packet);

	void Start();
	void LoadConfig();
	bool PassSecurityWIMIP(const char*);
	bool PassSecurityDatalogerIP(const char*);

	static void MainThread(void*);


public:
	HandleMACAddressTable();
	virtual ~HandleMACAddressTable();
};

#endif /* HANDLEMACADDRESSTABLE_H_ */
