#include "stdafx.h"
#include "RestProcessing.h"
#include "Define_Mif.h"
#include "LogFile.h"
#include "Configuration.h"
#include "Base64.h"
#include <stdio.h>
#include <boost/algorithm/string.hpp>



RestProcessing::RestProcessing()
{
	m_DBInf = new DatabaseInterface();
	m_LEDCTRL = new LedController();
}


RestProcessing::~RestProcessing()
{
	if (m_DBInf)
	{
		delete m_DBInf;
		m_DBInf = NULL;
	}

	if(m_LEDCTRL)
	{
		delete m_LEDCTRL;
		m_LEDCTRL = NULL;
	}
}

json::value RestProcessing::GenerateJsonCode(bool p_error, int p_status, std::string p_message , std::string p_description)
{
	json::value json_generation;
	json_generation[L"error"] = json::value::boolean(p_error);
	json_generation[L"status"] = json::value::number(p_status);
	json_generation[L"message"] = json::value::string(utility::conversions::to_string_t(p_message));
	json_generation[L"description"] = json::value::string(utility::conversions::to_string_t(p_description));

	return json_generation;
}

json::value RestProcessing::GenerateJsonCode(int p_code, std::string pDescription)
{
	//std::wcout << "JsonErrorResponse" << std::endl;
	switch (p_code)
	{
	case vms_ok:
	{
		return GenerateJsonCode(false, p_code, std::string("vms_ok"), pDescription);
		break;	
	}
	case unknow_url:
	{
		return GenerateJsonCode(true, p_code, std::string("unknow_url"), std::string(""));
		break;
	}

	case not_found_user:
	{
		return GenerateJsonCode(true, p_code, std::string("not_found_user"), std::string(""));
		break;
	}

	case wrong_password:
	{
		return GenerateJsonCode(true, p_code, std::string("wrong_password"), std::string(""));
		break;
	}

	case not_found_vms_device:
	{
		return GenerateJsonCode(true, p_code, std::string("not_found_vms_device"), std::string(""));
		break;
	}

	case not_found_program:
	{
		return GenerateJsonCode(true, p_code, std::string("not_found_program"), std::string(""));
		break;
	}

	case not_found_history:
	{
		return GenerateJsonCode(true, p_code, std::string("not_found_history"), std::string(""));
		break;
	}
	case get_list_history_failed:
	{
		return GenerateJsonCode(true, p_code, std::string("get_list_history_failed"), std::string(""));
		break;
	}
	case user_exist:
	{
		return GenerateJsonCode(true, p_code, std::string("user_exist"), std::string(""));
		break;
	}

	case template_name_exist:
	{
		return GenerateJsonCode(true, p_code, std::string("template_name_exist"), std::string(""));
		break;
	}

	case template_not_exist:
	{
		return GenerateJsonCode(true, p_code, std::string("template_not_exist"), std::string(""));
		break;
	}

	case not_match_content_type:
	{
		return GenerateJsonCode(true, p_code, std::string("not_match_content_type"), std::string(""));
		break;
	}

	case not_match_json_data:
	{
		return GenerateJsonCode(true, p_code, std::string("not_match_json_data"), std::string(""));
		break;
	}
	case insert_user_failed:
	{
		return GenerateJsonCode(true, p_code, std::string("insert_user_failed"), std::string(""));
		break;
	}

	case delete_user_failed:
	{
		return GenerateJsonCode(true, p_code, std::string("delete_user_failed"), std::string(""));
		break;
	}
	case update_user_failed:
	{
		return GenerateJsonCode(true, p_code, std::string("update_user_failed"), std::string(""));
		break;
	}
	case get_list_user_failed:
	{
		return GenerateJsonCode(true, p_code, std::string("get_list_user_failed"), std::string(""));
		break;
	}

	case insert_vms_failed:
	{
		return GenerateJsonCode(true, p_code, std::string("insert_vms_failed"), std::string(""));
		break;
	}

	case exist_vms_ip:
	{
		return GenerateJsonCode(true, p_code, std::string("exist_vms_ip"), std::string(""));
		break;
	}

	case exist_vms_name:
	{
		return GenerateJsonCode(true, p_code, std::string("exist_vms_name"), std::string(""));
		break;
	}

	case update_vms_failed:
	{
		return GenerateJsonCode(true, p_code, std::string("update_vms_failed"), std::string(""));
		break;
	}

	case delete_vms_failed:
	{
		return GenerateJsonCode(true, p_code, std::string("delete_vms_failed"), std::string(""));
		break;
	}
	case get_list_vms_failed:
	{
		return GenerateJsonCode(true, p_code, std::string("get_list_vms_failed"), std::string(""));
		break;
	}

	case insert_program_failed:
	{
		return GenerateJsonCode(true, p_code, std::string("insert_program_failed"), std::string(""));
		break;
	}

	case update_program_failed:
	{
		return GenerateJsonCode(true, p_code, std::string("update_program_failed"), std::string(""));
		break;
	}

	case delete_program_failed:
	{
		return GenerateJsonCode(true, p_code, std::string("delete_program_failed"), std::string(""));
		break;
	}
	case get_list_program_failed:
	{
		return GenerateJsonCode(true, p_code, std::string("get_list_program_failed"), std::string(""));
		break;
	}

	case apply_vms_ok:
	{
		return GenerateJsonCode(true, p_code, std::string("apply_vms_ok"), std::string(""));
		break;
	}
	case apply_vms_fail:
	{
		return GenerateJsonCode(true, p_code, std::string("apply_vms_fail"), std::string(""));
		break;
	}
	case not_found_parameter_user:
	{
		return GenerateJsonCode(true, p_code, std::string("not_found_parameter_user"), std::string(""));
		break;
	}

	default:
	{
		std::wcout << "Dont know error type " << std::endl;
		return GenerateJsonCode(true, p_code, std::string("dont_know_error_type"), std::string(""));
		break;
	}

	}

	return json::value();
}


void RestProcessing::DontKnowRequest(http_request p_request)
{
	std::wcout << "Request URL Unknow" << std::endl;

	json::value json_response = GenerateJsonCode(unknow_url);
	p_request.reply(http::status_codes::OK, json_response);

	return;
}

bool RestProcessing::IsHeaderJson(std::string p_header)
{
	if(p_header.find("application/json") == std::string::npos &&
		p_header.find("application\\json") == std::string::npos)
	{
		std::cout << p_header << std::endl;
		LOG_ERROR("Content-type != application/json");

		return false;
	}
	else
	{
		return true;
	}

	return false;
}


void RestProcessing::Login(http_request p_request)
{
	std::wcout << "Request login" << std::endl;
	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	auto found_password = query_parameters.find(L"pass");
	if (found_username == end(query_parameters))
	{
		std::wcout << "Query parameter fail !!" << std::endl;
		LOG_ERROR("Query parameter fail !!");
		json::value json_response = GenerateJsonCode(not_found_user);

		p_request.reply(http::status_codes::OK, json_response);

		return;
	}


	if (found_password == end(query_parameters))
	{
		std::wcout << "Query parameter fail: no attach password" << std::endl;
		LOG_ERROR("Query parameter fail: no attach password");
		json::value json_response = GenerateJsonCode(wrong_password);
		p_request.reply(http::status_codes::OK, json_response);

		return;
	}

	int l_roleid = m_DBInf->IsCorrectUser(utility::conversions::to_utf8string(found_username->second), utility::conversions::to_utf8string(found_password->second));
	if(l_roleid == -2)
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_found_user));
		LOG_ERROR("user not created");
	}
	else if(l_roleid == -1)
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(wrong_password));
		std::wcout << "is correct password" << std::endl;
		LOG_ERROR("is correct password");
	}
	else
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(vms_ok, std::to_string(l_roleid)));
		std::wcout << "Login successful" << std::endl;
		LOG_ERROR("login successful");
	}
	

	return;
};


void RestProcessing::GetRole(http_request p_request)
{
	std::wcout << "Request list role" << std::endl;
	LOG_INFO("Request list role");

	std::vector<vector<std::string> > l_array_role = m_DBInf->GetAllRole();
	//json::value root = json::value::array(l_array_role);
	
	if(l_array_role.size() > 0)
	{
		json::value l_root;
		json::value l_array;

		for (int i=0; i < l_array_role.size(); i++)
		{
			std::vector<std::string> l_vector_role = l_array_role[i];
			
			double id = -1;
			utility::string_t name(L"");

			id = stod(l_vector_role[0]);
			name = utility::conversions::to_string_t(l_vector_role[1]);

			json::value l_role;
			l_role[L"roleid"] = json::value::number(id);
			l_role[L"name"] = json::value::string(name);

			l_array[i] = l_role;
		}


		l_root[L"rolelist"] = l_array;
		p_request.reply(http::status_codes::OK, l_root);
	}
	else
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(get_list_role_failed));
	}

	return;
};


