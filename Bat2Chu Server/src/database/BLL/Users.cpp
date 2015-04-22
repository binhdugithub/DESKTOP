/*
 * Users.cpp
 *
 *  Created on: Aug 2, 2014
 *      Author: binhdu
 */

#include "Users.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>

namespace BLL {

Users::Users() {
	// TODO Auto-generated constructor stub

}


Users::Users(DAL::DataAccess* pDa) : Table(pDa)
{

}

Users::~Users()
{

}



bool Users::Insert(uint32_t pID, std::string pUsrName, std::string pFB, uint32_t pLevel, uint32_t pRuby)
{
	/*std::string sql = std::string("INSERT INTO Users (level,ruby) VALUES(") ;


	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	mDA->ExcuteNonQuery(sql) ;*/

	return false;
}

int Users::CreateNewUser()
{
	std::string sqlInsert = std::string("INSERT INTO Users (level, ruby) VALUES (") +
			std::to_string(0) +
			std::string(",") +
			std::to_string(0) +
			std::string(")");

	std::string sqlQuery = std::string("SELECT LAST_INSERT_ID()");

	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	sql::ResultSet *table = mDA->ExcuteInsertAndQuery(sqlInsert, sqlQuery);

	if(table == NULL)
	{
		std::cout << __FILE__ << " on line: " << __LINE__ << " [" << __func__<< "]" << "Get table fail" << std::endl;
		return -1 ;
	}

	while(table->next())
	{
		int lIDUser = table->getInt(1);
		if(lIDUser > 0)
		{
			delete table;
			table = NULL ;

			return lIDUser;
		}
		else
			continue ;
	};

	delete table;
	table = NULL ;

	return -1;
}

bool Users::Delete(uint32_t pID)
{
	std::string sql = std::string("DELETE FROM Users WHERE id =") + std::to_string(pID) ;

	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	if(mDA->ExcuteUpdate(sql) > 0)
		return true;
	else
		return false;

}


bool Users::UpdateFacebook(uint32_t pID,std::string pFB)
{

	std::string sql = std::string("UPDATE TABLE Users SET facebook= ")
			+ std::string("'") + pFB + std::string("'")
			+ std::string(" WHERE id =") + std::to_string(pID) ;

	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	if(mDA->ExcuteUpdate(sql) > 0)
		return true;
	else
		return false;
}

bool Users::UpdateUserName(uint32_t pID,std::string pUsrName)
{
	std::string sql = std::string("UPDATE TABLE Users SET user_name= ")
		+ std::string("'") + pUsrName + std::string("'")
		+ std::string(" WHERE id =") + std::to_string(pID) ;

	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	if(mDA->ExcuteUpdate(sql) > 0)
		return true;
	else
		return false;
}

bool Users::UpdateLevelAndRuby(uint32_t pID, uint32_t pLevel, uint32_t pRuby)
{
	std::string sql = std::string("UPDATE TABLE Users SET level= ")
					+ std::to_string(pLevel)
					+std::string(" , ruby =") + std::to_string(pRuby)
					+std::string(" WHERE id= ") +	std::to_string(pID);

	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	if(mDA->ExcuteUpdate(sql) > 0)
		return true;
	else
		return false;
}

bool Users::UpdateLevelAndRuby(uint32_t pID)
{
	std::string sql = std::string("UPDATE Users SET level = level +1, ruby = ruby + 20 WHERE id = ")
					 +std::to_string(pID);

	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	if(mDA->ExcuteUpdate(sql) > 0)
		return true;
	else
		return false;
}

sql::ResultSet* Users::GetAll()
{
	std::string sql = "SELECT* FROM Users" ;

	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	return mDA->GetTable(sql);
}

UserObject* Users::GetUserAtID(uint32_t pID)
{

	std::string idUser = std::to_string(pID);
	std::string sql = std::string("SELECT* FROM Users WHERE id =")
					 +idUser;


	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	sql::ResultSet *table = mDA->GetTable(sql);
	if(table == NULL)
	{
		std::cout << __FILE__ << " in function " << __func__ << " on line : " << __LINE__ << " Get table fail :" << std::endl;
		return NULL ;
	}

	while(table->next())
	{
		UserObject *data = new UserObject(
				table->getInt(1),
				table->getString(2),
				table->getInt(3),
				table->getInt(4)
				) ;


		if(data)
		{
			delete table;
			table = NULL ;
			return data;
		}
		else
		{
			continue;
		}

	};

	delete table;
	table = NULL ;

	return NULL;

}

uint32_t Users::GetMaxID()
{

	std::string sql = "SELECT MAX(id)";

	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	sql::ResultSet *table = mDA->GetTable(sql);

	if(table == NULL)
	{
		std::cout << __FILE__ << " in function " << __func__ << " on line : " << __LINE__ << " Get sql fail :" << sql << std::endl;
		return -1 ;
	}

	uint32_t idMax = -1 ;

	while(table->next())
	{
		idMax = table->getInt(1) ;

		if(idMax > 0)
		{
			break;
		}
		else
		{
			continue;
		}

	};

	delete table;
	table = NULL ;

	return idMax;
}





UserObject::UserObject()
{
	mID = 0 ;
	mFacebook = std::string("") ;
	mLevel = 0 ;
	mRuby = 0 ;
}

UserObject::UserObject(uint32_t pID,std::string pFB, uint32_t pLevel, uint32_t pRuby)
{
	mID = pID ;
	mFacebook = pFB ;
	mLevel = pLevel ;
	mRuby = pRuby ;

}
UserObject::~UserObject()
{
	mID = 0 ;
	mFacebook = std::string("") ;
	mLevel = 0 ;
	mRuby = 0 ;
}

} /* namespace BLL */

