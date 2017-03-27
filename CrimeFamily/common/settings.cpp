#include "settings.h"
#include "log.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
    this->dbms_driver_name			= "QSQLITE";
    this->dbms_database_name		= "crime_tree.db";
}

bool Settings::loadSettings()
{
    // Get directory
    QString application_path = QDir::currentPath();
    QString setting_file_path = application_path + "/configs/config.conf";

    // Check file setting is exists or not
    QFile file_setting(setting_file_path);

    if (!file_setting.exists())
    {
        gLog("File config.conf is not found.Create new file config "<<setting_file_path.toStdString().c_str(), Warning);
        bool result = file_setting.open(QIODevice::WriteOnly);

        if (!result)
        {
         gLog("* Create new file config "<< setting_file_path.toStdString().c_str() <<" failed.Application exit !", Error);
         file_setting.close();
         return false;
        }
        file_setting.close();
    }

    // Load file config
    QSettings settings(setting_file_path, QSettings::IniFormat);

    settings.beginGroup("DBMS");
    this->dbms_driver_name = settings.value("DriverName", "QSQLITE").toString();
    this->dbms_database_name = settings.value("DatabaseName", "crime_tree.db").toString();
    settings.endGroup();

    this->dbms_database_name = application_path + "/database/" + this->dbms_database_name;
    return true;
}

bool Settings::saveSettings()
{
	// Get directory
	QString application_path = QDir::currentPath();
	QString setting_file_path = application_path + "/configs/config.conf";

	// Check file setting is exists or not
	QFile file_setting(setting_file_path);

	if (!file_setting.exists())
	{
	    gLog("File config.conf is not found.Create new file config "<<setting_file_path.toStdString().c_str(), Warning);
	    bool result = file_setting.open(QIODevice::WriteOnly);

	    if (!result)
	    {
		 gLog("* Create new file config "<< setting_file_path.toStdString().c_str() <<" failed.Application exit !", Error);
		 file_setting.close();
		 return false;
	    }
	    file_setting.close();
	}

    // Save file config
	QSettings settings(setting_file_path, QSettings::IniFormat);

	settings.beginGroup("DBMS");
	settings.setValue("DriverName", this->dbms_driver_name);
	settings.setValue("DatabaseName", this->dbms_database_name);
	settings.endGroup();
	return true;
}

