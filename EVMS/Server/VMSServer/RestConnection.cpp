#include "stdafx.h"
#include <locale>
#include "RestConnection.h"

#include "MsgLogin.h"
#include "Define_Mif.h"
#include "LogFile.h"


RestConnection::RestConnection()
{
	/*utility::string_t test(L"ABCD");
	std::string test2(test.begin(), test.end());
	std::cout << test2 << std::endl;*/


	ProcessRequest = new RestProcessing();

	std::string link("http://");
	link += Configuration::GetSingleTon()->sv_ip;
	link += std::string(":");
	link += Configuration::GetSingleTon()->sv_port;
	//slink += std::string("/");
	link += Configuration::GetSingleTon()->sv_root;

	//const char* mbstr = link.c_str();
	//std::wstring_convert< std::codecvt<wchar_t, char, std::mbstate_t> > conv;
	//std::wstring link_wstring = conv.from_bytes(link.c_str());
	//std::wstring link_wstring = ProcessRequest->String2WString(link);
	std::wcout << "Path root:" << utility::conversions::to_string_t(link) << std::endl;

	//m_Listener = new http_listener(http::uri(std::wstring(L"http://192.168.7.32:80/api/evms")));
	m_Listener = new http_listener(http::uri(utility::conversions::to_string_t(link)));

	m_Listener->support(methods::GET, std::bind(&RestConnection::HandleGET, this, std::placeholders::_1));
	m_Listener->support(methods::POST, std::bind(&RestConnection::HandlePOST, this, std::placeholders::_1));
	m_Listener->support(methods::PUT, std::bind(&RestConnection::HandlePUT, this, std::placeholders::_1));
	m_Listener->support(methods::DEL, std::bind(&RestConnection::HandleDEL, this, std::placeholders::_1));

}



RestConnection::RestConnection(const char* p_link)
{
	ProcessRequest = new RestProcessing();

	std::wstring_convert< std::codecvt<wchar_t, char, std::mbstate_t> > conv;
	std::wstring link_wstring = conv.from_bytes(p_link);
	std::wcout << "Path root:" << link_wstring << std::endl;


	m_Listener = new  http_listener(http::uri(link_wstring));
	m_Listener->support(methods::GET, std::bind(&RestConnection::HandleGET, this, std::placeholders::_1));
	m_Listener->support(methods::POST, std::bind(&RestConnection::HandlePOST, this, std::placeholders::_1));
	m_Listener->support(methods::PUT, std::bind(&RestConnection::HandlePUT, this, std::placeholders::_1));
	m_Listener->support(methods::DEL, std::bind(&RestConnection::HandleDEL, this, std::placeholders::_1));
}


RestConnection::~RestConnection()
{
	m_Listener->close();
	delete m_Listener;
	m_Listener = NULL;

	delete ProcessRequest;
	ProcessRequest = NULL;
}


void RestConnection::StartListen()
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

void RestConnection::HandleGET(http_request p_request)
{
	//printf("-------------Handle Get-------------\n");
	std::wcout << "Handle GET:" << p_request.request_uri().to_string() << std::endl;
	//std::wcout << "Request URI: " << p_request.request_uri().to_string() << std::endl;
	std::wcout << "Relate URI: " << p_request.relative_uri().to_string() << std::endl;
	//std::wcout << "Query  URI: " << p_request.request_uri().query() << std::endl;

	utility::string_t directory_path = p_request.relative_uri().path();

	if (directory_path == PATH_LOGIN)
	{
		ProcessRequest->Login(p_request);
	}
	if (directory_path == PATH_ROLE)
	{
		ProcessRequest->GetRole(p_request);
	}
	else if (directory_path == PATH_VMS)
	{
		ProcessRequest->GetListObject(p_request);
	}
	else if (directory_path == PATH_USER)
	{
		ProcessRequest->GetListUser(p_request);
	}
	else if (directory_path == PATH_PROGRAM)
	{
		//std::wcout << "PATH_PROGRAM" << std::endl;
		ProcessRequest->GetListProgram(p_request);
	}
	else if (directory_path == PATH_DEVICE)
	{
		//std::wcout << "PATH_PROGRAM" << std::endl;
		ProcessRequest->GetListDevice(p_request);
	}
	else if (directory_path == PATH_MONITORING)
	{
		//std::wcout << "PATH_PROGRAM" << std::endl;
		ProcessRequest->GetListMonitoring(p_request);
	}
	else if (directory_path == PATH_IMAGE)
	{
		//std::wcout << "PATH_PROGRAM" << std::endl;
		ProcessRequest->GetListImageResource(p_request);
	}
	else if (directory_path == PATH_ACTION)
	{
		//std::wcout << "PATH_PROGRAM" << std::endl;
		ProcessRequest->GetListAction(p_request);
	}
	else if (directory_path == PATH_HISTORY)
	{
		//std::wcout << "PATH_PROGRAM" << std::endl;
		ProcessRequest->GetListHistory(p_request);
	}
	
	else
	{
		ProcessRequest->DontKnowRequest(p_request);
		std::wcout << L"ERROR: Dont know path client request" << std::endl;
		LOG_ERROR("ERROR: Dont know path client request");
	}


	return;
};