void RestProcessing::CreateUser(http_request p_request)
{
	std::wcout << "Request create user" << std::endl;
	LOG_INFO("Request create user");


	
	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		std::wcout << "CreateUser: Not fount username parameter" << std::endl;
		LOG_ERROR("CreateUser: Not fount username parameter");
		json::value json_response = GenerateJsonCode(not_found_parameter_user);
		p_request.reply(http::status_codes::OK, json_response);
		return;
	}
	
	if(p_request.headers().content_type() != L"application\\json" &&
	   p_request.headers().content_type() != L"application/json"	)
	{
		std::wcout << p_request.headers().content_type() << std::endl;
		std::wcout << L"Content-type != application/json" << std::endl;
		LOG_ERROR("Content-type != application/json");

		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_content_type));

		return;
	}

	pplx::task<json::value> task;

	try
	{
		task = p_request.extract_json();
	}
	catch(const http_exception &e)
	{
		std::wcout <<L"Cannot extract data to json" << std::endl;
		std::wcout << e.what() << std::endl;
		LOG_ERROR("Cannot extract data to json");
		LOG_ERROR(e.what());
	}

	try
	{
		const json::value  &json_request = task.get();
		
		std::string jv_username(""), jv_password(""), jv_fullname(""), 
			jv_birthday(""), jv_email(""), jv_phone(""), jv_currenttime(""),
			jv_address("");
		int jv_sex ,jv_roleid;
		if(json_request.is_object() ||
			json_request.is_array())
		{
			if(json_request.has_field(L"username"))
			{
				auto jv_temp = json_request.at(L"username");
				if(jv_temp.is_string())
					jv_username = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"address"))
			{
				auto jv_temp = json_request.at(L"address");
				if(jv_temp.is_string())
					jv_address = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"password"))
			{
				auto jv_temp = json_request.at(L"password");
				if(jv_temp.is_string())
					jv_password = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"fullname"))
			{
				auto jv_temp = json_request.at(L"fullname");
				if(jv_temp.is_string())
					jv_fullname = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"sex"))
			{
				auto jv_temp = json_request.at(L"sex");
				if(jv_temp.is_number())
					jv_sex = jv_temp.as_integer();
			}

			if(json_request.has_field(L"birthday"))
			{
				auto jv_temp = json_request.at(L"birthday");
				if(jv_temp.is_string())
					jv_birthday = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"email"))
			{
				auto jv_temp = json_request.at(L"email");
				if(jv_temp.is_string())
					jv_email = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"phone"))
			{
				auto jv_temp = json_request.at(L"phone");
				if(jv_temp.is_string())
					jv_phone = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"currenttime"))
			{
				auto jv_temp = json_request.at(L"currenttime");
				if(jv_temp.is_string())
					jv_currenttime = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"roleid"))
			{
				auto jv_temp = json_request.at(L"roleid");
				if(jv_temp.is_number())
					jv_roleid = jv_temp.as_integer() ;
			}
			
		}
		else if(json_request.is_string())
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));

			std::cout << L"Json is string" << std::endl;
			LOG_ERROR("Json is string");
		}
		
		if(!m_DBInf->ExistUserName(jv_username))
		{

			if(m_DBInf->InsertUser(jv_username, jv_password, jv_fullname, jv_sex, jv_birthday, jv_email, jv_phone, jv_currenttime, jv_roleid, jv_address))
			{
				p_request.reply(http::status_codes::OK, GenerateJsonCode(vms_ok));
			}
			else
			{
				p_request.reply(http::status_codes::OK, GenerateJsonCode(user_exist));
			}
		}
		else
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(user_exist));
		}

		string l_description = "Add user: " + jv_username;
		l_description += ", Full name: " + jv_fullname;
		m_DBInf->InsertHistory(utility::conversions::to_utf8string(found_username->second),  ADD_USER, utility::conversions::to_utf8string(l_description));

	}
	catch (const http_exception& e)
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
		std::wcout << e.what() << std::endl;
		LOG_ERROR(e.what());
	}

	task.wait();

	//p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
	return;
};


void RestProcessing::DeleteUser(http_request p_request)
{
	std::wcout << "Request Delete User" << std::endl;
	LOG_INFO("Request Delete User");

	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		std::wcout << "DeleteUser: Not fount username parameter" << std::endl;
		LOG_ERROR("DeleteUser: Not fount username parameter");
		json::value json_response = GenerateJsonCode(not_found_parameter_user);
		p_request.reply(http::status_codes::OK, json_response);
		return;
	}

	auto found_account = query_parameters.find(L"accountname");
	if (found_account == end(query_parameters))
	{
		std::wcout << "Query parameter fail !!" << std::endl;
		LOG_ERROR("Query parameter fail !!");
		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_found_user));
		return;
	}

	if (m_DBInf->DeleteUser(utility::conversions::to_utf8string(found_account->second)))
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(vms_ok));
		std::wcout << "Delete user : " << found_account->second << " sucessful" << std::endl;
		LOG_ERROR("Delte user succesful");
	}
	else
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(wrong_password));
		std::wcout << "Delete user: "<< found_account->second << " failed" << std::endl;
		LOG_ERROR("Delte user failed");
	}

	std::string l_description = std::string("Delete user: ") + utility::conversions::to_utf8string(found_account->second);
	//l_description += std::string("\nFull name: ") + jv_fullname;
	m_DBInf->InsertHistory(utility::conversions::to_utf8string(found_username->second),  DELETE_USER, l_description);

	return;
};

void RestProcessing::UpdateUser(http_request p_request)
{
	std::wcout << "Request update user" << std::endl;
	LOG_INFO("Request update user");

	
	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		std::wcout << "UpdateUser: Not fount username parameter" << std::endl;
		LOG_ERROR("UpdateUser: Not fount username parameter");
		json::value json_response = GenerateJsonCode(not_found_parameter_user);
		p_request.reply(http::status_codes::OK, json_response);
		return;
	}


	if(p_request.headers().content_type() != L"application\\json" &&
	   p_request.headers().content_type() != L"application/json"	)
	{
		std::wcout << p_request.headers().content_type() << std::endl;
		std::wcout << L"Content-type != application/json" << std::endl;
		LOG_ERROR("Content-type != application/json");

		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_content_type));

		return;
	}

	pplx::task<json::value> task;

	try
	{
		task = p_request.extract_json();
	}
	catch(const http_exception &e)
	{
		std::wcout <<L"Cannot extract data to json" << std::endl;
		std::wcout << e.what() << std::endl;
		LOG_ERROR("Cannot extract data to json");
		LOG_ERROR(e.what());
	}

	try
	{
		const json::value  &json_request = task.get();
		
		std::string jv_username(""), jv_password(""), jv_fullname(""), jv_birthday(""), 
			jv_email(""), jv_phone(""), jv_currenttime(""),
			jv_address("");
		int jv_sex = INT_MAX,jv_roleid = INT_MAX;

		if(json_request.is_object() ||
			json_request.is_array())
		{
			if(json_request.has_field(L"username"))
			{
				auto jv_temp = json_request.at(L"username");
				if(jv_temp.is_string())
					jv_username = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"address"))
			{
				auto jv_temp = json_request.at(L"address");
				if(jv_temp.is_string())
					jv_address = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"password"))
			{
				auto jv_temp = json_request.at(L"password");
				if(jv_temp.is_string())
					jv_password = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"fullname"))
			{
				auto jv_temp = json_request.at(L"fullname");
				if(jv_temp.is_string())
					jv_fullname = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"sex"))
			{
				auto jv_temp = json_request.at(L"sex");
				if(jv_temp.is_number())
					jv_sex = jv_temp.as_integer();
			}

			if(json_request.has_field(L"birthday"))
			{
				auto jv_temp = json_request.at(L"birthday");
				if(jv_temp.is_string())
					jv_birthday = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"email"))
			{
				auto jv_temp = json_request.at(L"email");
				if(jv_temp.is_string())
					jv_email = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"phone"))
			{
				auto jv_temp = json_request.at(L"phone");
				if(jv_temp.is_string())
					jv_phone = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"currenttime"))
			{
				auto jv_temp = json_request.at(L"currenttime");
				if(jv_temp.is_string())
					jv_currenttime = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"roleid"))
			{
				auto jv_temp = json_request.at(L"roleid");
				if(jv_temp.is_number())
					jv_roleid = jv_temp.as_integer() ;
			}
			
		}
		else if(json_request.is_string())
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));

			std::cout << L"Json is string" << std::endl;
			LOG_ERROR("Json is string");
		}
		
		if(m_DBInf->UpdateUser(jv_username, jv_password, jv_fullname, jv_sex, jv_birthday, jv_email, jv_phone, jv_currenttime, jv_roleid, jv_address))
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(vms_ok));
		}
		else
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(not_found_user));
		}

		string l_description = "Update user: " + jv_username;
		//l_description += std::string("\nFull name: ") + jv_fullname;
		//std::string l_description("");
		m_DBInf->InsertHistory(utility::conversions::to_utf8string(found_username->second),  UPDATE_USER, l_description);

	}
	catch (const http_exception& e)
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
		std::wcout << e.what() << std::endl;
		LOG_ERROR(e.what());
	}

	task.wait();

	return;
};


