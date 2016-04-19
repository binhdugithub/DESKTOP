/*
 * FSProcessing.cpp
 *
 *  Created on: Dec 16, 2015
 *      Author: root
 */

#include "FSProcessing.h"


FSProcessing* FSProcessing::m_Instance = NULL;

FSProcessing::FSProcessing()
{
	// TODO Auto-generated constructor stub
	m_count = 0;

}

FSProcessing::~FSProcessing() {
	// TODO Auto-generated destructor stub
}


FSProcessing* FSProcessing::GetSingleton()
{
	if(m_Instance == NULL)
	{
		m_Instance = new FSProcessing();
	}

	return m_Instance;
}

void FSProcessing::GetListStories(http_request p_request)
{
	//std::cout << "Request list stories" << std::endl;
	//LOG_INFO("Request list stories");

	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_idstart = query_parameters.find(U("id_start"));
	auto found_limit = query_parameters.find(U("limit"));

	if (found_idstart == end(query_parameters) || (found_limit == end(query_parameters)))
	{
		std::cout << "Query parameter fail !!" << std::endl;
		LOG_ERROR("Query parameter fail !!");

		p_request.reply(http::status_codes::OK);

		return;
	}
	else
	{
		int l_idstart = std::atoi(utility::conversions::to_utf8string(found_idstart->second).c_str());
		int l_limit	= std::atoi(utility::conversions::to_utf8string(found_limit->second).c_str());



		if (l_idstart == 0)
		{
			m_count++;
			if (m_count > 1000000)
				m_count = 0;

			LOG_INFO("Count user: " << m_count);
		}

		//std::cout << "ID start:" << l_idstart << " limit:" << l_limit << std::endl;
		std::vector<std::vector<std::string> > l_stories = DBInterface::GetSingleton()->GetListStories(l_idstart, l_limit);

		if(l_stories.size() > 0)
		{
			json::value l_json_root;
			json::value l_json_stories;

			for (size_t i=0; i < l_stories.size(); i++)
			{
				std::vector<std::string> l_story = l_stories[i];
				json::value l_json_story;

				l_json_story[U("id")] = json::value::number(std::stoi(l_story[0]));
				l_json_story[U("title")] = json::value::string(utility::conversions::to_string_t(l_story[1]));
				l_json_story[U("content")] = json::value::string(utility::conversions::to_string_t(l_story[2]));
				l_json_story[U("image")] = json::value::string(utility::conversions::to_string_t(l_story[3]));
				l_json_story[U("audio")] = json::value::string(utility::conversions::to_string_t(l_story[4]));
				l_json_story[U("rate")] = json::value::number(std::stoi(l_story[5]));

				l_json_stories[i] = l_json_story;
			}


			l_json_root[U("stories")] = l_json_stories;
			p_request.reply(http::status_codes::OK, l_json_root);
		}
		else
		{
			p_request.reply(http::status_codes::OK);
		}
	}


	return;
}//End GetStories



void FSProcessing::GetStory(http_request p_request)
{
	//std::cout << "Request list stories" << std::endl;
	//LOG_INFO("Request list stories");

	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_id = query_parameters.find(U("id"));

	if (found_id == end(query_parameters))
	{
		std::cout << "Query parameter fail !!" << std::endl;
		LOG_ERROR("Query parameter fail !!");

		p_request.reply(http::status_codes::OK);

		return;
	}
	else
	{
		int l_id = std::atoi(utility::conversions::to_utf8string(found_id->second).c_str());

		//std::cout << "ID start:" << l_idstart << " limit:" << l_limit << std::endl;
		std::vector<std::string>  l_story = DBInterface::GetSingleton()->GetStory(l_id);

		if(l_story.size() > 0)
		{
			json::value l_json_story;

			for (size_t i=0; i < l_story.size(); i++)
			{
				l_json_story[U("id")] = json::value::number(std::stoi(l_story[0]));
				l_json_story[U("title")] = json::value::string(utility::conversions::to_string_t(l_story[1]));
				l_json_story[U("content")] = json::value::string(utility::conversions::to_string_t(l_story[2]));
				l_json_story[U("image")] = json::value::string(utility::conversions::to_string_t(l_story[3]));
				l_json_story[U("audio")] = json::value::string(utility::conversions::to_string_t(l_story[4]));
				l_json_story[U("rate")] = json::value::number(std::stoi(l_story[5]));

			}

			p_request.reply(http::status_codes::OK, l_json_story);
		}
		else
		{
			p_request.reply(http::status_codes::OK);
		}
	}


	return;
}//end GetStory()



//GetListApps
void FSProcessing::GetListApps(http_request p_request)
{
	std::cout << "Request list apps" << std::endl;
	LOG_INFO("Request list apps");

	std::vector<std::vector<std::string> > l_apps = DBInterface::GetSingleton()->GetListApps();

	if(l_apps.size() > 0)
	{
		json::value l_json_root;
		json::value l_json_apps;

		for (size_t i=0; i < l_apps.size(); i++)
		{
			std::vector<std::string> l_app = l_apps[i];
			json::value l_json_app;

			l_json_app[U("nameapp")] = json::value::string(utility::conversions::to_string_t(l_app[1]));
			l_json_app[U("imageurl")] = json::value::string(utility::conversions::to_string_t(l_app[2]));
			l_json_app[U("linkapp")] = json::value::string(utility::conversions::to_string_t(l_app[3]));

			l_json_apps[i] = l_json_app;
		}

		l_json_root[U("apps")] = l_json_apps;
		p_request.reply(http::status_codes::OK, l_json_root);
	}
	else
	{
		p_request.reply(http::status_codes::OK);
	}


	return;
}//End GetListApps


