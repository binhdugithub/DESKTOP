/*
 * RESTServer.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: root
 */

#include <locale>
#include "RESTServer.h"
#include "MyLogger.h"


RESTServer::RESTServer()
{

	std::string l_link("http://");
	l_link += Configuration::GetSingleTon()->sv_ip;
	l_link += std::string(":");
	l_link += Configuration::GetSingleTon()->sv_port;
	l_link += Configuration::GetSingleTon()->sv_root;
	m_Listener = new http_listener(http::uri(utility::conversions::to_string_t(l_link)));
	std::cout << "Init server with root:" << l_link << std::endl;

	m_Listener->support(methods::GET, RESTServer::HandleGET);
	m_Listener->support(methods::POST, RESTServer::HandlePOST);
	m_Listener->support(methods::PUT, RESTServer::HandlePUT);
	m_Listener->support(methods::DEL, RESTServer::HandleDEL);

}


RESTServer::RESTServer(const std::string p_link)
{
	std::cout << "Init server with root:" << p_link << std::endl;
	LOG_INFO("Init server with root:" << p_link);
	m_Listener = new  http_listener(http::uri(utility::conversions::to_string_t(p_link)));
	m_Listener->support(methods::GET, RESTServer::HandleGET);
	m_Listener->support(methods::POST, RESTServer::HandlePOST);
	m_Listener->support(methods::PUT, RESTServer::HandlePUT);
	m_Listener->support(methods::DEL, RESTServer::HandleDEL);
}


RESTServer::~RESTServer()
{
	m_Listener->close();
	delete m_Listener;
	m_Listener = NULL;
}


void RESTServer::StartListen()
{
	try
	{
		m_Listener
			->open()
			.then([]() {
			printf("Start listening!!\n");
		}).wait();
	}
	catch (exception const& e)
	{
		std::cout << "Listen fail !!" << std::endl;
		std::wcout << e.what() << std::endl;
	}
}

void RESTServer::HandleGET(http_request p_request)
{
	RESTHandler::GetSingleton()->HandleGET(p_request);
	return;
};

void RESTServer::HandlePOST(http_request p_request)
{
	RESTHandler::GetSingleton()->HandlePOST(p_request);
	return;
};

void RESTServer::HandlePUT(http_request p_request)
{
	RESTHandler::GetSingleton()->HandlePUT(p_request);
	return;
};

void RESTServer::HandleDEL(http_request p_request)
{
	RESTHandler::GetSingleton()->HandleDELETE(p_request);
	return;
};

//
//void RESTServer::DoGET(http_request)
//{
//
//}//end DoGET
//
//void RESTServer::DoPOST(http_request)
//{
//
//}//end DoPOST
//
//void RESTServer::DoPUT(http_request)
//{
//
//}//end DoPUT
//
//void RESTServer::DoDEL(http_request)
//{
//
//}//end DoDEL