void RestProcessing::GetListUser(http_request p_request)
{
	std::wcout << "Request Get list User" << std::endl;
	std::vector<vector<std::string> > l_array_user = m_DBInf->GetAllUser();

	if(l_array_user.size() > 0)
	{
		json::value l_root;
		json::value l_array;

		for (int i=0; i < l_array_user.size(); i++)
		{
			std::vector<std::string> l_vector_user = l_array_user[i];
			
			double id = -1;
			
			json::value l_user;
			if(l_vector_user[0].length() > 0)
			l_user[L"username"]		= json::value::string(utility::conversions::to_string_t(l_vector_user[0]));
			if(l_vector_user[1].length() > 0)
			l_user[L"fullname"]		= json::value::string(utility::conversions::to_string_t(l_vector_user[1]));
			if(l_vector_user[2].length() > 0)
			l_user[L"sex"]			= json::value::number(stoi(l_vector_user[2]));
			if(l_vector_user[3].length() > 0)
			l_user[L"birthday"]		= json::value::string(utility::conversions::to_string_t(l_vector_user[3]));
			if(l_vector_user[4].length() > 0)
			l_user[L"email"]		= json::value::string(utility::conversions::to_string_t(l_vector_user[4]));
			if(l_vector_user[5].length() > 0)
			l_user[L"phone"]		= json::value::string(utility::conversions::to_string_t(l_vector_user[5]));
			if(l_vector_user[6].length() > 0)
			l_user[L"currenttime"]	= json::value::string(utility::conversions::to_string_t(l_vector_user[6]));
			if(l_vector_user[7].length() > 0)
			l_user[L"roleId"]		= json::value::number(stoi(l_vector_user[7]));
			if(l_vector_user[8].length() > 0)
			l_user[L"address"]	= json::value::string(utility::conversions::to_string_t(l_vector_user[8]));
			if(l_vector_user[9].length() > 0)
			l_user[L"password"]	= json::value::string(utility::conversions::to_string_t(l_vector_user[9]));

			l_array[i] = l_user;
		}

		l_root[L"userlist"] = l_array;
		p_request.reply(http::status_codes::OK, l_root);
	}
	else
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(get_list_user_failed));
	}

	return;
};

void RestProcessing::AssignObject(http_request p_request)
{
	std::wcout << "Request Assign Object" << std::endl;
	LOG_INFO("Request Assign Object");

	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		std::wcout << "AssignObject: Not fount username parameter" << std::endl;
		LOG_ERROR("AssignObject: Not fount username parameter");
		json::value json_response = GenerateJsonCode(not_found_parameter_user);
		p_request.reply(http::status_codes::OK, json_response);
		return;
	}

	//std::wcout << p_request.to_string() << std::endl
	if(p_request.headers().content_type() != L"application\\json" &&
	   p_request.headers().content_type() != L"application/json"	)
	{
		std::wcout << p_request.headers().content_type() << std::endl;
		std::wcout << L"Content-type != application/json" << std::endl;
		LOG_ERROR("Content-type != application/json");

		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_content_type));

		return;
	}

	pplx::task<json::value> task;

	try
	{
		task = p_request.extract_json();
	}
	catch(const http_exception &e)
	{
		std::wcout <<L"Cannot extract data to json" << std::endl;
		std::wcout << e.what() << std::endl;
		LOG_ERROR("Cannot extract data to json");
		LOG_ERROR(e.what());
	}

	try
	{
		const json::value  &json_request = task.get();
		
		std::string jv_username("");
		std::vector<int> l_listid;

		if(json_request.is_object() ||
			json_request.is_array())
		{
			if(json_request.has_field(L"username"))
			{
				auto jv_temp = json_request.at(L"username");
				if(jv_temp.is_string())
					jv_username = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"VMS"))
			{
				json::value l_array =  json_request.at(L"VMS");
				if(l_array.is_array())
				{
					for(int i=0; i < l_array.size(); i++)
					{
						json::value jv_vms = l_array[i];
						if(jv_vms.has_field(L"VmsId"))
						{
							auto jv_id = jv_vms[L"VmsId"];
							int id = -1;
							if(jv_id.is_string())
							{
								 id = stoi(jv_id.as_string());
							}
							else if(jv_id.is_number())
							{
								 id = jv_id.as_integer();
							}

							l_listid.push_back(id);
						}
					}
				}
				else
				{
					p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
					std::wcout << "List VMSid is not a array" << std::endl;
					LOG_ERROR("List VMSid is not a array");

					return;
				}
			}
			else
			{
				p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
				std::wcout << "json message don't have field VMS" << std::endl;
				LOG_ERROR("json message don't have field VMS");

				return;
			}

		}
		else if(json_request.is_string())
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));

			std::cout << L"Json is string" << std::endl;
			LOG_ERROR("Json is string");

			return;
		}
		
		if(m_DBInf->AssignVMS(jv_username, l_listid))
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(vms_ok));
		}
		else
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(assign_list_vms_failed));
		}

		m_DBInf->InsertHistory(utility::conversions::to_utf8string(found_username->second),  ASSIGN_OBJECT, "");

	}
	catch (const http_exception& e)
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
		std::wcout << e.what() << std::endl;
		LOG_ERROR(e.what());
	}

	task.wait();

	return;
};


void RestProcessing::DeleteObject(http_request p_request)
{
	std::wcout << "Request Delete Device" << std::endl;

	
	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		std::wcout << "DeleteObject: Not fount username parameter" << std::endl;
		LOG_ERROR("DeleteObject: Not fount username parameter");
		json::value json_response = GenerateJsonCode(not_found_parameter_user);
		p_request.reply(http::status_codes::OK, json_response);
		return;
	}
	
	auto found_id = query_parameters.find(L"vmsid");
	if (found_id == end(query_parameters))
	{
		std::wcout << "Query parameter fail !!" << std::endl;
		LOG_ERROR("Query parameter fail !!");
		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_found_user));
		return;
	}

	int id = std::stoi(found_id->second);

	if (m_DBInf->DeleteObject(id))
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(vms_ok));
		std::wcout << "Delete OBject : " << found_id->second << " sucessful" << std::endl;
		LOG_ERROR("Delte OBject succesful");
	}
	else
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(delete_vms_failed));
		std::wcout << "Delete OBject: "<< found_id->second << " failed" << std::endl;
		LOG_ERROR("Delte OBject failed");
	}

	std::string l_description = std::string("Delete vmsid: ") + utility::conversions::to_utf8string(found_id->second);
	//l_description += std::string("\nFull name: ") + jv_fullname;
	m_DBInf->InsertHistory(utility::conversions::to_utf8string(found_username->second),  DELETE_OBJECT, l_description);

	return;
};


