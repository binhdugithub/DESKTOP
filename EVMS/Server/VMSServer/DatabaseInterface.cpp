#include "stdafx.h"
#include "DatabaseInterface.h"


DatabaseInterface::DatabaseInterface()
{
}


DatabaseInterface::~DatabaseInterface()
{
}


//return -1 when is wrong password
int DatabaseInterface::IsCorrectUser(std::string p_user, std::string p_password)
{
	BLL::User *MyUser = new BLL::User();
	sql::ResultSet *table = MyUser->Select(p_user);
	if(!table)
	{
		if(MyUser)
		{
			delete MyUser;
			MyUser = NULL;
		}

		return -1;
	}

	std::string l_pass("");
	int l_role = -1;
	while (table->next())
	{
		try
		{
			l_pass += std::string(table->getString("password").c_str());
			l_role = table->getInt("roleid");

			break;
		}
		catch (sql::SQLException &e)
		{
			std::wcout << "Get data from table fail" << std::ends;
			LOG_ERROR("Get data from table fail");
			std::cout << e.what() << std::endl;
			break;
		}
	};

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyUser)
	{
		delete MyUser;
		MyUser = NULL;
	}

	if (l_pass == p_password)
		return l_role;
	else
		return -1;

	return -1;
};


bool DatabaseInterface::DeleteUser(std::string p_username)
{
	BLL::User *MyUser = new BLL::User();
	bool successful = MyUser->Delete(p_username);
	if(MyUser)
	{
		delete MyUser;
		MyUser = NULL;
	}

	if (successful)
		return true;
	else
		return false;

	return false;
};

bool DatabaseInterface::ExistUserName(std::string p_name)
{
	BLL::User *MyUser = new BLL::User();
	bool l_true_false = MyUser->ExistName(p_name);

	if(MyUser)
	{
		delete MyUser;
		MyUser = NULL;
	}

	return l_true_false;

};
bool DatabaseInterface::InsertUser(
	std::string pUsrName,
	std::string pPass,
	std::string pFullName,
	int pSex,
	std::string pBirthday,
	std::string pEmail,
	std::string pPhone,
	std::string pCurrentTime,
	int pRole,
	std::string pAddress)
{
	if(pUsrName == std::string("") ||
		pPass == std::string(""))
	{
		std::wcout << L"Insert user with data is empty!" << std::endl;
		LOG_ERROR("Insert user with data is empty!");

		return false;
	}

	BLL::User *MyUser = new BLL::User();

	bool successful = MyUser->Insert(pUsrName, pPass, pFullName, pSex,pBirthday,pEmail,pPhone, pCurrentTime, pRole, pAddress);

	if(MyUser)
	{
		delete MyUser;
		MyUser = NULL;
	}

	if(successful)
		return true;
	else 
		return false;

	return false;
};


bool DatabaseInterface::UpdateUser(
	std::string pUsrName,
	std::string pPass,
	std::string pFullName,
	int pSex,
	std::string pBirthday,
	std::string pEmail,
	std::string pPhone,
	std::string pCurrentTime,
	int pRole,
	std::string pAddress)
{
	if(pUsrName == std::string(""))
		return false;

	BLL::User *MyUser = new BLL::User();

	bool succesful = MyUser->Update(pUsrName, pPass, pFullName, pSex, pBirthday, pEmail, pPhone, pCurrentTime, pRole, pAddress);

	if(MyUser)
	{
		delete MyUser;
		MyUser = NULL;
	}

	if(succesful)
		return true;
	else
		return false;
	
	return false;
};

