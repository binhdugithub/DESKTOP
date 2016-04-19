/*
 * RESTHandler.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: root
 */

#include "RESTHandler.h"

RESTHandler* RESTHandler::m_Instance = NULL;

RESTHandler::RESTHandler()
{


}

RESTHandler::~RESTHandler()
{
	// TODO Auto-generated destructor stub
}

RESTHandler* RESTHandler::GetSingleton()
{
	if(m_Instance == NULL)
	{
		m_Instance = new RESTHandler();
	}

	return m_Instance;
}

void RESTHandler::HandleGET(http_request p_request)
{
	std::cout << "HandleGET" << "__" << __FUNCTION__<< "__" << __FILE__<< std::endl;
	LOG_INFO("HandleGET: "<< p_request.absolute_uri().to_string());

	utility::string_t l_directory_path = p_request.relative_uri().path();

	std::cout << l_directory_path << std::endl;

	if(l_directory_path == "/stories")
	{
		FSProcessing::GetSingleton()->GetListStories(p_request);
	}
	else if(l_directory_path == "/story")
	{
		FSProcessing::GetSingleton()->GetStory(p_request);
	}
	else if(l_directory_path == "/apps")
	{
		FSProcessing::GetSingleton()->GetListApps(p_request);
	}

	return;

}

void RESTHandler::HandlePOST(http_request p_request)
{
	std::cout << "HandlePOST" << "__" << __FUNCTION__<< "__" << __FILE__<< std::endl;
	LOG_INFO("HandlePOST__"<< __FUNCTION__<< "__" << __FILE__);

	utility::string_t l_directory_path = p_request.relative_uri().path();

	std::cout << l_directory_path << std::endl;

	if(l_directory_path == "/stories")
	{
		FSProcessing::GetSingleton()->ReloadStories(p_request);
	}
	else if(l_directory_path == "/apps")
	{
		FSProcessing::GetSingleton()->ReloadApps(p_request);
	}

	p_request.reply(http::status_codes::OK);

}

void RESTHandler::HandlePUT(http_request p_request)
{
	std::cout << "HandlePUT" << "__" << __FUNCTION__<< "__" << __FILE__<< std::endl;
	LOG_INFO("HandlePUT__"<< __FUNCTION__<< "__" << __FILE__);

	utility::string_t l_directory_path = p_request.relative_uri().path();

	std::cout << l_directory_path << std::endl;

	if(l_directory_path == "/stories")
	{
		FSProcessing::GetSingleton()->UpdateStories(p_request);
	}
	else if(l_directory_path == "/apps")
	{
		FSProcessing::GetSingleton()->UpdateApps(p_request);
	}

	p_request.reply(http::status_codes::OK);

}

void RESTHandler::HandleDELETE(http_request p_request)
{
	std::cout << "HandleDELETE" << "__" << __FUNCTION__<< "__" << __FILE__<< std::endl;
	LOG_INFO("HandleDELETE__"<< __FUNCTION__<< "__" << __FILE__);

	p_request.reply(http::status_codes::OK);

}