void RestProcessing::CreateObject(http_request p_request)
{
	std::wcout << "Request Create Object" << std::endl;
	LOG_INFO("Request Create Object");

	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		std::wcout << "CreateObject: Not fount username parameter" << std::endl;
		LOG_ERROR("CreateObject: Not fount username parameter");
		json::value json_response = GenerateJsonCode(not_found_parameter_user);
		p_request.reply(http::status_codes::OK, json_response);
		return;
	}

	if(p_request.headers().content_type() != L"application\\json" &&
	   p_request.headers().content_type() != L"application/json"	)
	{
		std::wcout << p_request.headers().content_type() << std::endl;
		std::wcout << L"Content-type != application/json" << std::endl;
		LOG_ERROR("Content-type != application/json");

		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_content_type));

		return;
	}

	pplx::task<json::value> task;

	try
	{
		task = p_request.extract_json();
	}
	catch(const http_exception &e)
	{
		std::wcout <<L"Cannot extract data to json" << std::endl;
		std::wcout << e.what() << std::endl;
		LOG_ERROR("Cannot extract data to json");
		LOG_ERROR(e.what());
	}

	try
	{
		const json::value  &json_request = task.get();
		
		std::string jv_name(""),jv_program(""), jv_screenshot(""), jv_location(""), jv_ip(""), jv_description("");
		int jv_port = INT_MAX, jv_deviceid = INT_MAX, jv_status = INT_MAX;

		if(json_request.is_object() ||
			json_request.is_array())
		{
			if(json_request.has_field(L"name"))
			{
				auto jv_temp = json_request.at(L"name");
				if(jv_temp.is_string())
					jv_name = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			
			if(json_request.has_field(L"deviceid"))
			{
				auto jv_temp = json_request.at(L"deviceid");
				if(jv_temp.is_string())
				{
					jv_deviceid = stoi(jv_temp.as_string());
				}
				else if(jv_temp.is_number())
				{
					jv_deviceid = jv_temp.as_integer();
				}
			}

			if(json_request.has_field(L"location"))
			{
				auto jv_temp = json_request.at(L"location");
				if(jv_temp.is_string())
					jv_location = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"ip"))
			{
				auto jv_temp = json_request.at(L"ip");
				if(jv_temp.is_string())
					//jv_content = utility::conversions::to_utf8string(jv_temp.serialize());
						jv_ip = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"port"))
			{
				auto jv_temp = json_request.at(L"port");
				if(jv_temp.is_string())
				{
					jv_port = stoi(jv_temp.as_string());
				}
				else if(jv_temp.is_number())
				{
					jv_port = jv_temp.as_integer();
				}
			}

			
			if(json_request.has_field(L"description"))
			{
				auto jv_temp = json_request.at(L"description");
				if(jv_temp.is_string())
					jv_description = utility::conversions::to_utf8string(jv_temp.as_string());
			}


		}
		else if(json_request.is_string())
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));

			std::cout << L"Json is string" << std::endl;
			LOG_ERROR("Json is string");
		}
		
		if(m_DBInf->ExistObjectIP(jv_ip))
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(exist_vms_ip));
		}
		else if(m_DBInf->ExistObjectName(jv_name))
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(exist_vms_name));
		}
		else
		{
			int id_inserted = m_DBInf->InsertObject(jv_name, jv_ip, jv_port, jv_description, jv_location, jv_deviceid, jv_program, jv_screenshot, jv_status);
		
			if(id_inserted > 0)
			{
				p_request.reply(http::status_codes::OK, GenerateJsonCode(vms_ok, std::to_string(id_inserted)));
			}
			else
			{
				p_request.reply(http::status_codes::OK, GenerateJsonCode(insert_vms_failed));
			}
		}

		std::string l_description = std::string("VMS name:") + jv_name;
		l_description += std::string("\nVMS ip:") + jv_ip;
		m_DBInf->InsertHistory(utility::conversions::to_utf8string(found_username->second),  ADD_OBJECT, l_description);

	}
	catch (const http_exception& e)
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
		std::wcout << e.what() << std::endl;
		LOG_ERROR(e.what());
	}

	task.wait();
	return;
};



void RestProcessing::UpdateObject(http_request p_request)
{
	std::wcout << "Request Update Object" << std::endl;
	LOG_INFO("Request Update Object");

	
	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		std::wcout << "UpdateObject: Not fount username parameter" << std::endl;
		LOG_ERROR("UpdateObject: Not fount username parameter");
		json::value json_response = GenerateJsonCode(not_found_parameter_user);
		p_request.reply(http::status_codes::OK, json_response);
		return;
	}


	if(p_request.headers().content_type() != L"application\\json" &&
	   p_request.headers().content_type() != L"application/json"	)
	{
		std::wcout << p_request.headers().content_type() << std::endl;
		std::wcout << L"Content-type != application/json" << std::endl;
		LOG_ERROR("Content-type != application/json");

		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_content_type));

		return;
	}

	pplx::task<json::value> task;

	try
	{
		task = p_request.extract_json();
	}
	catch(const http_exception &e)
	{
		std::wcout <<L"Cannot extract data to json" << std::endl;
		std::wcout << e.what() << std::endl;
		LOG_ERROR("Cannot extract data to json");
		LOG_ERROR(e.what());
	}

	try
	{
		const json::value  &json_request = task.get();
		
		std::string jv_name(""),jv_program(""), jv_screenshot(""), jv_location(""), jv_ip(""), jv_description("");
		int jv_port = INT_MAX, jv_deviceid = INT_MAX, jv_status = INT_MAX, jv_id = INT_MAX;

		if(json_request.is_object() ||
			json_request.is_array())
		{
			//1.
			if(json_request.has_field(L"name"))
			{
				auto jv_temp = json_request.at(L"name");
				if(jv_temp.is_string())
					jv_name = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			//2
			if(json_request.has_field(L"deviceid"))
			{
				auto jv_temp = json_request.at(L"deviceid");
				if(jv_temp.is_string())
				{
					jv_deviceid = stoi(jv_temp.as_string());
				}
				else if(jv_temp.is_number())
				{
					jv_deviceid = jv_temp.as_integer();
				}
			}

			//3
			if(json_request.has_field(L"location"))
			{
				auto jv_temp = json_request.at(L"location");
				if(jv_temp.is_string())
					jv_location = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			//4
			if(json_request.has_field(L"ip"))
			{
				auto jv_temp = json_request.at(L"ip");
				if(jv_temp.is_string())
					//jv_content = utility::conversions::to_utf8string(jv_temp.serialize());
						jv_ip = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			//5
			if(json_request.has_field(L"port"))
			{
				auto jv_temp = json_request.at(L"port");
				if(jv_temp.is_string())
				{
					jv_port = stoi(jv_temp.as_string());
				}
				else if(jv_temp.is_number())
				{
					jv_port = jv_temp.as_integer();
				}
			}

			//6
			if(json_request.has_field(L"description"))
			{
				auto jv_temp = json_request.at(L"description");
				if(jv_temp.is_string())
					jv_description = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			//7
			if(json_request.has_field(L"program"))
			{
				auto jv_temp = json_request.at(L"program");
				if(jv_temp.is_string())
					jv_program = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			//8
			if(json_request.has_field(L"screenshot"))
			{
				auto jv_temp = json_request.at(L"screenshot");
				if(jv_temp.is_string())
					jv_screenshot = utility::conversions::to_utf8string(jv_temp.as_string());
			}
			//9
			if(json_request.has_field(L"status"))
			{
				auto jv_temp = json_request.at(L"status");
				if(jv_temp.is_string())
					jv_status = stoi(jv_temp.as_string());
				else if (jv_temp.is_integer())
					jv_status = jv_temp.as_integer();
			}
			//10
			if(json_request.has_field(L"id"))
			{
				auto jv_temp = json_request.at(L"id");
				if(jv_temp.is_string())
					jv_id = stoi(jv_temp.as_string());
				else if(jv_temp.is_integer())
					jv_id = jv_temp.as_integer();
			}

		}
		else if(json_request.is_string())
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));

			std::cout << L"Json is string" << std::endl;
			LOG_ERROR("Json is string");
		}
		
		/*if(m_DBInf->ExistObjectName(jv_name))
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(exist_vms_name));

		}
		else if(m_DBInf->ExistObjectName(jv_ip))
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(exist_vms_ip));
		}
		else*/
		{
			int succesful = m_DBInf->UpdateObject(jv_id, jv_name, jv_ip, jv_port, jv_description, jv_location, jv_deviceid, jv_program, jv_screenshot, jv_status);
			if(succesful == 1)
			{
				p_request.reply(http::status_codes::OK, GenerateJsonCode(vms_ok));
			}
			else
			{
				p_request.reply(http::status_codes::OK, GenerateJsonCode(succesful));
			}
		}


		//std::string l_description = std::string("Delete user: ") + utility::conversions::to_utf8string(found_account->second);
		//l_description += std::string("\nFull name: ") + jv_fullname;
		std::string l_description("");
		m_DBInf->InsertHistory(utility::conversions::to_utf8string(found_username->second),  UPDATE_OBJECT, l_description);
	}
	catch (const http_exception& e)
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
		std::wcout << e.what() << std::endl;
		LOG_ERROR(e.what());
	}

	task.wait();

	return;
};

