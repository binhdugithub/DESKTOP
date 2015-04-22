/*
 * Table.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: binhdu
 */

#include "Table.h"

namespace BLL {

Table::Table()
{
	// TODO Auto-generated constructor stub
	mDA = NULL;
}

Table::Table(DAL::DataAccess* pDa)
{
	mDA = pDa ;
}

Table::~Table()
{
	// TODO Auto-generated destructor stub
	if(mDA)
	{
		mDA = NULL;
	}
}


void Table::SetDAL(DAL::DataAccess* pDAL)
{
	this->mDA = pDAL ;
};

} /* namespace BLL */
