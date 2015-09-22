#pragma once
#include <cpprest\http_client.h>
#include <cpprest\http_listener.h>
#include <cpprest\json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental::listener;

#include <iostream>
#include <map>
#include <set>
#include <string>

#include "RestProcessing.h"
#include "Configuration.h"

using namespace std;


class RestConnection
{

public:
	http_listener *m_Listener;
	RestProcessing *ProcessRequest;

public:
	RestConnection();
	RestConnection(const char*);
	virtual ~RestConnection();
	void StartListen();

private:
	void HandleGET(http_request);
	void HandlePOST(http_request);
	void HandlePUT(http_request);
	void HandleDEL(http_request);

public:
	void ProcessingJSON(const json::value obj);
};
