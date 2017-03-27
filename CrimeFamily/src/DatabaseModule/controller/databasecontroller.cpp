// DatabaseController includes
#include "databasecontroller.h"
#include "dataaccess.h"

DatabaseController::DatabaseController(QObject *parent) : QThread(parent)
{
    this->m_isStop		= false;
    this->m_dataAccess	= NULL;
}

DatabaseController::~DatabaseController()
{
    if (this->m_dataAccess != NULL)
    {
        delete this->m_dataAccess;
        this->m_dataAccess = NULL;
    }
}

void DatabaseController::setDataCommon(DataCommon *_dataCommon)
{
    this->m_dataCommon = _dataCommon;
}

void DatabaseController::startThread()
{
    this->m_muxtex.lock();
    this->m_isStop = false;
    this->start();
    this->m_muxtex.unlock();
}

void DatabaseController::stopThread()
{
    this->m_muxtex.lock();
    this->m_isStop = true;
    this->m_muxtex.unlock();
}

bool DatabaseController::createDatabaseAccess()
{
    if (this->m_dataAccess != NULL)
        return true;

    this->m_dataAccess = new DataAccess();
    connect(this->m_dataAccess, SIGNAL(send_error(QString)),
            this, SLOT(handle_message_error(QString)), Qt::DirectConnection);

    this->m_dataAccess->setDBMSInfo(g_settings.dbms_driver_name,
                                    g_settings.dbms_database_name);

    bool result = this->m_dataAccess->testConnectToDBMS();

    QString kq = result ? "ok" : "fail";
    QString sLog = QString("\n\tConnect to database "
                           + kq + ": "
                                  "\n\t- Driver name \t\t= %1"
                                  "\n\t- Database name \t= %2")
            .arg(g_settings.dbms_driver_name)
            .arg(g_settings.dbms_database_name);
    gLog(sLog.toStdString().c_str(), Info);

    return result;
}

bool DatabaseController::getListCaseInfo()
{
    return this->m_dataAccess->getListCaseInfo(this->m_dataCommon);
}

bool DatabaseController::getListCrimeInfo()
{
    return this->m_dataAccess->getListCrimeInfo(this->m_dataCommon);
}

bool DatabaseController::getListRelationshipInfo()
{
    return this->m_dataAccess->getListRelationshipInfo(this->m_dataCommon);
}

