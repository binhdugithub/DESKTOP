/*
 * BcDataManager.h
 *
 *  Created on: Jul 18, 2014
 *      Author: binhdu
 */

#ifndef BCDATAMANAGER_H_
#define BCDATAMANAGER_H_

#include "../database/BLL/Images.h"
#include "../database/BLL/Users.h"
#include "../database/DAL/DataAccess.h"



class BcDataManager
{

public:
	DAL::DataAccess *mDA ;

public:
	BLL::Images *TBImages ;
	BLL::Users *TBUsers ;

public:
	BcDataManager();
	BcDataManager(std::string , std::string , std::string , std::string );
	virtual ~BcDataManager();

	void SetDAL(DAL::DataAccess*);
};

#endif /* BCDATAMANAGER_H_ */
