#pragma once
#include "Table.h"

namespace BLL
{

	class Device :
		public Table
	{
	public:
		Device(void);
		virtual ~Device(void);

	public:
		virtual sql::ResultSet* SelectAll();
		sql::ResultSet* SelectAll(std::string pUsername);
		virtual sql::ResultSet* SelectWhere(std::string);
		int Insert(
			std::string,
			std::string,
			float,
			float,
			int,
			std::string
			);

		bool Delete(int);
		bool Update(
			int,
			std::string,
			std::string,
			float,
			float,
			int,
			std::string);
};

}//end namespace BLL
