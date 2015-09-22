#pragma once

#include <ostream>
#include <string>

class MsgLogin
{
public:
	std::string m_name;
	//std::string m_password;
	//std::string m_action;
	std::string m_result;
public:
	MsgLogin() 
		:m_name(""),
		//m_password(""),
		//m_action(""),
		m_result("")
	{

	};

	MsgLogin(std::string name, std::string result)
	{
		m_name = name;
		m_result = result;
	}

	virtual ~MsgLogin(){};

	void SetName(std::string p_value)
	{
		m_name = p_value;
	};

	void SetPass(std::string p_value)
	{
		//m_password = p_value;
	};

	void SetAction(std::string p_value)
	{
		//m_action = p_value;
	};

	void SetResult(std::string p_value)
	{
		m_result = p_value;
	};
};

