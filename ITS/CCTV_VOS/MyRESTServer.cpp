/*
 * MyRESTServer.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: binhngt
 */

#include <locale>

#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

#include "LogFile.h"
#include "MyRESTServer.h"
#include "imageoverlaytext.h"
#include "sourcemanager.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental::listener;


MyRESTServer::MyRESTServer(const std::string p_ip, const std::string p_port, const std::string p_root)
{

	std::string l_link("http://");
	l_link += p_ip;
	l_link += std::string(":");
	l_link += p_port;
	l_link += p_root;
	m_Listener = new http_listener(http::uri(utility::conversions::to_string_t(l_link)));
	std::cout << "Init server with root:" << l_link << std::endl;

	m_Listener->support(methods::GET, MyRESTServer::HandleGET);
	m_Listener->support(methods::POST, MyRESTServer::HandlePOST);
	m_Listener->support(methods::PUT, MyRESTServer::HandlePUT);
	m_Listener->support(methods::DEL, MyRESTServer::HandleDEL);

}


MyRESTServer::MyRESTServer(const std::string p_link)
{
	std::cout << "Init server with root:" << p_link << std::endl;
	LOG_INFO("Init server with root:" << p_link);
	m_Listener = new  http_listener(http::uri(utility::conversions::to_string_t(p_link)));
	m_Listener->support(methods::GET, MyRESTServer::HandleGET);
	m_Listener->support(methods::POST, MyRESTServer::HandlePOST);
	m_Listener->support(methods::PUT, MyRESTServer::HandlePUT);
	m_Listener->support(methods::DEL, MyRESTServer::HandleDEL);
}


MyRESTServer::~MyRESTServer()
{
	m_Listener->close();
	delete m_Listener;
	m_Listener = NULL;
}


void MyRESTServer::StartListen()
{
	try
	{
		m_Listener
			->open()
			.then([]() {
			std::cout << "Start listening!!\n";
		}).wait();
	}
	catch (exception const& e)
	{
		std::cout << "Listen fail !!" << std::endl;
		std::wcout << e.what() << std::endl;

		exit(0);
	}
}

void MyRESTServer::HandleGET(http_request p_request)
{
	std::cout << "HandleGET"<< std::endl;
	p_request.reply(http::status_codes::NotImplemented);
	return;
};