void RestProcessing::UpdateObjectProgram(http_request p_request)
{
	std::wcout << "Request Update tree program" << std::endl;
	std::wcout << p_request.relative_uri().to_string() << std::endl;
	LOG_INFO("Request Update tree program");

	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		std::wcout << "UpdateObjectProgram: Not fount username parameter" << std::endl;
		LOG_ERROR("UpdateObjectProgram: Not fount username parameter");
		json::value json_response = GenerateJsonCode(not_found_parameter_user);
		p_request.reply(http::status_codes::OK, json_response);
		return;
	}

	if(p_request.headers().content_type() != L"application\\json" &&
	   p_request.headers().content_type() != L"application/json")
	{
		std::wcout << p_request.headers().content_type() << std::endl;
		std::wcout << L"Content-type != application/json" << std::endl;
		LOG_ERROR("Content-type != application/json");

		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_content_type));

		return;
	}

	pplx::task<json::value> task;

	try
	{
		task = p_request.extract_json();
	}
	catch(const http_exception &e)
	{
		std::wcout <<L"Cannot extract data to json" << std::endl;
		std::wcout << e.what() << std::endl;
		LOG_ERROR("Cannot extract data to json");
		LOG_ERROR(e.what());
	}

	try
	{
		json::value  &json_request = task.get();

		if(json_request.is_object() ||
			json_request.is_array())
		{
			if(!json_request.has_field(L"programs"))
			{
				p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
				std::wcout << "no filed programs" << std::endl;
				LOG_ERROR("no filed programs");
				return;
			}
			
			auto jv_program = json_request.at(L"programs");
			if(jv_program.is_null())
			{
				p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
				std::wcout << "programs is null " << std::endl;
				LOG_ERROR("programs is null");

				return;
			}
			
			for(int i = 0; i < jv_program.size(); i++)
			{
				json::value jv_vms = jv_program[i];
				int jv_id = INT_MAX;
				json::value jv_text = NULL, jv_iamge = NULL;
				std::string jv_imagebase64(""), l_pathscreenshot("");
			
				if(jv_vms.has_field(L"vmsId"))
				{
					auto jv_temp = jv_vms.at(L"vmsId");
					if(jv_temp.is_null())
						continue;

					if(jv_temp.is_string())
					{
						jv_id = stoi(utility::conversions::to_utf8string(jv_temp.as_string()));
					}
					else
					{
						jv_id = jv_temp.as_integer();
					}
				
				}
				else
				{
					p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
					continue;
				}

				if(jv_vms.has_field(L"text"))
				{
					jv_text = jv_vms.at(L"text");
				}

				if(jv_vms.has_field(L"image"))
				{
					jv_iamge = jv_vms.at(L"image");
				}

				if(jv_vms.has_field(L"imagedata"))
				{
					auto jv_temp = jv_vms.at(L"imagedata");
					if(jv_temp.is_string())
					{
						jv_imagebase64 = utility::conversions::to_utf8string(jv_temp.as_string());
						std::string l_name_screenshot = std::to_string(jv_id) + std::string(".jpg");
						l_pathscreenshot = Configuration::GetSingleTon()->st_screenshot + std::string("/") + l_name_screenshot;
						
						size_t ret = 0;
						int leng = Base64::Base64decode_len(jv_imagebase64.c_str());
						char *result = (char*)malloc(leng * sizeof(char));
						Base64::Base64decode(result, jv_imagebase64.c_str());

						FILE *file;
						file = fopen(l_pathscreenshot.c_str(), "wb");
						if(file)
						{
							fwrite((const void*)result, sizeof(char), leng, file);
							fclose(file);
							l_pathscreenshot = Configuration::GetSingleTon()->st_http_screenshot + std::string("/") + l_name_screenshot;

							free(result);
						}
						else
						{
							l_pathscreenshot = std::string("");
						}

					}
				}

				json::value program;
				program[L"text"] = jv_text;
				program[L"image"] = jv_iamge;
				std::string str_content = utility::conversions::to_utf8string(program.serialize());
							
				if(m_DBInf->UpdateObject(jv_id, std::string(""), std::string(""),INT_MAX,  std::string(""), std::string(""),INT_MAX,str_content, l_pathscreenshot,INT_MAX) == 1)
				{
					LOG_ERROR("Update object ok");

					if(m_LEDCTRL->UpdateProgram(jv_id)  == 0)
					{
						LOG_INFO("Update program ok");
						std::cout << "Update program ok" << std::endl;
					}
					else
					{
						LOG_ERROR("Update program failed");
						std::cout << "Update program failed" << std::endl;
						p_request.reply(http::status_codes::OK, GenerateJsonCode(apply_vms_fail));
						return;
					}
				}
				else
				{
					LOG_ERROR("Update object failed");
					std::cout << "Update object failed" << std::endl;
					p_request.reply(http::status_codes::OK, GenerateJsonCode(apply_vms_fail));
					return;
				}
			}
		}
		
		p_request.reply(http::status_codes::OK, GenerateJsonCode(apply_vms_ok));


		//std::string l_description = std::string("Delete user: ") + utility::conversions::to_utf8string(found_account->second);
		//l_description += std::string("\nFull name: ") + jv_fullname;
		std::string l_description("");
		m_DBInf->InsertHistory(utility::conversions::to_utf8string(found_username->second),  UPDATE_OBJECT_PROGRAM, l_description);

	}
	catch (const http_exception& e)
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
		std::wcout << e.what() << std::endl;
		LOG_ERROR(e.what());
	}

	task.wait();
	return;
}

void RestProcessing::GetListObject(http_request p_request)
{
	std::wcout << "Request Get list Object" << std::endl;
	LOG_INFO("Request Get list Object");

	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		std::wcout << "GetListObject: Not fount username parameter" << std::endl;
		LOG_ERROR("GetListObject: Not fount username parameter");
		json::value json_response = GenerateJsonCode(not_found_user);
		p_request.reply(http::status_codes::OK, json_response);
		return;
	}

	std::vector<vector<std::string> > l_array_object = m_DBInf->GetAllObject(utility::conversions::to_utf8string(found_username->second));

	if(l_array_object.size() > 0)
	{
		json::value l_root;
		json::value l_array;

		for (int i=0; i < l_array_object.size(); i++)
		{
			std::vector<std::string> l_v_object = l_array_object[i];
			json::value l_json_object;

			if(l_v_object[0].length() > 0)
				l_json_object[L"id"]		= json::value::number(stoi(l_v_object[0]));
			if(l_v_object[1].length() > 0)
				l_json_object[L"name"]	= json::value::string(utility::conversions::to_string_t(l_v_object[1]));
			if(l_v_object[2].length() > 0)
				l_json_object[L"ip"]		= json::value::string(utility::conversions::to_string_t(l_v_object[2]));
			if(l_v_object[3].length() > 0)
				l_json_object[L"port"]	= json::value::number(stoi(l_v_object[3]));
			if(l_v_object[4].length() > 0)
				l_json_object[L"description"]	= json::value::string(utility::conversions::to_string_t(l_v_object[4]));
			if(l_v_object[5].length() > 0)
				//l_json_object[L"program"]	= json::value::parse(utility::conversions::to_string_t(l_vector_role[5]));
				l_json_object[L"location"]	= json::value::string(utility::conversions::to_string_t(l_v_object[5]));
			if(l_v_object[6].length() > 0)
				l_json_object[L"deviceid"]	= json::value::number(stoi(l_v_object[6]));
			if(l_v_object[7].length() > 0)
				l_json_object[L"program"]	= json::value::string(utility::conversions::to_string_t(l_v_object[7]));
			if(l_v_object[8].length() > 0)
				l_json_object[L"screenshot"]	= json::value::string(utility::conversions::to_string_t(l_v_object[8]));
			if(l_v_object[9].length() > 0)
				l_json_object[L"status"]	= json::value::number(stoi(l_v_object[9]));
			if(l_v_object[10].length() > 0)
				l_json_object[L"manufacturer"]	= json::value::string(utility::conversions::to_string_t(l_v_object[10]));
			if(l_v_object[11].length() > 0)
				l_json_object[L"model"]	= json::value::string(utility::conversions::to_string_t(l_v_object[11]));
			if(l_v_object[12].length() > 0)
				l_json_object[L"width"]	= json::value::number(stod(l_v_object[12]));
			if(l_v_object[13].length() > 0)
				l_json_object[L"height"]	= json::value::number(stod(l_v_object[13]));
			if(l_v_object[14].length() > 0)
				l_json_object[L"ncolor"]	= json::value::number(stoi(l_v_object[14]));
			if(l_v_object[15].length() > 0)
			{
				json::value l_array_type;
				int i = 0;
				std::string delim = "|";
				auto start = 0U;
				auto end = l_v_object[15].find(delim);
				while (end != std::string::npos)
				{
					std::string l_vmstype = l_v_object[15].substr(start, end - start);
					std::cout << l_vmstype << std::endl;
					json::value l_json_vmstype;
					l_json_vmstype[L"typename"] = json::value::string(utility::conversions::to_string_t(l_vmstype));
					l_array_type[i++] = l_json_vmstype;

					start = end + delim.length();
					end = l_v_object[15].find(delim, start);
				}

				l_json_object[L"multitype"] = l_array_type;
			}

	
			l_array[i] = l_json_object;
		}

		l_root[L"objectlist"] = l_array;
		p_request.reply(http::status_codes::OK, l_root);
	}
	else
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(get_list_vms_failed));
		std::wcout << "Get list vms for " << found_username->second  <<" failed" << std::endl;
		LOG_ERROR("Get list vms failed");
	}

	return;
};


