#ifndef DATABASE_INTERFACE_H_
#define DATABASE_INTERFACE_H_
#include <ostream>
#include <string>

#include "Story.h"
#include "App.h"
#include "MyLogger.h"


class DBInterface
{

public:
	DBInterface();
	virtual ~DBInterface();
private:
	static DBInterface *m_Instance;
	std::vector<std::vector<std::string> > m_ArrayStories;
	std::vector<std::vector<std::string> > m_ArrayApps;
public:
	static DBInterface* GetSingleton();
	bool InsertStory(
			std::string p_title,
			std::string p_content,
			std::string p_image,
			std::string p_audio);
	bool DeleteStory(int p_id);
	bool UpdateStory(
			int 		p_id,
			std::string p_title,
			std::string p_content,
			std::string p_image,
			std::string p_audio,
			float 		p_rate);

	std::vector<std::vector<std::string> > GetListStories(int p_idstart = 0, int p_limit = 0);
	std::vector<std::string> GetStory(int p_id);
	std::vector<std::vector<std::string> > GetListApps();

	void GetAllStories();
	void GetAllApps();
	std::vector<std::vector<std::string> > UpdateStories();
	std::vector<std::vector<std::string> > UpdateApps();
	std::vector<std::vector<std::string> > ReloadStories();
	std::vector<std::vector<std::string> > ReloadApps();

};

#endif
