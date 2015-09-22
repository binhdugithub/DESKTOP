#pragma once
#include "Table.h"
#include "User.h"

namespace BLL
{

class Object : public Table
{
public:
	Object(void);
	virtual ~Object(void);
	public:
		virtual sql::ResultSet* SelectAll();
		sql::ResultSet* SelectAll(std::string pUsername);
		virtual sql::ResultSet* SelectWhere(int);
		bool ExistName(std::string p_name);
		bool ExistIP(std::string p_ip);
		int Insert(
			std::string p_name,
			std::string p_ip,
			int p_port,
			std::string p_description,
			std::string p_location,
			int p_deviceid,
			std::string  p_program,
			std::string p_screenshot,
			int p_status
			);

		bool Delete(int);
		int Update(
			int p_id,
			std::string p_name,
			std::string p_ip,
			int p_port,
			std::string p_description,
			std::string p_location,
			int p_deviceid,
			std::string  p_program,
			std::string p_screenshot,
			int p_status);
};

}