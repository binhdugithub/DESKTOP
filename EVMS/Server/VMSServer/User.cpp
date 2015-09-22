/*
 * User.cpp
 *
 *  Created on: Aug 2, 2014
 *      Author: binhdu
 */

#include "stdafx.h"
#include "User.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "LogFile.h"


namespace BLL {

	User::User() 
	{
		// TODO Auto-generated constructor stub
		//mDA = new DAL::DataAccess();

	}

	User::~User()
	{

	}

	sql::ResultSet* User::SelectAll()
	{
		std::string sql = std::string("SELECT* FROM vms_user");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		if (table == NULL)
		{
			std::wcout << "User get table fail" << std::endl;
			LOG_ERROR("User get table fail");
		}
		else
		{
			return table;
		}

		return NULL;
	}

	bool User::ExistName(std::string p_name)
	{
		std::string sql = std::string("SELECT* FROM vms_user WHERE username =");
		sql += std::string("'") + p_name + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		sql::ResultSet  *table = mDA->QueryData(sql);
		bool l_true_false = false;;

		if (table == NULL)
		{
			std::wcout << "Get table vms_user failed" << std::endl;
			LOG_ERROR("Get table vms_user failed");

			l_true_false = false;
		}
		else
		{
			if(table->rowsCount() >0)
			{
				l_true_false = true;
			}
			else
			{
				l_true_false = false;
			}
		}

		delete table;

		return l_true_false;

	};


	bool User::Insert(std::string pUsrName,
		std::string pPass,
		std::string pFullName,
		int pSex,
		std::string pBirthday,
		std::string pEmail,
		std::string pPhone,
		std::string pCurrentTime,
		int pRole,
		std::string pAddress)
	{
		std::string sql =
			std::string("INSERT INTO vms_user VALUES(") +
			std::string("'") + pUsrName + std::string("',") +
			std::string("'") + pPass + std::string("',") +
			std::string("'") + pFullName + std::string("',") +
			std::string("'") + std::to_string(pSex) + std::string("',") +
			std::string("'") + pBirthday + std::string("',") +
			std::string("'") + pEmail + std::string("',") +
			std::string("'") + pPhone + std::string("',") +
			std::string("'") + pCurrentTime + std::string("',") +
			std::string("'") + std::to_string(pRole) + std::string("',") +
			std::string("'") + pAddress + std::string("')");
	
		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;

		if (mDA->QueryUpdate(sql) > 0)
			return true;
		else
			return false;
	}


	bool User::Delete(std::string pUserName)
	{
		std::string sql = std::string("DELETE FROM vms_user WHERE username =") +
			std::string("'") + pUserName + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		if (mDA->QueryUpdate(sql) > 0)
			return true;
		else
			return false;
	}


	sql::ResultSet* User::Select(std::string p_username)
	{
		std::string sql = std::string("SELECT* FROM vms_user where username = '") +
			p_username + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);
		if (table == NULL)
		{
			std::wcout << "User get table fail" << std::endl;
			LOG_ERROR("User get table fail");
		}
		else
		{
			return table;
		}

		return NULL;
	}


	bool User::Update(std::string pUsrName,
		std::string pPass,
		std::string pFullName,
		int pSex,
		std::string pBirthday,
		std::string pEmail,
		std::string pPhone,
		std::string pCurrentTime,
		int pRole,
		std::string pAddress)
	{
		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//1. password
		if(pPass.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_user SET password =") +
				std::string("'") + pPass + std::string("'") +
				std::string("where username = ") +
				std::string("'") + pUsrName + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update password failed!" << std::endl;
				return false;
			}
		}

		//2. fullname
		if(pFullName.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_user SET fullname =") +
				std::string("'") + pFullName + std::string("'") +
				std::string("where username = ") +
				std::string("'") + pUsrName + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update fullname failed!" << std::endl;
				return false;
			}
		}

		//2. pAddress
		if(pAddress.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_user SET address =") +
				std::string("'") + pAddress + std::string("'") +
				std::string("where username = ") +
				std::string("'") + pUsrName + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update address failed!" << std::endl;
				return false;
			}
		}

		//3. sex
		if(pSex != INT_MAX)
		{
			std::string sql = std::string("UPDATE vms_user SET sex =") +
				std::string("'") + std::to_string(pSex) + std::string("'") +
				std::string("where username = ") +
				std::string("'") + pUsrName + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update sex failed!" << std::endl;
				return false;
			}
		}

		//4. birthday
		if(pBirthday.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_user SET birthday =") +
				std::string("'") + pBirthday + std::string("'") +
				std::string("where username = ") +
				std::string("'") + pUsrName + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update birthday failed!" << std::endl;
				return false;
			}
		}
		
		//5. email
		if(pEmail.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_user SET email =") +
				std::string("'") + pEmail + std::string("'") +
				std::string("where username = ") +
				std::string("'") + pUsrName + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update email failed!" << std::endl;
				return false;
			}
		}

		//6. phone
		if(pPhone.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_user SET phone =") +
				std::string("'") + pPhone + std::string("'") +
				std::string("where username = ") +
				std::string("'") + pUsrName + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update birthday failed!" << std::endl;
				return false;
			}
		}
		//7. currenttime
		if(pCurrentTime.length() > 0)
		{
			std::string sql = std::string("UPDATE vms_user SET currenttime =") +
				std::string("'") + pCurrentTime + std::string("'") +
				std::string("where username = ") +
				std::string("'") + pUsrName + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update birthday failed!" << std::endl;
				return false;
			}
		}

		//3. sex
		if(pRole != INT_MAX)
		{
			std::string sql = std::string("UPDATE vms_user SET roleid =") +
				std::string("'") + std::to_string(pRole) + std::string("'") +
				std::string("where username = ") +
				std::string("'") + pUsrName + std::string("'");

			if (mDA->QueryUpdate(sql) < 0)
			{
				std::wcout << L"Update roleid failed!" << std::endl;
				return false;
			}
		}

		return true;
	};


	bool User::IsAdmin(std::string pUseranme)
	{
		std::string sql = std::string("SELECT(roleid) FROM vms_user WHERE username = ");
					sql += std::string("'") + pUseranme + std::string("'");

		if (mDA == NULL)
		{
			mDA = new DAL::DataAccess();
		}

		//std::cout << "Excute: " << sql << std::endl;
		sql::ResultSet  *table = mDA->QueryData(sql);

		if (table == NULL)
		{
			std::wcout << "User get table fail" << std::endl;
			LOG_ERROR("User get table fail");
		}
		else
		{
			while (table->next())
			{
				int id = table->getInt(1);
				if(id == 0)
					return true;
				else 
					return false;
			}

			delete table;
			table = NULL;
		}

		return false;
	}

} /* namespace BLL */

