#ifndef DATAACCESS_H
#define DATAACCESS_H

// Qt includes
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QPen>

// Commons includes
#include "datacommon.h"

class DataAccess : public QObject
{
    Q_OBJECT
public:
    explicit DataAccess(QObject *parent = 0);
    bool setDBMSInfo(QString driverName,
                QString databaseName);
    bool testConnectToDBMS();

    // SELECT
    bool getListCaseInfo(DataCommon* _dataCommon);
    bool getListCrimeInfo(DataCommon* _dataCommon);
    bool getListRelationshipInfo(DataCommon* _dataCommon);

    // INSERT
    bool saveCaseInfo(CaseInfo* _caseInfo);
    bool saveCrimeInfo(CrimeInfo* _crimeInfo);
    bool saveRelationshipInfo(RelationshipInfo* _relationshipInfo);

    // DELETE
    bool delCaseInfo(long id);
    bool delCrimeInfo(long id);
    bool delRelationshipInfo(long id);
signals:
    void send_error(QString error);

private:
    QSqlDatabase		m_db;
    QString             m_driverName;
    QString             m_databaseName;
};

#endif // DATAACCESS_H
