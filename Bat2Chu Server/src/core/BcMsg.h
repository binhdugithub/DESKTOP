/*
 * BcMsg.h
 *
 *  Created on: Jul 11, 2014
 *      Author: binhdu
 */

#ifndef BcMsg_H_
#define BcMsg_H_

#include <iostream>
#include <vector>

#include "M_if.h"


class BcRequestConnect;
class BcRequestNextLevel;
class BcRequestUpdate ;
class BcRequestSuggestion;
class BcRequestChargeRuby ;
class BcRequestShareFacebook;

class BcResponseNextLevel ;

class BcMsg
{

public:
	enum
	{
		Class_Unknow,
		Class_BcRequestConnect,
		Class_BcRequestNextLevel,
		Class_BcRequestUpdate ,
		Class_BcRequestSuggestion,
		Class_BcRequestChargeRuby ,
		Class_BcRequestShareFacebook,


		Class_BcResponseNextLevel

	};

public:
	int mTag ;
public:
	void *mData;

public:
	BcMsg();
	BcMsg(int, int, void*, int) ;
	BcMsg(std::string);
	virtual ~BcMsg();
	int GetTag();
	void* GetBuffer();
	void CreateRcvMsg(std::string);
	void CreateSendMsg(int, int, void*,int);
	//std::vector<std::string> SplitStringMsg(std::string, char );
};


class BcRequestNextLevel
{
public:
	int mLevel ;
	int mScore ;

public:
	BcRequestNextLevel();
	BcRequestNextLevel(int,int);
	virtual ~BcRequestNextLevel();

};



class BcResponseNextLevel
{

public:
	int mLeng ;
	std::string mHeader ;
	void *mImage ;

public:
	BcResponseNextLevel();
	BcResponseNextLevel(int,int, void*, int);
	virtual ~BcResponseNextLevel();

};
#endif /* BcMsg_H_ */
