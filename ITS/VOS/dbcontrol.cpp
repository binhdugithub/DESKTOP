/*
 * dbcontrol.cpp
 *
 *  Created on: Jul 31, 2014
 *      Author: xyz
 */

#include "dbcontrol.h"

DBControl::DBControl()
{

}

DBControl::~DBControl()
{
	closeDB();
}

bool DBControl::openDB(const string& mhost, const string& muser, const string& mpwd, const string& mdbname)
{
	host = mhost;
	user = muser;
	pwd = mpwd;
	dbname = mdbname;
	return openDB();
}

// check sql connection status, if it is not alive, close and reconnect.
// return true if connection are ready to use. Otherwise return false

bool DBControl::autoConnectDB()
{
	if(connection->server_status == MYSQL_STATUS_READY)
		return true;
	if(reopenDB())
		return true;
	return false;
}

bool DBControl::openDB()
{
	connection = mysql_init(NULL);
	if(!connection)
	{
		LOG_ERROR("Can not init DB");
		return false;
	}
	connection = mysql_real_connect(connection,host.c_str(), user.c_str(), pwd.c_str(),dbname.c_str(), 0, NULL, 0);
	if(!connection)
	{
		LOG_ERROR("Can not connect to DB host="<<host<<" user="<<user<<" dbname="<<dbname);
		return false;
	}
	return true;
}

int DBControl::addSource(const string& ip, const string& inputurl, const string& inputname, const string& usr, const string& pwd,
		const string& outputurl, const string& framewidth, const string& frameheight, const string& codec, const string& framerate, const string& status)
{
	dbLocker.lock();
	if(!openDB())
	{
		dbLocker.unlock();
		return -1;
	}
	string table = "its_vos_sources";
	// insert into database
	string msqlCommand = "INSERT INTO " + table + /*"(inputurl, outputurl, outputwidth, outputheight, outputcodec, outputframerate"*/ +
			" VALUES('" + ip + "', '" + inputurl + "','" + inputname + "','" + usr + "','" + pwd +
			"','" + outputurl + "','" + framewidth + "','" + frameheight + "','" + codec + "','" + framerate + "','" + status + "')";
	//cout<<"connection: "<<connection<<"  "<<cout<<msqlCommand<<endl;
	int res = mysql_query(connection, msqlCommand.c_str());
	dbLocker.unlock();
	closeDB();
	return res;
}

int DBControl::removeSource(const string& camip)
{
	// delete source
	LOG_INFO("Delete source camip = "<<camip);
	dbLocker.lock();
	if(!openDB())
	{
		LOG_ERROR("Connection is died");
		dbLocker.unlock();
		return -1;
	}
	dbLocker.unlock();
	string table = "its_vos_sources";
	string msqlCommand = "DELETE FROM " + table + " WHERE " + " cameraip = '" + camip + "'";
	LOG_INFO("Mysql query = "<<msqlCommand);
	int r = mysql_query(connection, msqlCommand.c_str());

	closeDB();
	return r;
}

int DBControl::getDisplayPosition(vector<int>& dspPos)
{
	dbLocker.lock();
	if(!openDB())
	{
		dbLocker.unlock();
		return -1;
	}
	string table = "its_vos_text_position";
	string msqlCommand = "SELECT * FROM "+ table;
	//cout<<"connection: "<<connection<<"  "<<msqlCommand<<endl;
	mysql_query(connection, msqlCommand.c_str());
	//cout<<"after query: "<<connection<<"  "<<msqlCommand<<endl;
	res_set = mysql_store_result(connection);
	unsigned int numrows = mysql_num_rows(res_set);
	unsigned int numfield = mysql_num_fields(res_set);
	row = mysql_fetch_row(res_set);
	if(row == NULL)
	{
		dbLocker.unlock();
		return -1;
	}

	for(int i = 0; i < numfield - 1; ++i)
	{
		int pos = elc::toInt(row[i]);
		if(pos < 1 || pos > 6)
		{
			dbLocker.unlock();
			return -1;
		}
		dspPos.push_back(pos);
	}

	mysql_free_result(res_set);
	dbLocker.unlock();
	closeDB();
	return 0;
}

int DBControl::addLayout(int lanepos, int staffpos, int classpos, int licensenumberpos, int pricepos, int timestamppos)
{
	dbLocker.lock();
	if(!connection)
	{
		dbLocker.unlock();
		return -1;
	}
	if(lanepos > 6 || lanepos < 1 || staffpos > 6 || staffpos < 1 || classpos > 6 || classpos < 1
			|| licensenumberpos > 6 || licensenumberpos < 1 || pricepos > 6 || pricepos < 1 || timestamppos > 6 || timestamppos < 1)
	{
		dbLocker.unlock();
		return -1;
	}

	string table = "its_vos_text_position";
	string lane = elc::toString(lanepos);
	string staff = elc::toString(staffpos);
	string classp = elc::toString(classpos);
	string license = elc::toString(licensenumberpos);
	string price = elc::toString(pricepos);
	string timesp = elc::toString(timestamppos);
	string status = "OK";

	string msqlcommand = "INSERT INTO " + table +
			" VALUES('" + lane + "', '" + staff + "','" + classp + "', '" + license + "', '" + "', '" + price + "', '" + timesp + "', '" + status + "')";

	//cout<<"connection: "<<connection<<"  "<<cout << msqlcommand <<endl;
	int res = mysql_query(connection, msqlcommand.c_str());
	dbLocker.unlock();
	return res;
}