std::vector<std::vector<std::string> > DatabaseInterface::GetAllUser()
{
	BLL::User *MyUser = new BLL::User();

	sql::ResultSet* table = MyUser->SelectAll();
	std::vector<std::vector<std::string> > l_result;
	if(!table)
	{
		if(MyUser)
		{
			delete MyUser;
			MyUser = NULL;
		}

		return l_result;
	}

	if (!table)
	{
		std::wcout << L"Get all user failed" << std::endl;
		LOG_ERROR("Get all user failed");

		if(MyUser)
		{
			delete MyUser;
			MyUser = NULL;
		}

		return l_result;
	}

	
	while (table->next())
	{
		std::vector<std::string> l_l_result;

		l_l_result.push_back(std::string(table->getString(1).c_str()));
		l_l_result.push_back(std::string(table->getString(3).c_str()));
		l_l_result.push_back(std::string(table->getString(4).c_str()));
		l_l_result.push_back(std::string(table->getString(5).c_str()));
		l_l_result.push_back(std::string(table->getString(6).c_str()));
		l_l_result.push_back(std::string(table->getString(7).c_str()));
		l_l_result.push_back(std::string(table->getString(8).c_str()));
		l_l_result.push_back(std::to_string(table->getInt(9)));
		l_l_result.push_back(std::string(table->getString(10).c_str()));
		l_l_result.push_back(std::string(table->getString(2).c_str()));

		l_result.push_back(l_l_result);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyUser)
	{
		delete MyUser;
		MyUser = NULL;
	}

	return l_result;
}

std::vector<std::vector<std::string>> DatabaseInterface::GetAllRole()
{
	BLL::Role *MyRole = new BLL::Role();
	sql::ResultSet* table = MyRole->SelectAll();
	std::vector<std::vector<std::string> > l_result;

	if (!table)
	{
		if(MyRole)
		{
			delete MyRole;
			MyRole = NULL;
		}
		
		return l_result;
	}
	
	while (table->next())
	{
		std::vector<std::string> l_l_result;
		std::string l_id =std::string(std::to_string(table->getInt(1)));
		std::string l_usr =std::string(table->getString(2).c_str());
		
		l_l_result.push_back(l_id);
		l_l_result.push_back(l_usr);

		l_result.push_back(l_l_result);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyRole)
	{
		delete MyRole;
		MyRole = NULL;
	}

	return l_result;
}


int DatabaseInterface::InsertDevice(
	std::string p_manufacturer,
	std::string p_model,
	float p_width,
	float p_height,
	int p_ncolor,
	std::string p_multitype
	)
{
	BLL::Device *MyVMS = new BLL::Device();
	int id_vms_inserted = INT_MAX;
	if(MyVMS)
		id_vms_inserted = MyVMS->Insert(p_manufacturer,p_model,p_width, p_height, p_ncolor, p_multitype);

	if(MyVMS)
	{
		delete MyVMS;
		MyVMS = NULL;
	}

	return id_vms_inserted;
};

bool DatabaseInterface::DeleteDevice(int pId)
{
	BLL::Device *MyVMS = new BLL::Device();
	bool successful = MyVMS->Delete(pId);

	if(MyVMS)
	{
		delete MyVMS;
		MyVMS = NULL;
	}

	if(successful)
		return true;
	else
		return false;

	return false;
}

bool DatabaseInterface::UpdateDevice(
	int p_id,
	std::string p_manufacturer,
	std::string p_model,
	float p_width,
	float p_heigth,
	int p_color,
	std::string p_multitype)
{
	
	BLL::Device *MyDevice = new BLL::Device();

	bool succesful = MyDevice->Update(p_id, p_manufacturer, p_model, p_width, p_heigth, p_color, p_multitype);

	if(MyDevice)
	{
		delete MyDevice;
		MyDevice = NULL;
	}

	if(succesful)
		return true;
	else
		return false;
	
	return false;
}

std::vector<std::vector<std::string> > DatabaseInterface::GetAllDevice()
{
	
	BLL::Device *MyDevice = new BLL::Device();
	sql::ResultSet *table = MyDevice->SelectAll();
	std::vector<std::vector<std::string> > l_result;

	if (!table)
	{
		delete MyDevice;
		MyDevice = NULL;
		return l_result;
	}

	while (table->next())
	{
		std::vector<std::string> l_l_result;

		l_l_result.push_back(std::to_string(table->getInt(1)));
		l_l_result.push_back(std::string(table->getString(2).c_str()));
		l_l_result.push_back(std::string(table->getString(3).c_str()));
		l_l_result.push_back(std::to_string(table->getDouble(4)));
		l_l_result.push_back(std::to_string(table->getDouble(5)));
		l_l_result.push_back(std::to_string(table->getInt(6)));
		l_l_result.push_back(std::string(table->getString(7).c_str()));

		l_result.push_back(l_l_result);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyDevice)
	{
		delete MyDevice;
		MyDevice = NULL;
	}

	return l_result;
}