void RestProcessing::GetListMonitoring(http_request p_request)
{
	std::wcout << "Request Get list Object" << std::endl;
	LOG_INFO("Request Get list Object");

	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		std::wcout << "Query parameter fail !!" << std::endl;
		LOG_ERROR("Query parameter fail !!");
		json::value json_response = GenerateJsonCode(not_found_user);
		p_request.reply(http::status_codes::OK, json_response);

		return;
	}

	std::vector<vector<std::string> > l_array_object = m_DBInf->GetMonitoring(utility::conversions::to_utf8string(found_username->second));

	if(l_array_object.size() > 0)
	{
		json::value l_root;
		json::value l_array;

		for (int i=0; i < l_array_object.size(); i++)
		{
			std::vector<std::string> l_v_object = l_array_object[i];
			json::value l_json_object;

			if(l_v_object[0].length() > 0)
				l_json_object[L"name"]	= json::value::string(utility::conversions::to_string_t(l_v_object[0]));
			if(l_v_object[1].length() > 0)
				//l_json_object[L"program"]	= json::value::parse(utility::conversions::to_string_t(l_vector_role[5]));
				l_json_object[L"location"]	= json::value::string(utility::conversions::to_string_t(l_v_object[1]));
			if(l_v_object[2].length() > 0)
				l_json_object[L"width"]	= json::value::number(stod(l_v_object[2]));
			if(l_v_object[3].length() > 0)
				l_json_object[L"height"]	= json::value::number(stod(l_v_object[3]));
			if(l_v_object[4].length() > 0)
				l_json_object[L"status"]	= json::value::number(stoi(l_v_object[4]));

			if(l_v_object[5].length() > 0)
				l_json_object[L"screenshoturl"]	= json::value::string(utility::conversions::to_string_t(l_v_object[5]));
			else
				l_json_object[L"screenshoturl"]	= json::value::string(L"");

			if(l_v_object[6].length() > 0)
				l_json_object[L"id"]	= json::value::number(stoi(l_v_object[6]));

			if(l_v_object[7].length() > 0)
				l_json_object[L"ip"]	= json::value::string(utility::conversions::to_string_t(l_v_object[7]));

			if(l_v_object[8].length() > 0)
				l_json_object[L"program"]	= json::value::string(utility::conversions::to_string_t(l_v_object[8]));

			
			l_array[i] = l_json_object;
		}

		l_root[L"vmsmonitoring"] = l_array;
		p_request.reply(http::status_codes::OK, l_root);
	}
	else
	{
		json::value l_array;
		json::value l_root;
		l_root[L"vmsmonitoring"] = l_array;
		
		p_request.reply(http::status_codes::OK, l_root);
		//p_request.reply(http::status_codes::OK, GenerateJsonCode(get_list_vms_failed));
		//std::wcout << "Get list vms for " << found_username->second  <<" failed" << std::endl;
		LOG_ERROR("Get list vms failed");
	}

	return;
};
void RestProcessing::GetListProgram(http_request p_request)
{
	std::wcout << "Request Get list program" << std::endl;
	LOG_INFO("Request get list Program");

	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_id = query_parameters.find(L"id");

	//return all list program
	if (found_id == end(query_parameters))
	{
		std::wcout << "Get list program" << std::endl;

		std::vector<vector<std::string> > l_array_program = m_DBInf->GetAllProgram();
		if(l_array_program.size() > 0)
		{
			json::value l_root;
			json::value l_array;

			for (int i=0; i < l_array_program.size(); i++)
			{
				std::vector<std::string> l_vector_program = l_array_program[i];
				json::value l_program;

				if(l_vector_program[0].length() > 0)
				l_program[L"id"]		= json::value::number(stoi(l_vector_program[0]));
				if(l_vector_program[1].length() > 0)
				l_program[L"name"]		= json::value::string(utility::conversions::to_string_t(l_vector_program[1]));
				if(l_vector_program[2].length() > 0)
				l_program[L"type"]		= json::value::number(stoi(l_vector_program[2]));
				if(l_vector_program[4].length() > 0)
				l_program[L"width"]		= json::value::number(stoi(l_vector_program[4]));
				if(l_vector_program[5].length() > 0)
				l_program[L"height"]	= json::value::number(stoi(l_vector_program[5]));
				
				l_array[i] = l_program;
			}

			l_root[L"programs"] = l_array;
			p_request.reply(http::status_codes::OK, l_root);
		}
		else
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(get_list_program_failed));
		}
	}
	//return a detail program
	else
	{
		std::wcout << "Get list program" << std::endl;

		vector<std::string> l_program = m_DBInf->GetProgram(stoi(found_id->second));
		if(l_program.size() > 0)
		{
			json::value l_json_program;

			if(l_program[0].length() > 0)
			l_json_program[L"id"]		= json::value::number(stoi(l_program[0]));
			if(l_program[1].length() > 0)
			l_json_program[L"name"]		= json::value::string(utility::conversions::to_string_t(l_program[1]));
			if(l_program[2].length() > 0)
			l_json_program[L"type"]		= json::value::number(stoi(l_program[2]));
			if(l_program[3].length() > 0)
			//l_json_program[L"content"]	= json::value::parse(utility::conversions::to_string_t(l_program[3]));
			l_json_program[L"content"]	= json::value::string(utility::conversions::to_string_t(l_program[3]));
			if(l_program[4].length() > 0)
			l_json_program[L"width"]	= json::value::number(stoi(l_program[4]));
			if(l_program[5].length() > 0)
			l_json_program[L"height"]	= json::value::number(stoi(l_program[5]));
	
			p_request.reply(http::status_codes::OK, l_json_program);

		}else
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(get_list_program_failed));
		}
	}


	return;
}

