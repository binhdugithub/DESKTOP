
#include "DBInterface.h"

DBInterface* DBInterface::m_Instance = NULL;

DBInterface::DBInterface()
{
	this->GetAllApps();
	this->GetAllStories();
}


DBInterface::~DBInterface()
{

}

DBInterface* DBInterface::GetSingleton()
{
	if(m_Instance == NULL)
	{
		m_Instance = new DBInterface();
	}

	return m_Instance;
}


bool DBInterface::InsertStory(std::string p_title, std::string p_content, std::string p_image, std::string p_audio)
{
	return true;
};

bool DBInterface::DeleteStory(int p_id)
{
	return true;
};

bool DBInterface::UpdateStory(int p_id, std::string p_title, std::string p_content, std::string p_image, std::string p_audio, float p_rate)
{
	return true;
};

std::vector<std::vector<std::string> > DBInterface::GetListStories(int p_idstart, int p_limit)
{
	std::vector<std::vector<std::string> > l_result;

	if (m_ArrayStories.size() > 0)
	{
		int l_count = 0;

		for (int i=0; i < m_ArrayStories.size(); i++)
		{
			if(std::atoi(m_ArrayStories[i][0].c_str()) > p_idstart)
			{
				l_count++;
				l_result.push_back(m_ArrayStories[i]);

				if (l_count == p_limit)
					break;
			}
		}

	}
	else
	{
		BLL::Story *MyStory = new BLL::Story();
		sql::ResultSet* table = MyStory->SelectList(p_idstart, p_limit);
		if(!table)
		{
			if(MyStory)
			{
				delete MyStory;
				MyStory = NULL;
			}

			return l_result;
		}

		while (table->next())
		{
			std::vector<std::string> l_story;

			l_story.push_back(std::to_string(table->getInt(1)));
			l_story.push_back(std::string(table->getString(2).c_str()));
			l_story.push_back(std::string(table->getString(3).c_str()));
			l_story.push_back(std::string(table->getString(4).c_str()));
			l_story.push_back(std::string(table->getString(5).c_str()));
			l_story.push_back(std::to_string(table->getInt(6)));

			l_result.push_back(l_story);
		}

		if(table)
		{
			delete table;
			table = NULL;
		}

		if(MyStory)
		{
			delete MyStory;
			MyStory = NULL;
		}

	}


	return l_result;
}

std::vector<std::string> DBInterface::GetStory(int p_id)
{
	BLL::Story *MyStory = new BLL::Story();

	sql::ResultSet* table = MyStory->SelectWhere(p_id);
	std::vector<std::string> l_story;
	if(!table)
	{
		if(MyStory)
		{
			delete MyStory;
			MyStory = NULL;
		}

		return l_story;
	}

	while (table->next())
	{
		l_story.push_back(std::to_string(table->getInt(1)));
		l_story.push_back(std::string(table->getString(2).c_str()));
		l_story.push_back(std::string(table->getString(3).c_str()));
		l_story.push_back(std::string(table->getString(4).c_str()));
		l_story.push_back(std::string(table->getString(5).c_str()));
		l_story.push_back(std::to_string(table->getInt(6)));

		break;
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyStory)
	{
		delete MyStory;
		MyStory = NULL;
	}

	return l_story;
}


//Get list apps
std::vector<std::vector<std::string> > DBInterface::GetListApps()
{
	std::vector<std::vector<std::string> > l_result;
	if (m_ArrayApps.size() > 0)
	{
		return m_ArrayApps;
	}
	else
	{
		BLL::App *MyApp = new BLL::App();

		sql::ResultSet* table = MyApp->SelectAll();

		if(!table)
		{
			if(MyApp)
			{
				delete MyApp;
				MyApp = NULL;
			}

			return l_result;
		}

		while (table->next())
		{
			std::vector<std::string> l_app;

			//l_story.push_back(std::to_string(table->getInt(1)));
			l_app.push_back(std::string(table->getString(2).c_str()));
			l_app.push_back(std::string(table->getString(3).c_str()));
			l_app.push_back(std::string(table->getString(4).c_str()));

			l_result.push_back(l_app);
		}

		if(table)
		{
			delete table;
			table = NULL;
		}

		if(MyApp)
		{
			delete MyApp;
			MyApp = NULL;
		}


	}

	return l_result;
}
//end get list app


void DBInterface::GetAllStories()
{
	BLL::Story *MyStory = new BLL::Story();

	sql::ResultSet* table = MyStory->SelectAll();

	if(!table)
	{
		if(MyStory)
		{
			delete MyStory;
			MyStory = NULL;
		}

		return;
	}

	while (table->next())
	{
		std::vector<std::string> l_story;

		l_story.push_back(std::to_string(table->getInt(1)));
		l_story.push_back(std::string(table->getString(2).c_str()));
		l_story.push_back(std::string(table->getString(3).c_str()));
		l_story.push_back(std::string(table->getString(4).c_str()));
		l_story.push_back(std::string(table->getString(5).c_str()));
		l_story.push_back(std::to_string(table->getInt(6)));

		m_ArrayStories.push_back(l_story);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyStory)
	{
		delete MyStory;
		MyStory = NULL;
	}

	std::cout << "Get " << m_ArrayStories.size() << " stories" << std::endl;
	LOG_INFO("Get " << m_ArrayStories.size() << " storeis");

	return;

}