bool DatabaseInterface::ExistObjectName(std::string p_name)
{
	BLL::Object *MyObject = new BLL::Object();
	bool l_true_false = MyObject->ExistName(p_name);

	if(MyObject)
	{
		delete MyObject;
		MyObject = NULL;
	}

	return l_true_false;
};

bool DatabaseInterface::ExistObjectIP(std::string p_ip)
{
	BLL::Object *MyObject = new BLL::Object();
	bool l_true_false = MyObject->ExistIP(p_ip);

	if(MyObject)
	{
		delete MyObject;
		MyObject = NULL;
	}

	return l_true_false;
};

int DatabaseInterface::InsertObject(
	std::string p_name,
	std::string p_ip,
	int p_port,
	std::string p_description,
	std::string p_location,
	int p_deviceid,
	std::string  p_program,
	std::string p_screenshot,
	int p_status
	)
	
{
	BLL::Object *MyObject = new BLL::Object();
	int id_vms_inserted = MyObject->Insert(p_name,p_ip,p_port, p_description, p_location, p_deviceid, p_program, p_screenshot,p_status);

	if(MyObject)
	{
		delete MyObject;
		MyObject = NULL;
	}

	return id_vms_inserted;
};

bool DatabaseInterface::DeleteObject(int p_id)
{
	BLL::Object *MyObject = new BLL::Object();
	bool successful = false;

	if(MyObject)
	{
		successful = MyObject->Delete(p_id);
		delete MyObject;
		MyObject = NULL;
	}

	if (successful)
		return true;
	else
		return false;

	return false;
};

int DatabaseInterface::UpdateObject(
	int p_id,
	std::string p_name,
	std::string p_ip,
	int p_port,
	std::string p_description,
	std::string p_location,
	int p_deviceid,
	std::string  p_program,
	std::string p_screenshot,
	int p_status)
	
{
	BLL::Object *MyObject = new BLL::Object();

	int succesful = 0 ;
	if(MyObject)
	{
		succesful = MyObject->Update(p_id, p_name, p_ip,p_port, p_description, p_location, p_deviceid, p_program,p_screenshot, p_status);
		delete MyObject;
		MyObject = NULL;
	}
	
	return succesful;
};

std::vector<std::vector<std::string> >	DatabaseInterface::GetAllObject(std::string p_account)
{
	BLL::User *MyUser = new BLL::User();
	bool l_b_isAdmin = MyUser->IsAdmin(p_account);
	sql::ResultSet* table;
	std::vector<std::vector<std::string> > l_array_object;
	BLL::Object *MyObject = new BLL::Object();
	if(l_b_isAdmin)
	{
		table = MyObject->SelectAll();
	}
	else
	{
		table = MyObject->SelectAll(p_account);
	}

	if (!table)
	{
		if(MyObject)
		{
			delete MyObject;
			MyObject = NULL;
		}
		if(MyUser)
		{
			delete MyUser;
			MyUser = NULL;
		}
		return l_array_object;
	}

	while (table->next())
	{
		std::vector<std::string> l_object;
		l_object.push_back(std::to_string(table->getInt(1)));
		l_object.push_back(std::string(table->getString(2)));
		l_object.push_back(std::string(table->getString(3)));
		l_object.push_back(std::to_string(table->getInt(4)));
		l_object.push_back(std::string(table->getString(5)));
		l_object.push_back(std::string(table->getString(6)));
		l_object.push_back(std::to_string(table->getInt(7)));
		l_object.push_back(std::string(table->getString(8)));
		l_object.push_back(std::string(table->getString(9)));
		l_object.push_back(std::to_string(table->getInt(10)));

		l_object.push_back(std::string(table->getString(12)));
		l_object.push_back(std::string(table->getString(13)));
		l_object.push_back(std::to_string(table->getDouble(14)));
		l_object.push_back(std::to_string(table->getDouble(15)));
		l_object.push_back(std::to_string(table->getInt(16)));
		l_object.push_back(std::string(table->getString(17)));

		l_array_object.push_back(l_object);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyObject)
	{
		delete MyObject;
		MyObject = NULL;
	}
	if(MyUser)
	{
		delete MyUser;
		MyUser = NULL;
	}

	return l_array_object;
}