void DatabaseController::run()
{
    emit display_waitting(true);
    bool isGetData = true;
    isGetData &= this->createDatabaseAccess();
    isGetData &= this->getListCaseInfo();
    isGetData &= this->getListCrimeInfo();
    isGetData &= this->getListRelationshipInfo();
    emit display_waitting(false);

    emit getDataFinish(isGetData);

    if (isGetData)
    {
        while (!this->m_isStop)
        {
            CaseInfo* caseInfo = this->m_dataCommon->getCaseInfoFromQueue();

            if (caseInfo)
            {
                emit display_waitting(true);
                QString message;
                int mode = 1;
                bool result = this->m_dataAccess->saveCaseInfo(caseInfo);

                if (result)
                {
                    if (!this->m_dataCommon->hashCase.contains(caseInfo->id))
                    {
                        this->m_dataCommon->hashCase.insert(caseInfo->id, caseInfo);
                        message = QString::fromUtf8("Thêm mới thành công !");
                        mode = 0;
                    }
                    else
                    {
                        CaseInfo* case_Info = this->m_dataCommon->hashCase.value(caseInfo->id);
                        delete case_Info;
                        case_Info = NULL;
                        this->m_dataCommon->hashCase.insert(caseInfo->id, caseInfo);
                        message = QString::fromUtf8("Sửa dữ liệu thành công !");
                        mode = 1;
                    }
                }
                else
                {
                    message = QString::fromUtf8("Lỗi : Thêm mới không thành công !");
                }

                emit display_waitting(false);

                emit display_message(message);
                emit update_caseInfo(caseInfo->id, mode);
            }

            long id = this->m_dataCommon->takeCaseIdFromList();

            if (id != -1)
            {
                emit display_waitting(true);
                bool result = this->m_dataAccess->delCaseInfo(id);

                if (result)
                {
                    CaseInfo* case_Info = this->m_dataCommon->hashCase.take(id);
                    delete case_Info;
                    case_Info = NULL;

                    emit remove_caseInfo(id);
                }

                emit display_waitting(false);
            }

            CrimeInfo* crimeInfo = this->m_dataCommon->getCrimeInfoFromQueue();

            if (crimeInfo)
            {
                emit display_waitting(true);
                QString message;
                int mode = 1;
                bool result = this->m_dataAccess->saveCrimeInfo(crimeInfo);

                if (result)
                {
                    if (!this->m_dataCommon->hashCrime.contains(crimeInfo->id))
                    {
                        this->m_dataCommon->hashCrime.insert(crimeInfo->id, crimeInfo);
                        this->m_dataCommon->hashCase.value(crimeInfo->case_id)->hashCrime.insert(crimeInfo->id, crimeInfo);
                        message = QString::fromUtf8("Thêm mới thành công !");
                        mode = 0;
                    }
                    else
                    {
                        CrimeInfo* crime_Info = this->m_dataCommon->hashCrime.value(crimeInfo->id);
                        delete crime_Info;
                        crime_Info = NULL;
                        this->m_dataCommon->hashCrime.insert(crimeInfo->id, crimeInfo);

                        CrimeInfo* crime_Info1 = this->m_dataCommon->hashCase.value(crimeInfo->case_id)->hashCrime.value(crimeInfo->id);
                        delete crime_Info1;
                        crime_Info1 = NULL;
                        this->m_dataCommon->hashCase.value(crimeInfo->case_id)->hashCrime.insert(crimeInfo->id, crimeInfo);
                        message = QString::fromUtf8("Sửa dữ liệu thành công !");
                        mode = 1;
                    }
                }
                else
                {
                    message = QString::fromUtf8("Lỗi : Thêm mới không thành công !");
                }

                emit display_waitting(false);
                if (mode == 0)
                    emit display_message(message);
                emit update_crimeInfo(crimeInfo->id, mode);
            }

            long crime_id = this->m_dataCommon->takeCrimeIdFromList();

            if (crime_id != -1)
            {
                emit display_waitting(true);
                bool result = this->m_dataAccess->delCrimeInfo(crime_id);

                if (result)
                {
                    CrimeInfo* crime_Info = this->m_dataCommon->hashCrime.take(crime_id);
                    delete crime_Info;
                    crime_Info = NULL;

                    emit remove_crimeInfo(crime_id);
                }

                emit display_waitting(false);
            }

            RelationshipInfo* relationshipInfo = this->m_dataCommon->getRelationshipInfoFromQueue();

            if (relationshipInfo)
            {
                emit display_waitting(true);
                QString message;
                int mode = 1;
                bool result = this->m_dataAccess->saveRelationshipInfo(relationshipInfo);

                if (result)
                {
                    if (!this->m_dataCommon->hashRelationship.contains(relationshipInfo->id))
                    {
                        this->m_dataCommon->hashRelationship.insert(relationshipInfo->id, relationshipInfo);
                        this->m_dataCommon->hashCase.value(relationshipInfo->case_id)->hashRelationship.insert(relationshipInfo->id, relationshipInfo);
                        message = QString::fromUtf8("Thêm mới thành công !");
                        mode = 0;
                    }
                    else
                    {
                        RelationshipInfo* relationship_Info = this->m_dataCommon->hashRelationship.value(relationshipInfo->id);
                        if (relationship_Info != NULL)
                        {
                            delete relationship_Info;
                            relationship_Info = NULL;
                        }
                        this->m_dataCommon->hashRelationship.insert(relationshipInfo->id, relationshipInfo);

                        RelationshipInfo* relationship_Info1 = this->m_dataCommon->hashCase.value(relationshipInfo->case_id)->hashRelationship.value(relationshipInfo->id);
                        if (relationship_Info1 != NULL)
                        {
                            delete relationship_Info1;
                            relationship_Info1 = NULL;
                        }
                        this->m_dataCommon->hashCase.value(relationshipInfo->case_id)->hashRelationship.insert(relationshipInfo->id, relationshipInfo);
                        message = QString::fromUtf8("Sửa dữ liệu thành công !");
                        mode = 1;
                    }
                }
                else
                {
                    message = QString::fromUtf8("Lỗi : Thêm mới không thành công !");
                }

                emit display_waitting(false);
                if (mode == 0)
                    emit display_message(message);
                emit update_relationshipInfo(relationshipInfo->id, mode);
            }
            usleep(1000);
        }
    }
    else
    {
        this->m_isStop = true;
    }
}

void DatabaseController::handle_message_error(QString message)
{
    gLog("* Message error : " << message.toStdString().c_str(), Error);
}
