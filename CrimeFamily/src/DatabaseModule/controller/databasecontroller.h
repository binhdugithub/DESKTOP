#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

// Qt includes
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QHash>
#include <QDateTime>

// Commons includes
#include "log.h"
#include "global.h"
#include "datacommon.h"

class DataAccess;

class DatabaseController : public QThread
{
	Q_OBJECT
public:
	explicit DatabaseController(QObject *parent = 0);
	~DatabaseController();
    void setDataCommon(DataCommon* _dataCommon);

	void startThread();
	void stopThread();
	bool createDatabaseAccess();

    bool getListCaseInfo();
    bool getListCrimeInfo();
    bool getListRelationshipInfo();

protected:
	void run();

public slots:
	void handle_message_error(QString message);

signals:
    void getDataFinish(bool value);
    void update_caseInfo(long id, int mode);
    void remove_caseInfo(long id);
    void update_crimeInfo(long id, int mode);
    void remove_crimeInfo(long id);
    void update_relationshipInfo(long id, int mode);
    void remove_relationshipInfo(long id);
    void display_waitting(bool value);
    void display_message(QString message);
    void display_error(QString message);

private:
	bool					m_isStop;
    QMutex                  m_muxtex;

    DataAccess*             m_dataAccess;
    DataCommon*             m_dataCommon;
};

#endif // DATABASECONTROLLER_H