std::vector<std::string>DatabaseInterface::GetObjectDetail(int p_id)
{
	std::vector<std::string> l_object;
	BLL::Object *MyObject = new BLL::Object();
	
	sql::ResultSet* table = MyObject->SelectWhere(p_id);
	if (!table)
	{
		if(MyObject)
		{
			delete MyObject;
			MyObject = NULL;
		}
		
		return l_object;
	}

	while (table->next())
	{
		l_object.push_back(std::to_string(table->getInt(1)));
		l_object.push_back(std::string(table->getString(2)));
		l_object.push_back(std::string(table->getString(3)));
		l_object.push_back(std::to_string(table->getInt(4)));
		l_object.push_back(std::string(table->getString(5)));
		l_object.push_back(std::to_string(table->getInt(6)));
		l_object.push_back(std::string(table->getString(7)));
		l_object.push_back(std::string(table->getString(8)));
		l_object.push_back(std::string(table->getString(9)));
		l_object.push_back(std::to_string(table->getInt(10)));

		l_object.push_back(std::to_string(table->getInt(11)));
		l_object.push_back(std::string(table->getString(12)));
		l_object.push_back(std::string(table->getString(13)));
		l_object.push_back(std::to_string(table->getDouble(14)));
		l_object.push_back(std::to_string(table->getDouble(15)));
		l_object.push_back(std::to_string(table->getInt(16)));
		l_object.push_back(std::string(table->getString(17)));
		
		break;
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyObject)
	{
		delete MyObject;
		MyObject = NULL;
	}

	return l_object;
}

std::vector<std::vector<std::string> >	DatabaseInterface::GetMonitoring(std::string p_account)
{
	std::vector<std::vector<std::string> > l_array_object;
	BLL::Object *MyObject = new BLL::Object();
	
	sql::ResultSet* table = MyObject->SelectAll(p_account);

	if(!table)
	{
		if(MyObject)
		{
			delete MyObject;
			MyObject = NULL;
		}

		return l_array_object;
	}

	while (table->next())
	{
		std::vector<std::string> l_object;
		
		l_object.push_back(std::string(table->getString(2)));
		l_object.push_back(std::string(table->getString(6)));
		l_object.push_back(std::to_string(table->getDouble(14)));
		l_object.push_back(std::to_string(table->getDouble(15)));
		l_object.push_back(std::to_string(table->getInt(10)));
		l_object.push_back(std::string(table->getString(9)));
		l_object.push_back(std::to_string(table->getInt(1)));
		l_object.push_back(std::string(table->getString(3)));
		l_object.push_back(std::string(table->getString(8)));
		
		l_array_object.push_back(l_object);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyObject)
	{
		delete MyObject;
		MyObject = NULL;
	}

	return l_array_object;
}

std::vector<std::vector<std::string> > DatabaseInterface::GetAllProgram()
{
	BLL::Program *MyProgram = new BLL::Program();
	
	sql::ResultSet* table = MyProgram->SelectAll();
	std::vector<std::vector<std::string> > l_result;
	if (!table)
	{
		if(MyProgram)
		{
			delete MyProgram;
			MyProgram = NULL;
		}
		
		return l_result;
	}


	while (table->next())
	{
		std::vector<std::string> l_l_result;

		l_l_result.push_back(std::to_string(table->getInt(1)));
		l_l_result.push_back(std::string(table->getString(2).c_str()));
		l_l_result.push_back(std::to_string(table->getInt(3)));
		l_l_result.push_back(std::string(table->getString(4).c_str()));
		l_l_result.push_back(std::to_string(table->getInt(5)));
		l_l_result.push_back(std::string(table->getString(6).c_str()));
	
		l_result.push_back(l_l_result);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyProgram)
	{
		delete MyProgram;
		MyProgram = NULL;
	}

	return l_result;
}