void FSProcessing::UpdateStories(http_request p_request)
{
	std::cout << "Request update stories" << std::endl;
	LOG_INFO("Request update stories");
	std::vector<std::vector<std::string> > l_stories = DBInterface::GetSingleton()->UpdateStories();

	if(l_stories.size() > 0)
	{
		json::value l_json_root;
		json::value l_json_stories;

		for (size_t i=0; i < l_stories.size(); i++)
		{
			std::vector<std::string> l_story = l_stories[i];
			json::value l_json_story;

			l_json_story[U("id")] = json::value::number(std::stoi(l_story[0]));
			l_json_story[U("title")] = json::value::string(utility::conversions::to_string_t(l_story[1]));
//			l_json_story[U("content")] = json::value::string(utility::conversions::to_string_t(l_story[2]));
//			l_json_story[U("image")] = json::value::string(utility::conversions::to_string_t(l_story[3]));
//			l_json_story[U("audio")] = json::value::string(utility::conversions::to_string_t(l_story[4]));
//			l_json_story[U("rate")] = json::value::number(std::stoi(l_story[5]));

			l_json_stories[i] = l_json_story;
		}


		l_json_root[U("stories")] = l_json_stories;
		p_request.reply(http::status_codes::OK, l_json_root);
	}
	else
	{
		std::cout << "update fail" << std::endl;
		LOG_ERROR("Update stories fail");
		p_request.reply(http::status_codes::OK);
	}


	return;
}//end Update Stories

void FSProcessing::UpdateApps(http_request p_request)
{
	std::cout << "Request update apps" << std::endl;
	LOG_INFO("Request update apps");

	std::vector<std::vector<std::string> > l_apps = DBInterface::GetSingleton()->UpdateApps();

	if(l_apps.size() > 0)
	{
		json::value l_json_root;
		json::value l_json_apps;

		for (size_t i=0; i < l_apps.size(); i++)
		{
			std::vector<std::string> l_app = l_apps[i];
			json::value l_json_app;

			l_json_app[U("id")] = json::value::string(utility::conversions::to_string_t(l_app[0]));
			l_json_app[U("nameapp")] = json::value::string(utility::conversions::to_string_t(l_app[1]));
			//l_json_app[U("imageurl")] = json::value::string(utility::conversions::to_string_t(l_app[2]));
			//l_json_app[U("linkapp")] = json::value::string(utility::conversions::to_string_t(l_app[3]));

			l_json_apps[i] = l_json_app;
		}

		l_json_root[U("apps")] = l_json_apps;
		p_request.reply(http::status_codes::OK, l_json_root);
	}
	else
	{
		p_request.reply(http::status_codes::OK);
	}


	return;
}//end Update Apps


void FSProcessing::ReloadStories(http_request p_request)
{
	std::cout << "Request reload stories" << std::endl;
	LOG_INFO("Request reload stories");
	std::vector<std::vector<std::string> > l_stories = DBInterface::GetSingleton()->ReloadStories();

	if(l_stories.size() > 0)
	{
		json::value l_json_root;
		json::value l_json_stories;

		for (size_t i=0; i < l_stories.size(); i++)
		{
			std::vector<std::string> l_story = l_stories[i];
			json::value l_json_story;

			l_json_story[U("id")] = json::value::number(std::stoi(l_story[0]));
			l_json_story[U("title")] = json::value::string(utility::conversions::to_string_t(l_story[1]));
//			l_json_story[U("content")] = json::value::string(utility::conversions::to_string_t(l_story[2]));
//			l_json_story[U("image")] = json::value::string(utility::conversions::to_string_t(l_story[3]));
//			l_json_story[U("audio")] = json::value::string(utility::conversions::to_string_t(l_story[4]));
//			l_json_story[U("rate")] = json::value::number(std::stoi(l_story[5]));

			l_json_stories[i] = l_json_story;
		}


		l_json_root[U("stories")] = l_json_stories;
		p_request.reply(http::status_codes::OK, l_json_root);
	}
	else
	{
		std::cout << "update fail" << std::endl;
		LOG_ERROR("Update stories fail");
		p_request.reply(http::status_codes::OK);
	}


	return;
}

void FSProcessing::ReloadApps(http_request p_request)
{
	std::cout << "Request update apps" << std::endl;
	LOG_INFO("Request update apps");

	std::vector<std::vector<std::string> > l_apps = DBInterface::GetSingleton()->ReloadApps();

	if(l_apps.size() > 0)
	{
		json::value l_json_root;
		json::value l_json_apps;

		for (size_t i=0; i < l_apps.size(); i++)
		{
			std::vector<std::string> l_app = l_apps[i];
			json::value l_json_app;

			l_json_app[U("id")] = json::value::string(utility::conversions::to_string_t(l_app[0]));
			l_json_app[U("nameapp")] = json::value::string(utility::conversions::to_string_t(l_app[1]));
			//l_json_app[U("imageurl")] = json::value::string(utility::conversions::to_string_t(l_app[2]));
			//l_json_app[U("linkapp")] = json::value::string(utility::conversions::to_string_t(l_app[3]));

			l_json_apps[i] = l_json_app;
		}

		l_json_root[U("apps")] = l_json_apps;
		p_request.reply(http::status_codes::OK, l_json_root);
	}
	else
	{
		p_request.reply(http::status_codes::OK);
	}


	return;
}

