/*
 * dbcontrol.h
 *
 *  Created on: Jul 31, 2014
 *      Author: xyz
 */

#ifndef DBCONTROL_H_
#define DBCONTROL_H_

#include "mycommon.h"
#include "dp/yo_singleton.h"

class DBControl : public yo::common::YoSingleton<DBControl>
{
public:
	DBControl();
	virtual ~DBControl();
	bool openDB(const string& host, const string& user, const string& pwd, const string& dbname);
	bool openDB();
	//int addSource(const string& sourceurl, const string& ouputurl);
	int addSource(const string& camip, const string& inputurl, const string& inputname, const string& usr, const string& pwd,
			const string& outputurl, const string& framewidth, const string& frameheight, const string& codec, const string& framerate, const string& status);
	int addLayout(int lanepos, int staffpos, int classpos, int licensenumberpos, int pricepos, int timestamppos);
	int removeSource(const string& camip);
	int getDisplayPosition(vector<int>& dspPos);
	int getSource(const string& id, string& inputurl, string& inputname, string& username, string& password, string& status);
	// Get all sources from database, store in mem
	int getAllSource(vector<string>& camip, vector<string>& inputurl, vector<string>& inputname, vector<string>& username, vector<string>& password,
			vector<string>& outputurl, vector<string>& framewidth, vector<string>& frameheight, vector<string>& codec, vector<string>& framerate, vector<string>& status);
	int updateSource(const string& id, const string& outputurl, const string& framewidth, const string& frameheight,
			const string& codec, const string& framerate,const string& status);
	int updateSourceStatus(const string& id, const string& status);
	int updateAllSourceStatus(const string& status);
	int closeDB();
	bool reopenDB();
	bool autoConnectDB();

private:
	MYSQL *connection;
	MYSQL_RES *res_set; /* Create a pointer to recieve the return value.*/
	MYSQL_ROW row;
	string host;
	string user;
	string pwd;
	string dbname;
	std::recursive_mutex dbLocker;

};

#endif /* DBCONTROL_H_ */
