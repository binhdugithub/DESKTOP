#pragma once
#include "table.h"

namespace BLL
{

	class History :
		public Table
	{
	public:
		History(void);
		virtual ~History(void);
		virtual sql::ResultSet* SelectAll();
		sql::ResultSet* SelectWhere(std::string p_username,
									int p_action,
									std::string p_starttime,
									std::string p_endtime);
		bool Insert(std::string p_username,
					int p_action,
					std::string p_detail);
		bool Delete(int p_id);
		bool Update(int p_id, 
					std::string p_username,
					int p_action,
					std::string p_time,
					std::string p_detail);
	};
}