void DBInterface::GetAllApps()
{
	BLL::App *MyApp = new BLL::App();

	sql::ResultSet* table = MyApp->SelectAll();
	if(!table)
	{
		if(MyApp)
		{
			delete MyApp;
			MyApp = NULL;
		}

		return;
	}

	while (table->next())
	{
		std::vector<std::string> l_app;

		l_app.push_back(std::to_string(table->getInt(1)));
		l_app.push_back(std::string(table->getString(2).c_str()));
		l_app.push_back(std::string(table->getString(3).c_str()));
		l_app.push_back(std::string(table->getString(4).c_str()));

		m_ArrayApps.push_back(l_app);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyApp)
	{
		delete MyApp;
		MyApp = NULL;
	}

	std::cout << "Get " << m_ArrayApps.size() << " apps" << std::endl;
	LOG_INFO("Get " << m_ArrayApps.size() << " apps");

	return;
}


std::vector<std::vector<std::string> > DBInterface::UpdateStories()
{
	auto it = m_ArrayStories.end() - 1;
	int l_idstart = std::atoi((*it)[0].c_str());
	std::cout << "Updatestories from id:" << l_idstart << std::endl;
	LOG_INFO("Updatestories from id:" << l_idstart);

	BLL::Story *MyStory = new BLL::Story();
	sql::ResultSet* table = MyStory->SelectList(l_idstart, 0);
	if(!table)
	{
		if(MyStory)
		{
			delete MyStory;
			MyStory = NULL;
		}

		return m_ArrayStories;
	}

	while (table->next())
	{
		std::vector<std::string> l_story;

		l_story.push_back(std::to_string(table->getInt(1)));
		l_story.push_back(std::string(table->getString(2).c_str()));
		l_story.push_back(std::string(table->getString(3).c_str()));
		l_story.push_back(std::string(table->getString(4).c_str()));
		l_story.push_back(std::string(table->getString(5).c_str()));
		l_story.push_back(std::to_string(table->getInt(6)));

		m_ArrayStories.push_back(l_story);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyStory)
	{
		delete MyStory;
		MyStory = NULL;
	}

	return m_ArrayStories;

}//end Update Stories

std::vector<std::vector<std::string> > DBInterface::UpdateApps()
{
	auto it = m_ArrayApps.end() - 1;
	int l_idstart = std::atoi((*it)[0].c_str());
	std::cout << "UpdatesApps from id:" << l_idstart << std::endl;
	LOG_INFO("UpdateApps from id:" << l_idstart);

	BLL::App *MyApp = new BLL::App();
	sql::ResultSet* table = MyApp->SelectList(l_idstart);

	if(!table)
	{
		if(MyApp)
		{
			delete MyApp;
			MyApp = NULL;
		}

		return m_ArrayApps;
	}

	while (table->next())
	{
		std::vector<std::string> l_app;

		l_app.push_back(std::to_string(table->getInt(1)));
		l_app.push_back(std::string(table->getString(2).c_str()));
		l_app.push_back(std::string(table->getString(3).c_str()));
		l_app.push_back(std::string(table->getString(4).c_str()));

		m_ArrayApps.push_back(l_app);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyApp)
	{
		delete MyApp;
		MyApp = NULL;
	}

	return m_ArrayApps;

}//end Update Apps




std::vector<std::vector<std::string> > DBInterface::ReloadStories()
{
	std::cout << "reload stories" << std::endl;
	LOG_INFO("reload stories");

	if (m_ArrayStories.size() > 0)
	{
//		while(!m_ArrayStories.empty())
//		{
//			delete m_ArrayStories.front();
//			m_ArrayStories.erase(m_ArrayStories.begin());
//		}
		m_ArrayStories.clear();
	}

	BLL::Story *MyStory = new BLL::Story();
	sql::ResultSet* table = MyStory->SelectAll();
	if(!table)
	{
		if(MyStory)
		{
			delete MyStory;
			MyStory = NULL;
		}

		return m_ArrayStories;
	}

	while (table->next())
	{
		std::vector<std::string> l_story;

		l_story.push_back(std::to_string(table->getInt(1)));
		l_story.push_back(std::string(table->getString(2).c_str()));
		l_story.push_back(std::string(table->getString(3).c_str()));
		l_story.push_back(std::string(table->getString(4).c_str()));
		l_story.push_back(std::string(table->getString(5).c_str()));
		l_story.push_back(std::to_string(table->getInt(6)));

		m_ArrayStories.push_back(l_story);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyStory)
	{
		delete MyStory;
		MyStory = NULL;
	}

	return m_ArrayStories;

}//end reload stories

std::vector<std::vector<std::string> > DBInterface::ReloadApps()
{
	std::cout << "reload apps" << std::endl;
	LOG_INFO("reload apps");

	if (m_ArrayApps.size() > 0)
	{
//		while(!m_ArrayApps.empty())
//		{
//			delete m_ArrayApps.front();
//			m_ArrayApps.erase(m_ArrayApps.begin());
//		}
		m_ArrayApps.clear();
	}

	BLL::App *MyApp = new BLL::App();
	sql::ResultSet* table = MyApp->SelectAll();

	if(!table)
	{
		if(MyApp)
		{
			delete MyApp;
			MyApp = NULL;
		}

		return m_ArrayApps;
	}

	while (table->next())
	{
		std::vector<std::string> l_app;

		l_app.push_back(std::to_string(table->getInt(1)));
		l_app.push_back(std::string(table->getString(2).c_str()));
		l_app.push_back(std::string(table->getString(3).c_str()));
		l_app.push_back(std::string(table->getString(4).c_str()));

		m_ArrayApps.push_back(l_app);
	}

	if(table)
	{
		delete table;
		table = NULL;
	}

	if(MyApp)
	{
		delete MyApp;
		MyApp = NULL;
	}

	return m_ArrayApps;

}//end reload apps
