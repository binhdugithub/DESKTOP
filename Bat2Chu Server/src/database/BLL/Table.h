/*
 * Table.h
 *
 *  Created on: Jul 18, 2014
 *      Author: binhdu
 */

#ifndef TABLE_H_
#define TABLE_H_

#include "../DAL/DataAccess.h"
#include <mutex>

namespace BLL
{

class Table
{
public:
	DAL::DataAccess *mDA ;
	//std::recursive_mutex mDAMutex ;

public:
	Table();
	Table(DAL::DataAccess*);
	virtual ~Table();
	virtual void SetDAL(DAL::DataAccess*) ;
	virtual sql::ResultSet* GetAll() = 0;
};

} /* namespace BLL */

#endif /* TABLE_H_ */
