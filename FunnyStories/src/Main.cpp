//============================================================================
// Name        : TestIQ.cpp
// Author      : binhngt
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <thread>
#include "Configuration.h"
#include "MyLogger.h"
#include "RESTServer.h"

using namespace std;

int main()
{
	InitLogger(true);
	LOG_INFO("Hello world!!");

	std::string l_link("http://");
	l_link += Configuration::GetSingleTon()->sv_ip;
	l_link += std::string(":");
	l_link += Configuration::GetSingleTon()->sv_port;
	l_link += Configuration::GetSingleTon()->sv_root;

	RESTServer *Server = new RESTServer(l_link);
	Server->StartListen();

	while(1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	return 0;
}
