#ifndef DATACOMMON_H
#define DATACOMMON_H

#include <QObject>
#include <QMap>
#include <QMutex>
#include <QDateTime>
#include <QPoint>
#include <QQueue>
#include <QHash>
#include <QPen>

class CrimeInfo;
class RelationshipInfo;

class CaseInfo : public QObject
{
    Q_OBJECT
public:
    long    id;
    QString name;
    QDate   timebegin;
    QDate   timeend;
    QString description;
    QString status;
    QHash<qint64, CrimeInfo*> hashCrime;
    QHash<qint64, RelationshipInfo*> hashRelationship;
};

class CrimeInfo : public QObject
{
    Q_OBJECT
public:
    long    id;
    QString name;
    QString avatar;
    QString profile;
    QString description;
    bool    visible;
    QPoint  pos;
    long    case_id;
};

class RelationshipInfo : public QObject
{
    Q_OBJECT
public:
    long    id;
    long    crime_1;
    long    crime_2;
    QString name;
    QPen    pen;
    bool    visible;
    long    case_id;
};

class DataCommon : public QObject
{
    Q_OBJECT
public:
    explicit DataCommon(QObject *parent = 0);

    // Add data to queue
    void addCaseInfoToQueue(CaseInfo* caseInfo);
    CaseInfo* getCaseInfoFromQueue();
    void addCrimeInfoToQueue(CrimeInfo* crimeInfo);
    CrimeInfo* getCrimeInfoFromQueue();
    void addRelationshipInfoToQueue(RelationshipInfo* relationshipInfo);
    RelationshipInfo* getRelationshipInfoFromQueue();

    // Add data to list
    void addCaseIdToList(long id);
    long takeCaseIdFromList();
    void addCrimeIdToList(long id);
    long takeCrimeIdFromList();

    QMap<qint64, CaseInfo*>                 hashCase;
    QMap<qint64, CrimeInfo*>                hashCrime;
    QMap<qint64, RelationshipInfo*>         hashRelationship;
    QQueue<CaseInfo*>                       queueCase;
    QQueue<CrimeInfo*>                      queueCrime;
    QQueue<RelationshipInfo*>               queueRelationship;
    QList<long>                             listCaseId;
    QList<long>                             listCrimeId;

    QMutex                                  caseMutex;
    QMutex                                  crimeMutex;
    QMutex                                  relationshipMutex;
};

#endif // DATACOMMON_H
