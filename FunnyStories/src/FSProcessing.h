/*
 * FSProcessing.h
 *
 *  Created on: Dec 16, 2015
 *      Author: root
 */

#ifndef SRC_FSPROCESSING_H_
#define SRC_FSPROCESSING_H_

#include <iostream>
#include <vector>


#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

#include "DBInterface.h"
#include "MyLogger.h"


using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental::listener;


class FSProcessing
{
public:
	FSProcessing();
	virtual ~FSProcessing();
private:
	static FSProcessing *m_Instance;
	volatile long long m_count;

public:
	static FSProcessing* GetSingleton();
	void GetListStories(http_request p_request);
	void GetStory(http_request p_request);
	void GetListApps(http_request p_request);
	void UpdateStories(http_request);
	void UpdateApps(http_request p_request);
	void ReloadStories(http_request);
	void ReloadApps(http_request p_request);
};

#endif /* SRC_FSPROCESSING_H_ */
