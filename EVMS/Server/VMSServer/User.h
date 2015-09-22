/*
 * User.h
 *
 *  Created on: Aug 2, 2014
 *      Author: binhdu
 */

#ifndef User_H_
#define User_H_

#include "Table.h"
#include "DataAccess.h"
#include <iostream>
#include <mutex>


namespace BLL
{

	class User :public Table
	{
	public:
		User();
		virtual ~User();
	public:

		virtual sql::ResultSet* SelectAll();
		bool ExistName(std::string p_name);
		bool Insert(std::string pUsrName,
			std::string pPass,
			std::string pFullName,
			int pSex,
			std::string pBirthday,
			std::string pEmail,
			std::string pPhone,
			std::string pCurrentTime,
			int pRole,
			std::string pAddress);
		bool Delete(std::string);
		virtual sql::ResultSet* Select(std::string);
		bool Update(std::string pUsrName,
			std::string pPass,
			std::string pFullName,
			int pSex,
			std::string pBirthday,
			std::string pEmail,
			std::string pPhone,
			std::string pCurrentTime,
			int pRole,
			std::string pAddress);

		bool IsAdmin(std::string pUseranme);
	};

}


#endif /* User_H_ */
