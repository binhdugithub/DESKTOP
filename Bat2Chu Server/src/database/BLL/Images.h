/*
 * Images.h
 *
 *  Created on: Jul 18, 2014
 *      Author: binhdu
 */

#ifndef IMAGES_H_
#define IMAGES_H_


#include "../DAL/DataAccess.h"
#include "Table.h"
#include <iostream>
#include <mutex>

namespace BLL
{

class ImageObject ;

class Images : public Table
{

public:
	Images();
	Images(DAL::DataAccess*);
	virtual ~Images();

public:
	bool Insert(std::string, std::string, std::string) ;
	bool Delete(int);
	bool Update(std::string, std::string, std::string) ;
	virtual sql::ResultSet* GetAll();
	ImageObject* GetImage(uint32_t pUserID = 1000);
};

class ImageObject
{
public:
	std::string mEnResult;
	std::string mVnResult;
	std::string mUrl;

public:
	ImageObject();
	ImageObject(std::string, std::string, std::string);
	~ImageObject();

};

} /* namespace BLL */

#endif /* IMAGES_H_ */