std::vector<std::string> DatabaseInterface::GetProgram(int p_id)
{
	BLL::Program *MyProgram = new BLL::Program();
	
	sql::ResultSet* table = MyProgram->Select(p_id);
	std::vector<std::string> l_result;
	if (!table)
	{
		if(MyProgram)
		{
			delete MyProgram;
			MyProgram = NULL;
		}
		
		return l_result;
	}
	while (table->next())
	{
		l_result.push_back(std::to_string(table->getInt(1)));
		l_result.push_back(std::string(table->getString(2).c_str()));
		l_result.push_back(std::to_string(table->getInt(3)));
		l_result.push_back(std::string(table->getString(4).c_str()));
		l_result.push_back(std::to_string(table->getInt(5)));
		l_result.push_back(std::to_string(table->getInt(6)));

		break;
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyProgram)
	{
		delete MyProgram;
		MyProgram = NULL;
	}

	return l_result;
}


bool DatabaseInterface::AssignVMS(std::string p_name, std::vector<int> p_listid)
{
	BLL::UserObject *MyUserObject = new BLL::UserObject();
	if(MyUserObject->Delete(p_name))
	{
		for(size_t i=0; i < p_listid.size(); i++)
		{
			if(!MyUserObject->Insert(p_name, p_listid[i]))
			{
				if(MyUserObject)
				{
					delete MyUserObject;
					MyUserObject = NULL;
				}

				return false;
			}
		}
	}
	else
	{
		if(MyUserObject)
		{
			delete MyUserObject;
			MyUserObject = NULL;
		}
		return false;
	}

	if(MyUserObject)
	{
		delete MyUserObject;
		MyUserObject = NULL;
	}

	return true;
}


bool DatabaseInterface::InsertProgram(std::string p_name, int p_type, std::string p_content, float p_w, float p_h)
{
	BLL::Program *MyProgram = new BLL::Program();
	bool successful = false;

	if(MyProgram)
	{
		successful =  MyProgram->Insert(p_name, p_type, p_content, p_w, p_h);
		delete MyProgram;
		MyProgram = NULL;
	}

	return successful;
}


bool DatabaseInterface::UpdatetProgram(int p_id, std::string p_name, int p_type, std::string p_content, float p_w, float p_h)
{
	BLL::Program *MyProgram = new BLL::Program();
	bool successful = false;
	if(MyProgram)
	{
		successful = MyProgram->Update(p_id, p_name, p_type, p_content, p_w, p_h);
		delete MyProgram;
		MyProgram = NULL;
	}

	return successful;
}

bool DatabaseInterface::DeleteProgram(int pId)
{
	BLL::Program *MyProgram = new BLL::Program();
	bool successful = false;
	
	if(MyProgram)
	{
		successful = MyProgram->Delete(pId);
		delete MyProgram;
		MyProgram = NULL;
	}

	if(successful)
		return true;
	else
		return false;

	return false;
}

bool DatabaseInterface::InsertImage(std::string)
{

	return false;
};

bool DatabaseInterface::UpdatetImage(int, std::string)
{

	return false;
};

bool DatabaseInterface::DeleteImage(int)
{

	return false;
};

