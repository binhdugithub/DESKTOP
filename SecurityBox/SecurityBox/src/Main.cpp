//============================================================================
// Name        : Main.cpp
// Author      : binhngt
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>

#include "TCPConnection.h"


using namespace std;

int main()
{

	//unsigned short port = 8080;
	TCPConnection *MyConnection = new TCPConnection();
	MyConnection->Listen();
	MyConnection->Start();

	while(1)
	{
		this_thread::sleep_for(std::chrono::milliseconds(1));

		//sleep(5);
	}
	return 0;
}