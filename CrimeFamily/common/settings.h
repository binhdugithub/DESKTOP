#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QTextStream>

class Settings : public QObject
{
	Q_OBJECT
public:
	explicit Settings(QObject *parent = 0);
	bool loadSettings();
	bool saveSettings();

	// Database
	QString         dbms_driver_name;
	QString         dbms_database_name;
    int             dbms_retry_connect;
};

#endif // SETTINGS_H