int DBControl::getSource(const string& id, string& inputurl, string& inputname, string& username, string& password, string& status)
{
	dbLocker.lock();
	if(!openDB())
	{
		dbLocker.unlock();
		return -1;
	}

	string table = "its_vos_sources";
	string msqlCommand = "SELECT * FROM "+ table + " WHERE cameraip = '" + id + "'";
	//cout<<"connection: "<<connection<<"  "<<cout<<msqlCommand<<endl;
	int res = mysql_query(connection, msqlCommand.c_str());
	if(res != 0)
	{
		dbLocker.unlock();
		return res;
	}
	res_set = mysql_store_result(connection);
	unsigned int numrows = mysql_num_rows(res_set);
	unsigned int numfield = mysql_num_fields(res_set);
	row = mysql_fetch_row(res_set);
	if(row == NULL)
	{
		dbLocker.unlock();
		return -1;
	}
	inputurl = row[1];
	inputname = row[2];
	username = row[3];
	password = row[4];
	status = row[10];

	mysql_free_result(res_set);
	dbLocker.unlock();

	closeDB();
	return 0;
}

int DBControl::getAllSource(vector<string>& camip, vector<string>& inputurl, vector<string>& inputname, vector<string>& username, vector<string>& password,
		vector<string>& outputurl, vector<string>& framewidth, vector<string>& frameheight, vector<string>& codec, vector<string>& framerate, vector<string>& status)
{
	dbLocker.lock();
	if(!openDB())
	{
		dbLocker.unlock();
		return -1;
	}
	string table = "its_vos_sources";
	string msqlCommand = "SELECT * FROM "+ table;
	//cout<<"connection: "<<connection<<"  "<<cout<<msqlCommand<<endl;
	int res = mysql_query(connection, msqlCommand.c_str());
	if(res != 0)
	{
		dbLocker.unlock();
		return res;
	}
	res_set = mysql_store_result(connection);
	unsigned int numrows = mysql_num_rows(res_set);
	unsigned int numfield = mysql_num_fields(res_set);
	// TODO check if numfield != 11 -- may return
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{
		camip.push_back(row[0]);
		inputurl.push_back(row[1]);
		inputname.push_back(row[2]);
		username.push_back(row[3]);
		password.push_back(row[4]);
		outputurl.push_back(row[5]);
		framewidth.push_back(row[6]);
		frameheight.push_back(row[7]);
		codec.push_back(row[8]);
		framerate.push_back(row[9]);
		status.push_back(row[10]);
	}

	mysql_free_result(res_set);
	dbLocker.unlock();
	closeDB();
	return 0;
}

// return 0 means susscessfully, otherwise fail.
int DBControl::updateSource(const string& id, const string& outputurl, const string& framewidth, const string& frameheight,
			const string& codec, const string& framerate,const string& status)
{
	dbLocker.lock();
	if(!openDB())
	{
		dbLocker.unlock();
		return -1;
	}
	string table = "its_vos_sources";
	string msqlCommand = "UPDATE " + table + " SET" +
			" outputurl='" + outputurl + "'," +
			" outputframewidth='" + framewidth + "'," +
			" outputframeheight='" + frameheight + "'," +
			" outputcodec='" + codec + "'," +
			" outputframerate='" + framerate + "'," +
			" status='" + status + "'" +
			" WHERE cameraip='" + id + "'";
	//cout<<"connection: "<<connection<<"  "<<cout<<msqlCommand<<endl;
	int res = mysql_query(connection, msqlCommand.c_str());
	dbLocker.unlock();
	closeDB();
	return res;
}

int DBControl::updateSourceStatus(const string& id, const string& status)
{
	dbLocker.lock();
	if(!openDB())
	{
		dbLocker.unlock();
		return -1;
	}

	string table = "its_vos_sources";
	string msqlCommand = "UPDATE " + table + " SET" +
			" status='" + status + "'" +
			" WHERE cameraip='" + id + "'";
	//cout<<"connection: "<<connection<<"  "<<cout<<msqlCommand<<endl;
	int res = mysql_query(connection, msqlCommand.c_str());
	dbLocker.unlock();
	closeDB();
	return res;
}

int DBControl::updateAllSourceStatus(const string& status)
{
	dbLocker.lock();
	if(!openDB())
	{
		dbLocker.unlock();
		return -1;
	}

	string table = "its_vos_sources";
	string msqlCommand = "UPDATE " + table + " SET" +
			" status='" + status + "'";
	//cout<<"connection: "<<connection<<"  "<<msqlCommand<<endl;
	int res = mysql_query(connection, msqlCommand.c_str());

	dbLocker.unlock();
	closeDB();
	return res;
}

int DBControl::closeDB()
{
	dbLocker.lock();
	LOG_INFO("DBControl Close connection: ");
	mysql_close(connection);
	dbLocker.unlock();
	return 0;
}

bool DBControl::reopenDB()
{
	closeDB();
	return openDB();
}
