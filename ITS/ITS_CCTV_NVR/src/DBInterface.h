#ifndef DATABASE_INTERFACE_H_
#define DATABASE_INTERFACE_H_
#include <ostream>
#include <string>

#include "LogFile.h"
#include "DataAccess.h"


class DBInterface
{

private:
	DAL::DataAccess *m_DA;

public:
	DBInterface();
	virtual ~DBInterface();
private:
	static DBInterface *m_Instance;
public:
	static DBInterface* GetSingleton();

	std::vector<std::vector<std::string>> GetRecordedCam();
	std::vector<std::vector<std::string>> GetListFile2Delete(int p_number);

	bool Insert(std::string p_query);
	bool Update(std::string p_query);
	bool Delete(std::string p_query);

};

#endif
