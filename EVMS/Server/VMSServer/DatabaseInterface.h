#pragma once
#include <ostream>
#include <string>
#include "LogFile.h"
#include "User.h"
#include "Role.h"
#include "Device.h"
#include "UserObject.h"
#include "Program.h"
#include "Object.h"
#include "ImageSource.h"
#include "Action.h"
#include "History.h"

class DatabaseInterface
{
public:
	DatabaseInterface();
	virtual ~DatabaseInterface();

public:
	//1. User table
	int IsCorrectUser(std::string, std::string);
	bool DeleteUser(std::string);
	bool ExistUserName(std::string p_name);
	bool InsertUser(std::string pUsrName,
		std::string pPass,
		std::string pFullName,
		int pSex,
		std::string pBirthday,
		std::string pEmail,
		std::string pPhone,
		std::string pCurrentTime,
		int pRole,
		std::string pAddress);
	bool UpdateUser(std::string pUsrName,
		std::string pPass,
		std::string pFullName,
		int pSex,
		std::string pBirthday,
		std::string pEmail,
		std::string pPhone,
		std::string pCurrentTime,
		int pRole,
		std::string pAddress);
	std::vector<std::vector<std::string> > GetAllUser();

	//2. Device
	int InsertDevice(
		std::string,
		std::string,
		float,
		float,
		int,
		std::string
		);

	bool DeleteDevice(int pId);
	bool UpdateDevice(
		int,
		std::string,
		std::string,
		float,
		float,
		int,
		std::string);
	std::vector<std::vector<std::string> >	GetAllDevice();
	std::vector<std::vector<std::string> >	GetAllProgram();
	std::vector<std::string> GetProgram(int);

	//3. Object
	bool ExistObjectName(std::string p_name);
	bool ExistObjectIP(std::string p_ip);
	int InsertObject(
		std::string p_name,
		std::string p_ip,
		int p_port,
		std::string p_description,
		std::string p_location,
		int p_deviceid,
		std::string  p_program,
		std::string p_screenshot,
		int p_status
		);

	bool DeleteObject(int p_id);
	int UpdateObject(
		int p_id,
		std::string p_name,
		std::string p_ip,
		int p_port,
		std::string p_description,
		std::string p_location,
		int p_deviceid,
		std::string  p_program,
		std::string p_screenshot,
		int p_status);
	std::vector<std::vector<std::string> >	GetAllObject(std::string);
	std::vector<std::vector<std::string> >	GetMonitoring(std::string);
	std::vector<std::string>	GetObjectDetail(int);

	//4. assign vms
	bool AssignVMS(std::string, std::vector<int>);

	//5. Role table
	std::vector<std::vector<std::string> > GetAllRole();

	//6. program
	bool InsertProgram(std::string, int type, std::string, float, float);
	bool UpdatetProgram(int, std::string, int, std::string, float, float);
	bool DeleteProgram(int pId);

	//7.image resource
	//6. program
	bool InsertImage(std::string);
	bool UpdatetImage(int, std::string);
	bool DeleteImage(int);
	std::vector<std::vector<std::string> >	GetAllImage();


	//7.action
	std::vector<std::vector<std::string> > GetAllAction();

	//8.HISTORY
	bool InsertHistory(std::string p_username,
				int p_action,
				std::string p_detail);
	std::vector<std::vector<std::string> > GetAllHistory();
	std::vector<std::vector<std::string> > GetWhereHistory(
				std::string p_username,
				int p_action,
				std::string p_starttime,
				std::string p_endtime);
};