void RestProcessing::CreateProgram(http_request p_request)
{
	std::wcout << "Request Create Template" << std::endl;
	LOG_INFO("Request Create Template");

	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		std::wcout << "CreateProgram: Not fount username parameter" << std::endl;
		LOG_ERROR("CreateProgram: Not fount username parameter");
		json::value json_response = GenerateJsonCode(not_found_parameter_user);
		p_request.reply(http::status_codes::OK, json_response);
		return;
	}

	if(p_request.headers().content_type() != L"application\\json" &&
	   p_request.headers().content_type() != L"application/json"	)
	{
		std::wcout << p_request.headers().content_type() << std::endl;
		std::wcout << L"Content-type != application/json" << std::endl;
		LOG_ERROR("Content-type != application/json");

		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_content_type));

		return;
	}

	pplx::task<json::value> task;

	try
	{
		task = p_request.extract_json();
	}
	catch(const http_exception &e)
	{
		std::wcout <<L"Cannot extract data to json" << std::endl;
		std::wcout << e.what() << std::endl;
		LOG_ERROR("Cannot extract data to json");
		LOG_ERROR(e.what());
	}

	try
	{
		const json::value  &json_request = task.get();
		
		std::string jv_name(""), jv_content("");
		int jv_type = INT_MAX;
		float jv_w = FLT_MAX, jv_h = FLT_MAX;

		if(json_request.is_object() ||
			json_request.is_array())
		{
			if(json_request.has_field(L"name"))
			{
				auto jv_temp = json_request.at(L"name");
				if(jv_temp.is_string())
					jv_name = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"width"))
			{
				auto jv_temp = json_request.at(L"width");
				if(jv_temp.is_string())
				{
					jv_w = stod(jv_temp.as_string());
				}
				else if(jv_temp.is_number())
				{
					jv_w = jv_temp.as_double();
				}
			}

			if(json_request.has_field(L"height"))
			{
				auto jv_temp = json_request.at(L"height");
				if(jv_temp.is_string())
				{
					jv_h = stod(jv_temp.as_string());
				}
				else if(jv_temp.is_number())
				{
					jv_h = jv_temp.as_double();
				}
			}



			if(json_request.has_field(L"type"))
			{
				auto jv_temp = json_request.at(L"type");
				if(jv_temp.is_string())
				{
					jv_type = stod(jv_temp.as_string());
				}
				else if(jv_temp.is_number())
				{
					jv_type = jv_temp.as_double();
				}
			}



			if(json_request.has_field(L"content"))
			{
				auto jv_temp = json_request.at(L"content");
				if(jv_temp.is_null())
				{
					p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
					std::cout << L"content is null" << std::endl;
					LOG_ERROR("content is null");
					return;
				}
				else
				{
					//jv_content = utility::conversions::to_utf8string(jv_temp.serialize());
					jv_content = utility::conversions::to_utf8string(jv_temp.as_string());
				}
			}
			
			
		}
		else if(json_request.is_string())
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));

			std::cout << L"Json is string" << std::endl;
			LOG_ERROR("Json is string");
		}
		
		if(m_DBInf->InsertProgram(jv_name, jv_type, jv_content, jv_w, jv_h) > 0)
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(vms_ok));
		}
		else
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(insert_program_failed));
		}

		m_DBInf->InsertHistory(utility::conversions::to_utf8string(found_username->second),  ADD_PROGRAM, "");

	}
	catch (const http_exception& e)
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
		std::wcout << e.what() << std::endl;
		LOG_ERROR(e.what());
	}

	task.wait();

	return;
};

void RestProcessing::UpdateProgram(http_request p_request)
{
	std::wcout << "Request Update Program" << std::endl;
	LOG_INFO("Request Update Program");

	
	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		std::wcout << "UpdateProgram: Not fount username parameter" << std::endl;
		LOG_ERROR("UpdateProgram: Not fount username parameter");
		json::value json_response = GenerateJsonCode(not_found_parameter_user);
		p_request.reply(http::status_codes::OK, json_response);
		return;
	}


	if(p_request.headers().content_type() != L"application\\json" &&
	   p_request.headers().content_type() != L"application/json"	)
	{
		std::wcout << p_request.headers().content_type() << std::endl;
		std::wcout << L"Content-type != application/json" << std::endl;
		LOG_ERROR("Content-type != application/json");

		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_content_type));

		return;
	}

	pplx::task<json::value> task;

	try
	{
		task = p_request.extract_json();
	}
	catch(const http_exception &e)
	{
		std::wcout <<L"Cannot extract data to json" << std::endl;
		std::wcout << e.what() << std::endl;
		LOG_ERROR("Cannot extract data to json");
		LOG_ERROR(e.what());
	}

	try
	{
		const json::value  &json_request = task.get();
		
		std::string jv_name(""), jv_content("");
		int jv_id = INT_MAX, jv_type = INT_MAX;
		float jv_w = FLT_MAX, jv_h = FLT_MAX;
	

		if(json_request.is_object() ||
			json_request.is_array())
		{
			if(json_request.has_field(L"id"))
			{
				auto jv_temp = json_request.at(L"id");
				if(jv_temp.is_string())
				{
					jv_id = stoi(jv_temp.as_string());
				}
				else if(jv_temp.is_number())
				{
					jv_id = jv_temp.as_integer();
				}
			}

			if(json_request.has_field(L"name"))
			{
				auto jv_temp = json_request.at(L"name");
				if(jv_temp.is_string())
					jv_name = utility::conversions::to_utf8string(jv_temp.as_string());
			}

			if(json_request.has_field(L"width"))
			{
				auto jv_temp = json_request.at(L"width");
				if(jv_temp.is_string())
				{
					jv_w = stod(jv_temp.as_string());
				}
				else if(jv_temp.is_number())
				{
					jv_w = jv_temp.as_double();
				}
			}

			if(json_request.has_field(L"height"))
			{
				auto jv_temp = json_request.at(L"height");
				if(jv_temp.is_string())
				{
					jv_h = stod(jv_temp.as_string());
				}
				else if(jv_temp.is_number())
				{
					jv_h = jv_temp.as_double();
				}
			}

			if(json_request.has_field(L"type"))
			{
				auto jv_temp = json_request.at(L"type");
				if(jv_temp.is_string())
				{
					jv_type = stod(jv_temp.as_string());
				}
				else if(jv_temp.is_number())
				{
					jv_type = jv_temp.as_double();
				}
			}

			if(json_request.has_field(L"content"))
			{
				auto jv_temp = json_request.at(L"content");
				if(jv_temp.is_null())
				{
					p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
					std::cout << L"content is null" << std::endl;
					LOG_ERROR("content is null");
					return;
				}
				else
				{
					jv_content = utility::conversions::to_utf8string(jv_temp.as_string());
				}
			}
			
		}
		else if(json_request.is_string())
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));

			std::cout << L"Json is string" << std::endl;
			LOG_ERROR("Json is string");
		}
		
		if(m_DBInf->UpdatetProgram(jv_id, jv_name, jv_type, jv_content, jv_w, jv_h))
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(vms_ok));
		}
		else
		{
			p_request.reply(http::status_codes::OK, GenerateJsonCode(update_program_failed));
		}

		//std::string l_description = std::string("Delete user: ") + utility::conversions::to_utf8string(found_account->second);
		//l_description += std::string("\nFull name: ") + jv_fullname;
		std::string l_description("");
		m_DBInf->InsertHistory(utility::conversions::to_utf8string(found_username->second),  UPDATE_PROGRAM, l_description);

	}
	catch (const http_exception& e)
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_match_json_data));
		std::wcout << e.what() << std::endl;
		LOG_ERROR(e.what());
	}

	task.wait();

	return;
};

void RestProcessing::DeleteProgram(http_request p_request)
{
	std::wcout << "Request Delete Program" << std::endl;
	LOG_INFO("Request Delete Program");

	
	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		std::wcout << "DeleteProgram: Not fount username parameter" << std::endl;
		LOG_ERROR("DeleteProgram: Not fount username parameter");
		json::value json_response = GenerateJsonCode(not_found_user);
		p_request.reply(http::status_codes::OK, json_response);
		return;
	}
	
	auto found_id = query_parameters.find(L"id");
	if (found_id == end(query_parameters))
	{
		std::wcout << "Query parameter fail !!" << std::endl;
		LOG_ERROR("Query parameter fail !!");
		p_request.reply(http::status_codes::OK, GenerateJsonCode(not_found_program));

		return;
	}

	int id = std::stoi(found_id->second);

	if (m_DBInf->DeleteProgram(id))
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(vms_ok));

		std::wcout << "Delete Program : " << found_id->second << " sucessful" << std::endl;
		LOG_ERROR("Delte Program succesful");
	}
	else
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(delete_program_failed));
		std::wcout << "Delete Program: "<< found_id->second << " failed" << std::endl;
		LOG_ERROR("Delte Program failed");
	}

	//std::string l_description = std::string("Delete Program: ") + utility::conversions::to_utf8string(found_id->second);
	//l_description += std::string("\nFull name: ") + jv_fullname;
	std::string l_description("");
	m_DBInf->InsertHistory(utility::conversions::to_utf8string(found_username->second),  DELETE_OBJECT, l_description);

	return;
};

void RestProcessing::ShowHistory(http_request)
{
	std::wcout << "Request Show History" << std::endl;

	return;
};

