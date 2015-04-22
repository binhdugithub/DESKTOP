/*
 * BcThreadObject.h
 *
 *  Created on: Jul 17, 2014
 *      Author: binhdu
 */

#ifndef BcThreadObject_H_
#define BcThreadObject_H_

#include "../threadpool/ThreadObject.h"
#include "BcDataManager.h"

#define HOST "127.0.0.1"
#define USER "root"
#define PASS "root"
#define DATABASE "Bat2Chu"


class BcThreadObject : public ThreadObject
{

private:
	BcDataManager *mDataManager ;

public:
	BcThreadObject();
	BcThreadObject(std::string , std::string , std::string , std::string );

protected:
	virtual ~BcThreadObject();

	virtual bool AddJob(ThreadJob*) ;


};

#endif /* BcThreadObject_H_ */
