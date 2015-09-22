#include "stdafx.h"
#include "Role.h"

namespace BLL
{
	Role::Role(void)
	{
	}


	Role::~Role(void)
	{
	}

	sql::ResultSet* Role::SelectAll()
	{
		std::string sql = std::string("SELECT* FROM vms_role");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		std::string l_pass("");
		if (table == NULL)
		{
			std::wcout << "Get all data from vms_role fail" << std::endl;
			LOG_ERROR("Get all data from vms_role fail");
		}
		else
		{
			return table;
		}

		return NULL;
	}


	bool Role::Insert(int p_id, std::string p_name)
	{
		std::string sql = std::string("INSERT INTO vms_role VALUES(");
		sql += std::string("'") + std::to_string(p_id) + std::string("'");
		sql += std::string("'") + p_name + std::string("'");
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

	bool Role::Delete(int p_id)
	{
		std::string sql = std::string("DELETE FROM vms_role WHERE roleid =") +
					sql += std::string("'") + std::to_string(p_id) + std::string("'");

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

	bool Role::Update(int p_id, std::string p_name)
	{
		std::string sql = std::string("UPDATE vms_role SET name =") +
			std::string("'") + p_name + std::string("'") +
			std::string("where roleid = ") +
			std::string("'") + std::to_string(p_id) + std::string("'");

		if (mDA->QueryUpdate(sql) < 0)
		{
			std::wcout << L"Update role failed!" << std::endl;
			return false;
		}

		return true;
	};
}//end namespace BLL