std::vector<std::vector<std::string> >	DatabaseInterface::GetAllImage()
{
	std::vector<std::vector<std::string> > l_array_image;
	BLL::ImageSource *MyImage = new BLL::ImageSource();
	sql::ResultSet* table = MyImage->SelectAll();
	if (!table)
	{
		if(MyImage)
		{
			delete MyImage;
			MyImage = NULL;
		}
		
		return l_array_image;
	}

	while (table->next())
	{
		std::vector<std::string> l_image;
		l_image.push_back(std::string(table->getString(1)));
		l_image.push_back(std::string(table->getString(2)));
		l_image.push_back(std::string(table->getString(3)));
		
		l_array_image.push_back(l_image);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyImage)
	{
		delete MyImage;
		MyImage = NULL;
	}

	return l_array_image;
};



std::vector<std::vector<std::string> > DatabaseInterface::GetAllAction()
{
	std::vector<std::vector<std::string> > l_array_action;
	BLL::Action *MyAction = new BLL::Action();
	sql::ResultSet* table = MyAction->SelectAll();
	if (!table)
	{
		if(MyAction)
		{
			delete MyAction;
			MyAction = NULL;
		}
		
		return l_array_action;
	}
	while (table->next())
	{
		std::vector<std::string> l_action;
		l_action.push_back(std::to_string(table->getInt(1)));
		l_action.push_back(std::string(table->getString(3)));

		l_array_action.push_back(l_action);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyAction)
	{
		delete MyAction;
		MyAction = NULL;
	}

	return l_array_action;

}


bool DatabaseInterface::InsertHistory(
				std::string p_username,
				int p_action,
				std::string p_detail)
{
	BLL::History *MyHistory = new BLL::History();
	bool l_true_false = false;
	if(MyHistory)
		l_true_false = MyHistory->Insert(p_username,p_action, p_detail);

	if(MyHistory)
	{
		delete MyHistory;
		MyHistory = NULL;
	}

	return l_true_false;
};


std::vector<std::vector<std::string> > DatabaseInterface::GetAllHistory()
{
	std::vector<std::vector<std::string> > l_array_history;
	BLL::History *MyHistory = new BLL::History();
	sql::ResultSet* table = MyHistory->SelectAll();
	if (!table)
	{
		if(MyHistory)
		{
			delete MyHistory;
			MyHistory = NULL;
		}
		
		return l_array_history;
	}

	while (table->next())
	{
		std::vector<std::string> l_history;
		l_history.push_back(std::to_string(table->getInt(1))); //id
		l_history.push_back(std::string(table->getString(2))); //username
		l_history.push_back(std::to_string(table->getInt(3))); //action
		l_history.push_back(std::string(table->getString(4))); //time
		l_history.push_back(std::string(table->getString(5))); //detail
		l_history.push_back(std::to_string(table->getInt(6))); //action
		l_history.push_back(std::string(table->getString(7))); //name
		l_history.push_back(std::string(table->getString(8))); //description

		l_array_history.push_back(l_history);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyHistory)
	{
		delete MyHistory;
		MyHistory = NULL;
	}

	return l_array_history;
};



std::vector<std::vector<std::string> > DatabaseInterface::GetWhereHistory(
				std::string p_username,
				int p_action,
				std::string p_starttime,
				std::string p_endtime)
{
	std::vector<std::vector<std::string> > l_array_history;
	BLL::History *MyHistory = new BLL::History();
	sql::ResultSet* table = MyHistory->SelectWhere(p_username, p_action, p_starttime, p_endtime);
	
	if (!table)
	{
		if(MyHistory)
		{
			delete MyHistory;
			MyHistory = NULL;
		}
		
		return l_array_history;
	}

	while (table->next())
	{
		std::vector<std::string> l_history;
		l_history.push_back(std::to_string(table->getInt(1))); //id
		l_history.push_back(std::string(table->getString(2))); //username
		l_history.push_back(std::to_string(table->getInt(3))); //action
		l_history.push_back(std::string(table->getString(4))); //time
		l_history.push_back(std::string(table->getString(5))); //detail
		l_history.push_back(std::to_string(table->getInt(6))); //action
		l_history.push_back(std::string(table->getString(7))); //name
		l_history.push_back(std::string(table->getString(8))); //description

		l_array_history.push_back(l_history);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyHistory)
	{
		delete MyHistory;
		MyHistory = NULL;
	}

	return l_array_history;
};