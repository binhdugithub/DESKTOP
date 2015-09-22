#include "stdafx.h"
#include "UserObject.h"

namespace BLL
{

	UserObject::UserObject(void)
	{
	}


	UserObject::~UserObject(void)
	{
	}

	sql::ResultSet* UserObject::SelectAll()
	{
		std::string sql = std::string("SELECT* FROM vms_user_object");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		std::string l_pass("");
		if (table == NULL)
		{
			std::wcout << "Get all data from vms_user_object fail" << std::endl;
			LOG_ERROR("Get all data from vms_user_object fail");
		}
		else
		{
			return table;
		}

		return NULL;
	}


	bool UserObject::Insert(std::string p_name, int p_id)
	{
		std::string sql = std::string("INSERT INTO vms_user_object VALUES(");
		sql += std::string("'") + p_name + std::string("'");
		sql += std::string(",");
		sql += std::string("'") + std::to_string(p_id) + std::string("'");
		sql += std::string(")");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		if (mDA->QueryUpdate(sql) > 0)
			return true;
		else
			return false;

		return false;
	};

	bool UserObject::Delete(std::string p_username)
	{
		std::string sql = std::string("DELETE FROM vms_user_object WHERE username =") +
						 std::string("'") + p_username + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		if (mDA->QueryUpdate(sql) >= 0)
			return true;
		else
			return false;

		return false;
	};

	/*bool UserDevice::Update(int p_id, std::string p_name)
	{
		std::string sql = std::string("UPDATE vms_user_object SET name =") +
			std::string("'") + p_name + std::string("'") +
			std::string("where roleid = ") +
			std::string("'") + std::to_string(p_id) + std::string("'");

		if (mDA->QueryUpdate(sql) <= 0)
		{
			std::wcout << L"Update role failed!" << std::endl;
			return false;
		}

		return true;
	};*/
}
