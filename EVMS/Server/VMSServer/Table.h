/*
 * Table.h
 *
 *  Created on: Jul 18, 2014
 *      Author: binhdu
 */

#ifndef TABLE_H_
#define TABLE_H_

#include "DataAccess.h"
#include <mutex>
#include "LogFile.h"

namespace BLL
{

class Table
{
public:
	DAL::DataAccess *mDA ;
public:
	Table();
	virtual ~Table();
	virtual sql::ResultSet* SelectAll() = 0;
};

} /* namespace BLL */

#endif /* TABLE_H_ */
