/*
 * Images.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: binhdu
 */

#include "Images.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>


namespace BLL
{

Images::Images()
{
	// TODO Auto-generated constructor stub
	mDA = NULL ;

}

Images::Images(DAL::DataAccess* pDa):Table(pDa)
{

}


Images::~Images()
{

}

bool Images::Insert(std::string enRes, std::string vnRes, std::string url)
{

	std::string sql = std::string("INSERT INTO Images(en_result, vn_result, url) VALUES(")
			+ enRes
			+ std::string(",")
			+ vnRes
			+ std::string(",")
			+url
			+ std::string(")")  ;

	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	if(mDA->ExcuteUpdate(sql) > 0)
		return true;
	else
		return false;

};


bool Images::Delete(int pID)
{
	std::string idString = std::to_string(pID);
	std::string sql = std::string("DELETE FROM Images WHERE id =")
						+ idString;


	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	if(mDA->ExcuteUpdate(sql) > 0)
		return true;
	else
		return false;
};

bool Images::Update(std::string enRes, std::string vnRes, std::string url)
{
	std::string sql = std::string("UPDATE Images SET en_result=")
						+ std::string("'") + enRes + std::string("'")
						+ std::string(", vn_result= ")
						+ std::string("'") + vnRes + std::string("'")
						+ std::string(", url=")
						+ std::string("'") + url + std::string("'")
						+ std::string(" WHERE en_result =")
						+ std::string("'") + enRes + std::string("'") ;

	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}


	if(mDA->ExcuteUpdate(sql) > 0)
		return true;
	else
		return false;
};


sql::ResultSet* Images::GetAll()
{
	std::string sql = "SELECT* FROM Images" ;

	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	return mDA->GetTable(sql);
};

ImageObject* Images::GetImage(uint32_t pUserID)
{
	std::string sql = std::string("SELECT en_result, vn_result, url "
						"FROM (SELECT * , @i := @i +1 AS level FROM Images, (SELECT @i :=0)temp LIMIT 0 , 10000)TempTable, Users "
						"WHERE TempTable.level = Users.level and Users.id = ")
						+ std::to_string(pUserID);
	if(mDA == NULL)
	{
		mDA = new DAL::DataAccess();
	}

	sql::ResultSet *table = mDA->GetTable(sql);

	if(table == NULL)
	{
		std::cout << __FILE__ << " in function " << __func__ << " on line : " << __LINE__ << " Get sql fail :" << sql << std::endl;
		return NULL ;
	}


	while(table->next())
	{
		ImageObject *data = new ImageObject(
				table->getString(1),
				table->getString(2),
				table->getString(3)
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



ImageObject::ImageObject()
{
	mEnResult = std::string("");
	mVnResult = std::string("");
	mUrl = std::string("");
}


ImageObject::ImageObject(std::string pEnResult, std::string pVnResult, std::string pUrl)
{

	mEnResult = pEnResult ;
	mVnResult = pVnResult ;
	mUrl = pUrl ;

};


ImageObject::~ImageObject()
{
	mEnResult = std::string("");
	mVnResult = std::string("");
	mUrl = std::string("");
};




} /* namespace BLL */
