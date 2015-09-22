#include "stdafx.h"
#include "Program.h"

namespace BLL
{

	Program::Program(void)
	{
	}


	Program::~Program(void)
	{
	}

	sql::ResultSet* Program::SelectAll()
	{
		std::string sql = std::string("SELECT* FROM vms_program");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		if (table == NULL)
		{
			std::wcout << "program get table fail" << std::endl;
			LOG_ERROR("program get table fail");
		}
		else
		{
			return table;
		}

		return NULL;
	};


	sql::ResultSet* Program::Select(int p_id)
	{

		std::string sql = std::string("SELECT* FROM vms_program where id =");
		sql += std::string("'");
		sql += std::to_string(p_id);
		sql += std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		if (table == NULL)
		{
			std::wcout << "program get table fail" << std::endl;
			LOG_ERROR("program get table fail");
		}
		else
		{
			return table;
		}

		return NULL;
	}


	bool Program::Insert(std::string p_name, int p_type, std::string p_content, float p_w, float p_h)
	{
		std::string sql =
			std::string("INSERT INTO vms_program(name, type, content,width, height) VALUES(") +
			std::string("'") + p_name + std::string("',") +
			std::string("'") + std::to_string(p_type) + std::string("',") +
			std::string("'") + p_content + std::string("',") +
			std::string("'") + std::to_string(p_w) + std::string("',") +
			std::string("'") + std::to_string(p_h) + std::string("')");
	
		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;

		if (mDA->QueryUpdate(sql) > 0)
			return true;
		else
			return false;
	};


	bool Program::Delete(int p_id)
	{
		std::string sql = std::string("DELETE FROM vms_program WHERE id =") +
			std::string("'") + std::to_string(p_id) + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;

		if (mDA->QueryUpdate(sql) > 0)
			return true;
		else
			return false;
	};


	bool Program::Update(int p_id, std::string p_name, int p_type, std::string p_content, float p_w, float p_h)
	{
		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//1. name
		if(p_name.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_program SET name =") +
				std::string("'") + p_name + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update name from vms_program failed!" << std::endl;
				LOG_ERROR("Update name from vms_program failed!");
				return false;
			}
		}

		//2. type
		if(p_type != INT_MAX)
		{
			std::string sql = std::string("UPDATE vms_program SET type =") +
				std::string("'") + std::to_string(p_type) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update type from vms_program failed!" << std::endl;
				LOG_ERROR("Update type from vms_program failed!");
				return false;
			}
		}

		//3. content
		if(p_content.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_program SET content =") +
				std::string("'") + p_content + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update content failed!" << std::endl;
				return false;
			}
		}

		//4. width
		if(p_w != FLT_MAX)
		{
			std::string sql = std::string("UPDATE vms_program SET width =") +
				std::string("'") + std::to_string(p_w) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update width from vms_program failed!" << std::endl;
				LOG_ERROR("Update width from vms_program failed!");
				return false;
			}
		}

		//4. height
		if(p_h != FLT_MAX)
		{
			std::string sql = std::string("UPDATE vms_program SET height =") +
				std::string("'") + std::to_string(p_h) + std::string("'") +
				std::string("where id = ") +
				std::string("'") + std::to_string(p_id) + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update height from vms_program failed!" << std::endl;
				LOG_ERROR("Update height from vms_program failed!");
				return false;
			}
		}

		return true;
	};
}