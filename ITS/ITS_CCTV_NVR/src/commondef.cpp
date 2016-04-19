/*
 * commondef.cpp
 *
 *  Created on: 8 Jul, 2014
 *      Author: cuonglm
 */
#include <string>


#include "commondef.h"




std::string textLog;
bool isExit = false;

void initMutexCommond()
{
	pthread_mutex_init(&myMutex, NULL);
}

void destroyMutexCommond()
{
    pthread_mutex_destroy(&myMutex);
}

void insertFirstDBQueue(std::string query)
{
	pthread_mutex_lock(&myMutex);
	//std::cout << "Push front" << std::endl;
	dbQueue.push_front(query);
	pthread_mutex_unlock(&myMutex);
}

void pushDBQueue(std::string query)
{
	pthread_mutex_lock(&myMutex);
	//std::cout << "Push back" << std::endl;
	dbQueue.push_back(query);
	pthread_mutex_unlock(&myMutex);
}

std::string getDBQueue()
{
	std::string result = "";
	pthread_mutex_lock(&myMutex);
	//std::cout << "Get dbqueue" << std::endl;
	if(!dbQueue.empty())
	{
		result = dbQueue.front();
		dbQueue.erase(dbQueue.begin());
	}
	pthread_mutex_unlock(&myMutex);
	return result;
}

int getSizeDBQueue()
{
	int size;
	pthread_mutex_lock(&myMutex);
	//std::cout << "getSizeDBQueue dbqueue" << std::endl;
	size = dbQueue.size();
	pthread_mutex_unlock(&myMutex);
	return size;
}

std::string GetDeltaTime(struct tm ts)
{
	std::string hour, minus, second, dataSize, filename;
	struct timespec tv;
	clock_gettime( CLOCK_REALTIME, &tv);
	struct tm tm = *localtime(&tv.tv_sec);
	if(ts.tm_mday<tm.tm_mday)
		tm.tm_hour = tm.tm_hour + 24;
	int h, m, s ;
	int duration = (tm.tm_hour - ts.tm_hour)*3600 + (tm.tm_min - ts.tm_min)*60 + tm.tm_sec - ts.tm_sec;

	h = duration/3600;
	m = (duration - h*3600)/60;
	s = duration - h*3600 - m*60;
	if(s<10)
		second = "0" + std::to_string(s);
	else
		second = std::to_string(s);

	if(h<10)
		hour =  "0" + std::to_string(h);
	else
		hour = std::to_string(h);

	if(m<10)
		minus = "0" + std::to_string(m);
	else
		minus = std::to_string(m);


	std::string m_LengTimeFile = hour +":" + minus + ":" + second;

	return m_LengTimeFile;
}

std::string GetSizeOfRecoredFile(std::string p_path)
{
	float sizeInBytes = 0.0f;
	//char * fileName = filePath.c_str();
	fstream file(p_path.c_str(), ios::in);
	if (file)
	{
		file.seekg(0, ios::end);
		sizeInBytes = file.tellg();
	}
	else
	{
		LOG_ERROR("False get size file "<<p_path);
	}


	float fileSize = sizeInBytes/(1024*1024);
	int tam = (int) (fileSize * pow(10, 2));
	fileSize= (float) (tam / pow(10, 2));
	std::ostringstream ss;
	ss << fileSize;

	return ss.str();
}


