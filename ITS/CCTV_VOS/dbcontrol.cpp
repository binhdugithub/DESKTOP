/*
 * dbcontrol.cpp
 *
 *  Created on: Jul 31, 2014
 *      Author: xyz
 */

#include "dbcontrol.h"


DBControl::DBControl()
{
	std::cout << "Khoi tao DBcontroler" << std::endl;
	m_DA = new DAL::DataAccess();
}

DBControl::~DBControl()
{
	if (m_DA)
	{
		delete m_DA;
		m_DA = NULL;
	}
}



int DBControl::addSource(const string& ip, const string& inputurl, const string& inputname, const string& usr, const string& pwd,
		const string& outputurl, const string& framewidth, const string& frameheight, const string& codec, const string& framerate, const string& status)
{
	std::cout << "DBControll::addSource" << std::endl;
	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	string table = "its_vos_sources";
	// insert into database
	string msqlCommand = "INSERT INTO " + table + /*"(inputurl, outputurl, outputwidth, outputheight, outputcodec, outputframerate"*/ +
			" VALUES('" + ip + "', '" + inputurl + "','" + inputname + "','" + usr + "','" + pwd +
			"','" + outputurl + "','" + framewidth + "','" + frameheight + "','" + codec + "','" + framerate + "','" + status + "')";

	int res = m_DA->QueryUpdate(msqlCommand);

	return res;
}

int DBControl::removeSource(const string& camip)
{
	std::cout << "DBControll::removeSource" << std::endl;

	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	string table = "its_vos_sources";
	string msqlCommand = "DELETE FROM " + table + " WHERE " + " cameraip = '" + camip + "'";

	int r = m_DA->QueryUpdate(msqlCommand);
	return r;
}

int DBControl::getDisplayPosition(vector<int>& dspPos)
{
	std::cout << "DBControll::getDisplayPosition" << std::endl;
	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	string l_query = "SELECT * FROM its_vos_text_position";
	sql::ResultSet *table = m_DA->QueryData(l_query);
	if(table)
	{
		while (table->next())
		{
			for(int i = 1; i < 7; i++)
			{
				int pos = table->getInt(i);
				if(pos < 1 || pos > 6)
				{
					return -1;
				}

				dspPos.push_back(pos);
			}

			break;
		}

		delete table;
		table = NULL;
	}
	else
	{
		std::cout << "DATABASE: Get position info failed" << std::endl;
		LOG_ERROR("DATABASE: Get position info failed");
	}

	return 0;
}

int DBControl::addLayout(int lanepos, int staffpos, int classpos, int licensenumberpos, int pricepos, int timestamppos)
{
	std::cout << "DBControll::addLayout" << std::endl;

	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	if(lanepos > 6 || lanepos < 1 || staffpos > 6 || staffpos < 1 || classpos > 6 || classpos < 1
			|| licensenumberpos > 6 || licensenumberpos < 1 || pricepos > 6 || pricepos < 1 || timestamppos > 6 || timestamppos < 1)
	{
		return -1;
	}

	string lane = elc::toString(lanepos);
	string staff = elc::toString(staffpos);
	string classp = elc::toString(classpos);
	string license = elc::toString(licensenumberpos);
	string price = elc::toString(pricepos);
	string timesp = elc::toString(timestamppos);
	string status = "OK";

	string msqlcommand = std::string("INSERT INTO its_vos_text_position")  + " VALUES('" + lane + "', '" + staff + "','" + classp + "', '" + license + "', '" + "', '" + price + "', '" + timesp + "', '" + status + "')";


	int res = m_DA->QueryUpdate(msqlcommand);
	return res;
}

int DBControl::getSource(const string& id, string& inputurl, string& inputname, string& username, string& password, string& status)
{
	std::cout << "DBControll::getSource" << std::endl;
	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	string l_query = "SELECT * FROM its_vos_sources WHERE cameraip = '" + id + "'";
	sql::ResultSet *table = m_DA->QueryData(l_query);
	if(table)
	{
		while (table->next())
		{
			inputurl = table->getString(2);
			inputname = table->getString(3);
			username = table->getString(4);
			password = table->getString(5);
			status = table->getString(11);

			break;
		}

		delete table;
		table = NULL;
	}
	else
	{
		std::cout << "DATABASE: Get vos sources info failed" << std::endl;
		LOG_ERROR("DATABASE: Get vos sources info failed");
	}

	return 0;
}

int DBControl::getAllSource(vector<string>& camip, vector<string>& inputurl, vector<string>& inputname, vector<string>& username, vector<string>& password,
		vector<string>& outputurl, vector<string>& framewidth, vector<string>& frameheight, vector<string>& codec, vector<string>& framerate, vector<string>& status)
{
	std::cout << "DBControll::getAllSource" << std::endl;
	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	string l_query = "SELECT * FROM its_vos_sources";
	sql::ResultSet *table = m_DA->QueryData(l_query);
	if(table)
	{
		while (table->next())
		{
			camip.push_back(table->getString(1));
			inputurl.push_back(table->getString(2));
			inputname.push_back(table->getString(3));
			username.push_back(table->getString(4));
			password.push_back(table->getString(5));
			outputurl.push_back(table->getString(6));
			framewidth.push_back(table->getString(7));
			frameheight.push_back(table->getString(8));
			codec.push_back(table->getString(9));
			framerate.push_back(table->getString(10));
			status.push_back(table->getString(11));
		}

		delete table;
		table = NULL;
	}
	else
	{
		std::cout << "DATABASE: Get position info failed" << std::endl;
		LOG_ERROR("DATABASE: Get position info failed");
	}

	return 0;
}

// return 0 means susscessfully, otherwise fail.
int DBControl::updateSource(const string& id, const string& outputurl, const string& framewidth, const string& frameheight,
			const string& codec, const string& framerate,const string& status)
{
	std::cout << "DBControll::updateSource" << std::endl;
	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	string l_query = std::string("UPDATE its_vos_sources SET") +
			std::string(" outputurl='") + outputurl + std::string("',")+
			std::string(" outputframewidth ='") + framewidth + std::string("',") +
			std::string(" outputframeheight='") + frameheight + std::string("',") +
			std::string(" outputcodec='") + codec + std::string("',") +
			std::string(" outputframerate='") + framerate + std::string("',") +
			std::string(" status='") + status + std::string("'") +
			std::string(" WHERE cameraip='") + id + std::string("'");

	int res = m_DA->QueryUpdate(l_query);
	return res;
}

int DBControl::updateSourceStatus(const string& id, const string& status)
{
	std::cout << "DBControll::updateSourceStatus" << std::endl;
	if (m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	string msqlCommand = std::string("UPDATE its_vos_sources SET status='") + status + std::string("' WHERE cameraip='") + id + std::string("'");
	int res = m_DA->QueryUpdate(msqlCommand);

	return res;
}

int DBControl::updateAllSourceStatus(const string& status)
{
	std::cout << "DBControll::updateallSourceStatus" << std::endl;

	if(m_DA == NULL)
	{
		m_DA = new DAL::DataAccess();
	}

	string msqlCommand = std::string("UPDATE its_vos_sources SET status='") + status + std::string("'");

	int res = m_DA->QueryUpdate(msqlCommand);

	return res;
}