void RestConnection::HandlePOST(http_request p_request)
{
	//printf("-------------Handle Post-------------\n");
	std::wcout << "Handle POST:" << p_request.request_uri().to_string() << std::endl;

	utility::string_t path = p_request.relative_uri().path();


	if (path == PATH_USER)
	{
		ProcessRequest->CreateUser(p_request);
	}
	else if (path == PATH_VMS)
	{
		ProcessRequest->CreateObject(p_request);
	}
	else if (path == PATH_PROGRAM)
	{
		ProcessRequest->CreateProgram(p_request);
	}
	
	else
	{
		ProcessRequest->DontKnowRequest(p_request);

		std::wcout << L"ERROR: Dont know path client request" << std::endl;
		LOG_ERROR("ERROR: Dont know path client request");
	}


	return;


};

void RestConnection::HandlePUT(http_request p_request)
{
	std::wcout << "Handle PUT:" << p_request.request_uri().to_string() << std::endl;
	utility::string_t path = p_request.relative_uri().path();

	if (path == PATH_USER)
	{
		ProcessRequest->UpdateUser(p_request);
	}
	else if (path == PATH_VMS)
	{
		ProcessRequest->UpdateObject(p_request);
	}
	else if (path == PATH_VMS_PROGRAM)
	{
		ProcessRequest->UpdateObjectProgram(p_request);
	}
	else if (path == PATH_USER_VMS)
	{
		ProcessRequest->AssignObject(p_request);
	}
	else if (path == PATH_PROGRAM)
	{
		ProcessRequest->UpdateProgram(p_request);
	}
	else
	{
		ProcessRequest->DontKnowRequest(p_request);

		std::wcout << L"ERROR: Dont know path client request" << std::endl;
		LOG_ERROR("ERROR: Dont know path client request");
	}


	return;
};

void RestConnection::HandleDEL(http_request p_request)
{
	std::wcout << "Handle DEL:" << p_request.request_uri().to_string() << std::endl;

	utility::string_t path = p_request.relative_uri().path();

	if (path == PATH_USER)
	{
		ProcessRequest->DeleteUser(p_request);
	}
	else if (path == PATH_VMS)
	{
		ProcessRequest->DeleteObject(p_request);
	}
	else if (path == PATH_PROGRAM)
	{
		ProcessRequest->DeleteProgram(p_request);
	}
	else
	{
		ProcessRequest->DontKnowRequest(p_request);

		std::wcout << L"ERROR: Dont know path client request" << std::endl;
		LOG_ERROR("ERROR: Dont know path client request");
	}


	return;
};



//Process json
void RestConnection::ProcessingJSON(const json::value obj)
{
	if (!obj.is_null())
	{
		if (obj.is_object())
		{
			std::wcout << L"JSON is Object !" << std::endl;
			// Loop over each element in the object. 
			for (auto iter = obj.as_object().cbegin(); iter != obj.as_object().cend(); ++iter)
			{
				// Make sure to get the value as const reference otherwise you will end up copying 
				// the whole JSON value recursively which can be expensive if it is a nested object. 
				//const json::value &str = iter->first

				const utility::string_t &key = iter->first;
				const json::value &value = iter->second;

				if (value.is_object() || value.is_array())
				{
					//We have an object with children or an array
					std::wcout << L"Parent: " << key.c_str() << std::endl;

					//Loop over each element in the object by calling  ProcessingJSON
					ProcessingJSON(value);

					std::wcout << L"End of Parent" << key.c_str() << std::endl;
				}

				else
				{
					//Always display the value as a string
					std::wcout << key.c_str();

					if (value.is_null())
					{
						std::wcout << L"NULL" << std::endl;

					}
					else
					{
						if (value.is_string())
							std::wcout << value.as_string() << std::endl;

						else if (value.is_number())
							std::wcout << value.as_number().to_int32() << std::endl;

						else if (value.is_boolean())
							std::wcout << value.as_bool() << std::endl;
						else
							std::wcout << L"Unknow" << std::endl;

					}

				}
			}
		}
		else if (obj.is_array())
		{
			std::wcout << L"JSON is Array !" << std::endl;

			for (json::array::const_iterator it = obj.as_array().cbegin(); it != obj.as_array().cend(); ++it)
			{
				//std::wcout << it->as << std::endl;
				const json::value& key1 = it->at(U("UserAccount"));
				const json::value& key2 = it->at(U("Password"));
				const json::value& key3 = it->at(U("FullName"));
				const json::value& key4 = it->at(U("Email"));
				const json::value& key5 = it->at(U("Birthday"));

				std::wcout << L"UserAccount: " << key1.as_string().c_str() << std::endl;
				std::wcout << L"Password: " << key2.as_string().c_str() << std::endl;
				std::wcout << L"FullName: " << key3.as_string().c_str() << std::endl;
				std::wcout << L"Email: " << key4.as_string().c_str();
				std::wcout << L"Birthday: " << key5.as_string().c_str() << std::endl;

				//ProcessingJSON(key1);
				//ProcessingJSON(key2);
				//ProcessingJSON(key3);
				//ProcessingJSON(key4);sssss
				//ProcessingJSON(key5);
			}
		}
		else if (obj.is_string())
			std::wcout << L"JSON is String !\n" << obj.as_string() << std::endl;
	}
	else
	{
		std::wcout << L"Data is NULL or Dont' know !!" << std::endl;
	}

}