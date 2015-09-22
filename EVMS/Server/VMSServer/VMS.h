#pragma once
#include "Table.h"

namespace BLL
{

	class VMS :
		public Table
	{
	public:
		VMS(void);
		virtual ~VMS(void);

	public:
		virtual sql::ResultSet* SelectAll();
		sql::ResultSet* SelectAll(std::string pUsername);
		virtual sql::ResultSet* SelectWhere(std::string);
		int Insert(
			std::string name,
			float width,
			float height,
			std::string location,
			std::string content
			);
		bool Delete(int id);
		bool Update(int id,
			std::string name,
			float width,
			float height,
			std::string location,
			std::string content);
};

}//end namespace BLL