void RestProcessing::GetListDevice(http_request p_request)
{
	std::wcout << "Request Get list Device" << std::endl;
	LOG_INFO("Request Get list Device");

	std::vector<vector<std::string> > l_array_device = m_DBInf->GetAllDevice();

	if(l_array_device.size() > 0)
	{
		json::value l_root;
		json::value l_array;

		for (int i=0; i < l_array_device.size(); i++)
		{
			std::vector<std::string> l_vector_device = l_array_device[i];
			json::value l_vms;

			if(l_vector_device[0].length() > 0)
				l_vms[L"deviceid"]	= json::value::number(stoi(l_vector_device[0]));
			if(l_vector_device[2].length() > 0)
				l_vms[L"modelname"]	= json::value::string(utility::conversions::to_string_t(l_vector_device[2]));
			if(l_vector_device[3].length() > 0)
				l_vms[L"width"]		= json::value::number(stod(l_vector_device[3]));
			if(l_vector_device[4].length() > 0)
				l_vms[L"height"]	= json::value::number(stod(l_vector_device[4]));
			if(l_vector_device[5].length() > 0)
				l_vms[L"nColor"]	= json::value::number(stoi(l_vector_device[5]));
			if(l_vector_device[6].length() > 0)
			{
				json::value l_array_type;
				int i = 0;
				std::string delim = "|";
				auto start = 0U;
				auto end = l_vector_device[6].find(delim);
				while (end != std::string::npos)
				{
					std::string l_vmstype = l_vector_device[6].substr(start, end - start);
					std::cout << l_vmstype << std::endl;
					json::value l_json_vmstype;
					l_json_vmstype[L"typename"] = json::value::string(utility::conversions::to_string_t(l_vmstype));
					l_array_type[i++] = l_json_vmstype;

					start = end + delim.length();
					end = l_vector_device[6].find(delim, start);

				}

				l_vms[L"vmstype"] = l_array_type;
			}

			l_array[i] = l_vms;
		}

		l_root[L"vmsmodels"] = l_array;
		p_request.reply(http::status_codes::OK, l_root);
	}
	else
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(get_list_vms_failed));
		std::wcout << "Get list devie failed" << std::endl;
		LOG_ERROR("Get list device failed");
	}

	return;
}

void RestProcessing::GetListImageResource(http_request p_request)
{
	std::wcout << "Request Get list image" << std::endl;
	LOG_INFO("Request Get list image");

	std::vector<vector<std::string> > l_array_image = m_DBInf->GetAllImage();

	if(l_array_image.size() > 0)
	{
		json::value l_root;
		json::value l_array;

		for (int i=0; i < l_array_image.size(); i++)
		{
			std::vector<std::string> l_vector_image = l_array_image[i];
			json::value l_json_image;

			if(l_vector_image[0].length() > 0)
				l_json_image[L"id"]	= json::value::number(stoi(l_vector_image[0]));
			if(l_vector_image[0].length() > 0)
				l_json_image[L"name"]	= json::value::string(utility::conversions::to_string_t(l_vector_image[1]));
			if(l_vector_image[1].length() > 0)
				l_json_image[L"link"]	= json::value::string(utility::conversions::to_string_t(l_vector_image[2]));
			
			l_array[i] = l_json_image;
		}

		l_root[L"imagelist"] = l_array;
		p_request.reply(http::status_codes::OK, l_root);
	}
	else
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(get_list_vms_failed));
		std::wcout << "Get list image failed" << std::endl;
		LOG_ERROR("Get list image failed");
	}

	return;

}


void RestProcessing::GetListAction(http_request p_request)
{
	std::wcout << "Request Get list action" << std::endl;
	LOG_INFO("Request Get list action");

	std::vector<vector<std::string> > l_array_action = m_DBInf->GetAllAction();

	if(l_array_action.size() > 0)
	{
		json::value l_root;
		json::value l_array;

		for (int i=0; i < l_array_action.size(); i++)
		{
			std::vector<std::string> l_vector_action = l_array_action[i];
			json::value l_json_action;

			if(l_vector_action[0].length() > 0)
				l_json_action[L"id"]	= json::value::number(stoi(l_vector_action[0]));
			if(l_vector_action[1].length() > 0)
				l_json_action[L"description"]	= json::value::string(utility::conversions::to_string_t(l_vector_action[1]));
			
			l_array[i] = l_json_action;
		}
		
		l_root[L"actionlist"] = l_array;
		p_request.reply(http::status_codes::OK, l_root);
	}
	else
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(get_list_vms_failed));
		std::wcout << "Get list action failed" << std::endl;
		LOG_ERROR("Get list action failed");
	}

	return;
};


void RestProcessing::GetListHistory(http_request p_request)
{
	std::wcout << "Request Get list history" << std::endl;
	LOG_INFO("Request Get list history");

	std::string jv_username(""), jv_timestart(""), jv_timeend("");
	int jv_action = INT_MAX, jv_from = INT_MAX, jv_to = INT_MAX;

	std::map<utility::string_t, utility::string_t> query_parameters = uri::split_query(p_request.request_uri().query());
	auto found_username = query_parameters.find(L"username");
	if (found_username == end(query_parameters))
	{
		//std::wcout << "GetListObject: Not fount username parameter" << std::endl;
		//LOG_ERROR("GetListObject: Not fount username parameter");
		//json::value json_response = GenerateJsonCode(not_found_parameter_user);
		//p_request.reply(http::status_codes::OK, json_response);
		//return;
	}
	else
	{
		jv_username = utility::conversions::to_utf8string(found_username->second);
	}

	auto found_action = query_parameters.find(L"action");
	if (found_action != end(query_parameters))
		jv_action = stoi(utility::conversions::to_utf8string(found_action->second));
	
	auto found_from = query_parameters.find(L"from");
	if (found_from != end(query_parameters))
		jv_from = stoi(utility::conversions::to_utf8string(found_from->second));

	auto found_to = query_parameters.find(L"to");
	if (found_to != end(query_parameters))
		jv_to = stoi(utility::conversions::to_utf8string(found_to->second));


	auto found_timestart = query_parameters.find(L"timestart");
	if (found_timestart != end(query_parameters))
	{
		jv_timestart = utility::conversions::to_utf8string(found_timestart->second);
		//jv_timestart.replace("%20"," ");
		boost::algorithm::replace_first(jv_timestart,"%20", " ");
	}

	auto found_timeend = query_parameters.find(L"timeend");
	if (found_timeend != end(query_parameters))
	{
		jv_timeend = utility::conversions::to_utf8string(found_timeend->second);
		boost::algorithm::replace_first(jv_timeend,"%20", " ");
	}

	//Send message
	std::vector<vector<std::string> > l_array_history = m_DBInf->GetWhereHistory(jv_username, jv_action, jv_timestart, jv_timeend);
	int l_rows = l_array_history.size();

	if(jv_from == INT_MAX || jv_from < 0)
		jv_from = 0;
	if(jv_from == INT_MAX)
		jv_to = l_rows;

	jv_to = jv_to < l_rows ? jv_to : l_rows;

	
	if(l_rows > 0)
	{
		json::value l_root;
		json::value l_array;

		int j = 0;
		for (int i=jv_from; i < jv_to; i++)
		{
			std::vector<std::string> l_v_history = l_array_history[i];
			json::value l_json_history;

			if(l_v_history[0].length() > 0)
				l_json_history[L"id"]		= json::value::number(stoi(l_v_history[0]));

			if(l_v_history[1].length() > 0)
				l_json_history[L"username"]	= json::value::string(utility::conversions::to_string_t(l_v_history[1]));

			if(l_v_history[2].length() > 0)
				l_json_history[L"action"]		= json::value::number(stoi(l_v_history[2]));

			if(l_v_history[3].length() > 0)
				l_json_history[L"time"]	= json::value::string(utility::conversions::to_string_t(l_v_history[3]));

			if(l_v_history[7].length() > 0)
				l_json_history[L"actionname"]	= json::value::string(utility::conversions::to_string_t(l_v_history[7]));

			if(l_v_history[4].length() > 0)
				l_json_history[L"detail"]	= json::value::string(utility::conversions::to_string_t(l_v_history[4]));

			l_array[j++] = l_json_history;
		}

		l_root[L"rows"] = l_rows;
		l_root[L"historylist"] = l_array;

		p_request.reply(http::status_codes::OK, l_root);
	}
	else
	{
		p_request.reply(http::status_codes::OK, GenerateJsonCode(get_list_history_failed));
		std::wcout << "Get list history for " << found_username->second  <<" failed" << std::endl;
		LOG_ERROR("Get list history failed");
	}


	return;
};