/*
 * RESTServer.h
 *
 *  Created on: Dec 12, 2015
 *      Author: root
 */

#ifndef RESTSERVER_H_
#define RESTSERVER_H_

#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental::listener;

#include <iostream>
#include <map>
#include <set>
#include <string>

#include "RESTHandler.h"
#include "Configuration.h"

using namespace std;


class RESTServer
{

public:
	http_listener *m_Listener;

public:
	RESTServer();
	RESTServer(std::string);
	virtual ~RESTServer();
	void StartListen();

private:
	static void HandleGET(http_request);
	static void HandlePOST(http_request);
	static void HandlePUT(http_request);
	static void HandleDEL(http_request);

//public:
//	virtual void DoGET(http_request) = 0;
//	virtual void DoPOST(http_request) = 0;
//	virtual void DoPUT(http_request) = 0;
//	virtual void DoDEL(http_request) = 0;
};

#endif /* RESTSERVER_H_ */
