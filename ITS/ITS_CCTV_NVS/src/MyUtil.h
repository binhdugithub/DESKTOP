/**
  * @file  : MyUltil.h
  * @brief : utinity conversion and others
  * @author: Longnv
  * @date  : 26/6/2014
  */

#ifndef MY_ULTIL_H
#define MY_ULTIL_H

#include <sstream>
#include <iostream>
#include <string>
#include <time.h>
#include <queue>

using namespace std;

namespace elc{

template<typename T>
string toString(const T& val)
{
	stringstream ss;
	ss << val;
	return ss.str();
}

template<typename T>
int toInt(const T& val)
{
	return atoi(toString(val).c_str());
}

template<typename T>
double toDouble(const T& val)
{
	return atof(toString(val).c_str());
}

static void getCurrentTime(string& timeForImage, string& timeForFile)
{
	time_t now = time(0);
	struct tm ts;
	char buf1[50];
	char buf2[50];
	ts = *localtime(&now);
	strftime(buf1, sizeof(buf1), "%H:%M:%S   %d/%m/%Y", &ts);
	strftime(buf2, sizeof(buf2), "%Y_%m_%d_%H_%M_%S", &ts);
	timeForImage = string(buf1);
	timeForFile = string(buf2);
}

// define GetTickCount on linux
#ifdef __linux
static unsigned long GetTickCount()
{
	struct timespec now;
	if (clock_gettime(CLOCK_MONOTONIC, &now))
	    return 0;
	return (unsigned long)(now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0);
}
#endif

} /* end of elc*/
#endif
