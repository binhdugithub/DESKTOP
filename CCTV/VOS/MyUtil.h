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
#include <algorithm>

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

// split string into substring by token
static vector<string> splitStr(const string& str, char token)
{
	stringstream ss(str);
	string item;
	vector<string> result;
	while(std::getline(ss, item, token))
	{
		result.push_back(item);
	}
	return result;
}

// get current time to display, form : h:m:s d/m/y
static string getCurrentTimeDisplay(/*string& timeToDisplay*/)
{
	time_t now = time(0);
	struct tm ts;
	char buf1[50];
	char buf2[50];
	ts = *localtime(&now);
	strftime(buf1, sizeof(buf1), "%H:%M:%S   %d/%m/%Y", &ts);
	return string(buf1);
	//strftime(buf2, sizeof(buf2), "%Y_%m_%d_%H_%M_%S", &ts);
	//timeToDisplay = string(buf1);
	//timeForFile = string(buf2);
}

#ifdef __linux
// define GetTickCount on linux = GetTickCount on windows (in ms)
static unsigned long GetTickCount()
{
	struct timespec now;
	if (clock_gettime(CLOCK_MONOTONIC, &now))
	    return 0;
	return (unsigned long)(now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0);
}
#endif

// get tick count in microsecond. it is more precise
// to pass into encoder and decoder as time stamp
static unsigned long uGetTickCount()
{
	struct timespec now;
	if (clock_gettime(CLOCK_MONOTONIC, &now))
		return 0;
	return (unsigned long)(now.tv_sec * 1000000 + now.tv_nsec);
}

// get string from rtsp url
static string getIpFromRtspUrl(const string& rtspUrl)
{
	// if rtspurl is already an ip
	if(rtspUrl.length() < 8)
		return ""; // not real ip, not real url
	if(rtspUrl.size() >= 8 && rtspUrl.size() <= 16)
	{
		vector<string> ipstr = splitStr(rtspUrl, '.');
		if(ipstr.size() == 4)
		{
			if(toInt(ipstr[0]) >= 0 && toInt(ipstr[0]) <= 255 &&
				toInt(ipstr[1]) >= 0 && toInt(ipstr[1]) <= 255 &&
				toInt(ipstr[2]) >= 0 && toInt(ipstr[2]) <= 255 &&
				toInt(ipstr[3]) >= 0 && toInt(ipstr[3]) <= 255)
			return rtspUrl;
		}
	}

	// now url must be real url
	if(rtspUrl.substr(0,7) != "rtsp://")
	{
		if(rtspUrl.find(":") != string::npos) // url ip:port
			return rtspUrl;
		else
			return "";
	}

	string subUrl = rtspUrl.substr(7, string::npos);
	int pos = subUrl.find("/");
	//if(pos == string::npos) // not found ip:port
		//pos = subUrl.find("/");
	string ipPos = subUrl.substr(0, pos);
	if(ipPos.find("@") == string::npos) // not find @ in string (no user, pass)
		return ipPos;
	else
		return ipPos.substr(ipPos.find("@") + 1, string::npos);
}

// convert to vietnamese currency format: 10000 - > 1.000
template<typename T>
string toVNCurrencyFormat(T num)
{
	string result = "";
	stringstream ss;
	ss << num;
	string s = ss.str();
	if(s.length() <= 3)
		return s;
	std::reverse(s.begin(), s.end());
	int cnt = 0;
	for(size_t i = 0; i < s.length() - 1; ++i)
	{
		result += s[i];
		cnt++;
		if(cnt == 3)
		{
			result += ".";
			cnt = 0;
		}
	}
	result += s[s.length() - 1];
	std::reverse(result.begin(), result.end());
	return result;
}

} /* end of elc*/
#endif
