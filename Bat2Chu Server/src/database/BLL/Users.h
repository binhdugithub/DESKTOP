/*
 * Users.h
 *
 *  Created on: Aug 2, 2014
 *      Author: binhdu
 */

#ifndef USERS_H_
#define USERS_H_

#include "Table.h"
#include "../DAL/DataAccess.h"
#include <iostream>
#include <mutex>

namespace BLL
{

class UserObject ;
class Users :public Table
{
public:
	Users();
	Users(DAL::DataAccess*) ;
	virtual ~Users();
public:
	bool Insert(uint32_t pID, std::string pUsrName, std::string pFB, uint32_t pLevel, uint32_t pRuby) ;
	int CreateNewUser() ;
	bool Delete(uint32_t);
	bool UpdateFacebook(uint32_t,std::string) ;
	bool UpdateUserName(uint32_t,std::string) ;
	bool UpdateLevelAndRuby(uint32_t pID);
	bool UpdateLevelAndRuby(uint32_t pID, uint32_t pLevel, uint32_t pRuby) ;
	virtual sql::ResultSet* GetAll();
	UserObject* GetUserAtID(uint32_t);
	uint32_t GetMaxID() ;

};

class UserObject
{
public:
	uint32_t mID ;
	std::string mFacebook;
	uint32_t mLevel;
	uint32_t mRuby;
	//int mNextID ;

public:
	UserObject();
	UserObject(uint32_t,std::string, uint32_t, uint32_t);
	~UserObject();

};

} /* namespace BLL */



#endif /* USERS_H_ */
