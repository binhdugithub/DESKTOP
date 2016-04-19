/*
 * RESTHandler.h
 *
 *  Created on: Dec 12, 2015
 *      Author: root
 */

#ifndef RESTHANDLER_H_
#define RESTHANDLER_H_
#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "MyLogger.h"
#include "FSProcessing.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental::listener;

class RESTHandler
{
private:
	static RESTHandler *m_Instance;
	//FSProcessing *m_FSProcessing;

public:
	RESTHandler();
	virtual ~RESTHandler();
	static RESTHandler* GetSingleton();
	void HandlePOST(http_request);
	void HandlePUT(http_request);
	void HandleGET(http_request);
	void HandleDELETE(http_request);
};

#endif /* RESTHANDLER_H_ */