void MyRESTServer::HandlePOST(http_request p_request)
{
	std::cout << "HandlePOST"<< std::endl;
	LOG_INFO(__FUNCTION__<< " @ " << __FILE__);
	utility::string_t l_directory_path = p_request.relative_uri().path();

	std::cout << "path:" << l_directory_path << std::endl;
	if (l_directory_path == "/overlay")
	{
		std::cout << "handle overlay" << std::endl;
		pplx::task<json::value> l_task;
		try
		{
			l_task = p_request.extract_json();
			const json::value &json_request = l_task.get();
			LOG_INFO(__FUNCTION__<< " @ " << __FILE__ << " ** JSON body:\n" << json_request.serialize());


			std::string l_staffname(""), l_platecode(""), l_tickettype(""), l_camlaneip("");
			int l_price = 0;
			int  l_lanenumber;

			//lanenumber
			if (!json_request.has_field(utility::conversions::to_string_t("lanenumber")))
			{
				LOG_ERROR(__FUNCTION__<< " @ " << __FILE__ << "Missing field lanenumber");
				p_request.reply(http::status_codes::BadRequest);
				return;
			}

			auto jv_temp = json_request.at(utility::conversions::to_string_t("lanenumber"));
			if(jv_temp.is_integer())
			{
				l_lanenumber = jv_temp.as_integer();
			}

			//platecode
			if (!json_request.has_field(utility::conversions::to_string_t("platecode")))
			{
				LOG_ERROR(__FUNCTION__<< " @ " << __FILE__ << "Missing field platecode");
				p_request.reply(http::status_codes::BadRequest);
				return;
			}

			jv_temp = json_request.at(utility::conversions::to_string_t("platecode"));
			if(jv_temp.is_string())
			{
				l_platecode = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			//laneip
			if (!json_request.has_field(utility::conversions::to_string_t("camlaneip")))
			{
				LOG_ERROR(__FUNCTION__<< " @ " << __FILE__ << "Missing field camlaneip");
				p_request.reply(http::status_codes::BadRequest);
				return;
			}

			jv_temp = json_request.at(utility::conversions::to_string_t("camlaneip"));
			if(jv_temp.is_string())
			{
				l_camlaneip = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			//staffname
			if (!json_request.has_field(utility::conversions::to_string_t("staffname")))
			{
				LOG_ERROR(__FUNCTION__<< " @ " << __FILE__ << "Missing field staffname");
				p_request.reply(http::status_codes::BadRequest);
				return;
			}

			jv_temp = json_request.at(utility::conversions::to_string_t("staffname"));
			if(jv_temp.is_string())
			{
				l_staffname = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			//tickettype
			if (!json_request.has_field(utility::conversions::to_string_t("tickettype")))
			{
				LOG_ERROR(__FUNCTION__<< " @ " << __FILE__ << "Missing field tickettype");
				p_request.reply(http::status_codes::BadRequest);
				return;
			}

			jv_temp = json_request.at(utility::conversions::to_string_t("tickettype"));
			if(jv_temp.is_string())
			{
				l_tickettype = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			//price
			if (!json_request.has_field(utility::conversions::to_string_t("price")))
			{
				LOG_ERROR(__FUNCTION__<< " @ " << __FILE__ << "Missing field price");
				p_request.reply(http::status_codes::BadRequest);
				return;
			}

			jv_temp = json_request.at(utility::conversions::to_string_t("price"));
			if (jv_temp.is_integer())
			{
				l_price = jv_temp.as_integer();
			}

			std::cout << "lane:" << l_lanenumber << " platecode:" << l_platecode << " staffname:" << l_staffname << std::endl;
			std::cout << "tickettype:" << l_tickettype << " price:" << l_price << std::endl;

			MulticastMsg msg;
			msg.laneid = l_lanenumber;
			msg.cameralanip = l_camlaneip;
			msg.platenumber = l_platecode;
			msg.staffname = l_staffname;
			msg.price  = l_price;
			msg.tickettype = l_tickettype;
			ImageOverlayText* ov = SourceManager::getSingleton().findOverlay(msg.cameralanip);
			if(!ov) {
				LOG_ERROR(__FUNCTION__ << " @ " << __FILE__ << " lane camera's ip is not found or not turned on. Detail: " << l_camlaneip );
				p_request.reply(http::status_codes::NotFound);
				return;
			}

			ov->setMulticastMsg(msg);
			p_request.reply(http::status_codes::OK);
		}
		catch (const http_exception& e)
		{
			std::wcout << e.what() << std::endl;
			//std::wcout << utility::conversions::to_utf8string(p_request.to_string()).c_str() << std::endl;
			LOG_INFO(e.what());

			json::value l_json;
			l_json[utility::conversions::to_string_t("title")] = json::value::string(utility::conversions::to_string_t("POST info"));
			l_json[utility::conversions::to_string_t("status")] = json::value::string(utility::conversions::to_string_t("NOTOK"));
			l_json[utility::conversions::to_string_t("description")] = json::value::string(utility::conversions::to_string_t("Exception when parse JSON"));
			p_request.reply(http::status_codes::NotFound, l_json);
		}

		//p_request.reply(http::status_codes::OK);
		l_task.wait();
	}//end overlay
	else
	{
		p_request.reply(http::status_codes::BadRequest);
	}

	return;
};

void MyRESTServer::HandlePUT(http_request p_request)
{
	std::cout << "HandlePUT"<< std::endl;
	p_request.reply(http::status_codes::NotImplemented);
	return;
};

void MyRESTServer::HandleDEL(http_request p_request)
{
	std::cout << "HandleDEL"<< std::endl;
	p_request.reply(http::status_codes::NotImplemented);
	return;
};


