/*
 * MyRESTServer.h
 *
 *  Created on: Dec 12, 2015
 *      Author: binhngt
 */

#ifndef RESTSERVER_H_
#define RESTSERVER_H_

#include <iostream>
#include <map>
#include <set>
#include <string>
#include "config.h"


#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental::listener;

using namespace std;


class MyRESTServer
{

public:
	http_listener *m_Listener;

public:
	MyRESTServer(const std::string p_ip, const std::string p_port, const std::string p_root);
	MyRESTServer(std::string);
	virtual ~MyRESTServer();
	void StartListen();

private:
	static void HandleGET(http_request);
	static void HandlePOST(http_request);
	static void HandlePUT(http_request);
	static void HandleDEL(http_request);

};

#endif /* RESTSERVER_H_ */
