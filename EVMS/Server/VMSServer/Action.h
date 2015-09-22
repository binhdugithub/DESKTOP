#pragma once
#include "table.h"
namespace BLL
{

class Action :
	public Table
{
public:
	Action(void);
	virtual ~Action(void);
	virtual sql::ResultSet* SelectAll();
	bool Insert(int, std::string);
	bool Delete(int);
	bool Update(int, std::string);
};

}
