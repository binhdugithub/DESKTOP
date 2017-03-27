// DatabaseController includes
#include "dataaccess.h"

// Common includes
#include "log.h"

//!
//! \brief DataAccess::DataAccess
//! \param parent
//!
DataAccess::DataAccess(QObject *parent) : QObject(parent)
{
    this->m_driverName      = "";
    this->m_databaseName	= "";
}

//!
//! \brief DataAccess::setDBMSInfo
//! \param driverName
//! \param hostName
//! \param databaseName
//! \param userName
//! \param password
//! \return
//!
bool DataAccess::setDBMSInfo(QString driverName, QString databaseName)
{
    this->m_driverName          = driverName;
    this->m_databaseName        = databaseName;

    this->m_db = QSqlDatabase::addDatabase(driverName);
    this->m_db.setDatabaseName(databaseName);

    if (this->m_db.open())
        return true;
    else
        return false;
}

//!
//! \brief DataAccess::testConnectToDBMS
//! \return
//!
bool DataAccess::testConnectToDBMS()
{
    bool result = this->m_db.open();
    this->m_db.close();

    return result;
}

bool DataAccess::getListCaseInfo(DataCommon *_dataCommon)
{
    if (_dataCommon == NULL)
        return false;
    if (_dataCommon->hashCase.size() != 0)
        return true;

    if (this->m_db.open())
    {
        QSqlQuery query("SELECT * FROM 'Case' ORDER BY 'id' DESC");

        if (query.exec())
        {
            while (query.next())
            {
                CaseInfo* case_info = new CaseInfo();
                case_info->id = query.value("id").toLongLong();
                case_info->name = query.value("name").toString();
                case_info->timebegin = QDate::fromString(query.value("timebegin").toString(), "dd/MM/yyyy");
                case_info->timeend = QDate::fromString(query.value("timebegin").toString(), "dd/MM/yyyy");
                case_info->description = query.value("description").toString();
                case_info->status = query.value("status").toString();

                _dataCommon->hashCase.insert(case_info->id, case_info);
            }
        }
        else
        {
            gLog("Get list case error : " + query.lastError().text(), Error);
        }
        this->m_db.close();
        return true;
    }
    return false;
}

bool DataAccess::getListCrimeInfo(DataCommon *_dataCommon)
{
    if (_dataCommon == NULL)
        return false;
    if (_dataCommon->hashCrime.size() != 0)
        return true;

    if (this->m_db.open())
    {
        QSqlQuery query("SELECT * FROM 'Crime'");

        if (query.exec())
        {
            while (query.next())
            {
                CrimeInfo* crimeInfo = new CrimeInfo();
                crimeInfo->id = query.value("id").toLongLong();
                crimeInfo->case_id = query.value("case_id").toLongLong();
                crimeInfo->name = query.value("name").toString();
                crimeInfo->description = query.value("description").toString();
                crimeInfo->avatar = query.value("avatar").toString();
                crimeInfo->profile = query.value("profile").toString();
                crimeInfo->visible = query.value("visible").toInt() == 0 ? false : true;
                crimeInfo->pos.setX(query.value("pos_x").toInt());
                crimeInfo->pos.setY(query.value("pos_y").toInt());
                _dataCommon->hashCrime.insert(crimeInfo->id, crimeInfo);

                CaseInfo* caseInfo = _dataCommon->hashCase.value(crimeInfo->case_id);
                caseInfo->hashCrime.insert(crimeInfo->id, crimeInfo);
            }
        }
        else
        {
            gLog("Get list crime error : " + query.lastError().text(), Error);
        }
        this->m_db.close();
        return true;
    }
    return false;
}

bool DataAccess::getListRelationshipInfo(DataCommon *_dataCommon)
{
    if (_dataCommon == NULL)
        return false;
    if (_dataCommon->hashRelationship.size() != 0)
        return true;

    if (this->m_db.open())
    {
        QSqlQuery query("SELECT * FROM 'Relationship'");

        if (query.exec())
        {
            while (query.next())
            {
                RelationshipInfo* relationshipInfo = new RelationshipInfo();
                relationshipInfo->id = query.value("id").toLongLong();
                relationshipInfo->name = query.value("name").toString();
                relationshipInfo->crime_1 = query.value("crime1_id").toInt();
                relationshipInfo->crime_2 = query.value("crime2_id").toInt();
                relationshipInfo->visible = query.value("visible").toInt() == 0 ? false : true;
                relationshipInfo->pen = QPen(QColor(query.value("line_color").toString()),
                                             query.value("line_size").toInt(),
                                             static_cast<Qt::PenStyle>(query.value("line_type").toInt()));

                relationshipInfo->case_id = query.value("case_id").toLongLong();
                _dataCommon->hashRelationship.insert(relationshipInfo->id, relationshipInfo);

                CaseInfo* caseInfo = _dataCommon->hashCase.value(relationshipInfo->case_id);
                caseInfo->hashRelationship.insert(relationshipInfo->id, relationshipInfo);
            }
        }
        else
        {
            gLog("Get list relationship error : " + query.lastError().text(), Error);
        }
        this->m_db.close();
        return true;
    }
    return false;
}

bool DataAccess::saveCaseInfo(CaseInfo* _caseInfo)
{
    if (_caseInfo == NULL)
        return false;

    if (this->m_db.open())
    {
        if (_caseInfo->id == -1)
        {
            QSqlQuery query;
            query.prepare("INSERT INTO 'Case'(name, timebegin, timeend, description, status) VALUES(:name, :timebegin, :timeend, :description, :status)");
            query.bindValue(":name", _caseInfo->name);
            query.bindValue(":timebegin", _caseInfo->timebegin.toString("dd/MM/yyyy"));
            query.bindValue(":timeend", _caseInfo->timeend.toString("dd/MM/yyyy"));
            query.bindValue(":description", _caseInfo->description);
            query.bindValue(":status", _caseInfo->status);

            if (!query.exec())
            {
                gLog("Insert case info error  : " + query.lastError().text(), Error);
            }

            _caseInfo->id = query.lastInsertId().toLongLong();
        }
        else
        {
            QSqlQuery query;
            query.prepare("UPDATE 'Case' SET name =:name, timebegin =:timebegin, timeend =:timeend, description =:description, status =:status WHERE id = " + QString::number(_caseInfo->id));
            query.bindValue(":name", _caseInfo->name);
            query.bindValue(":timebegin", _caseInfo->timebegin.toString("dd/MM/yyyy"));
            query.bindValue(":timeend", _caseInfo->timeend.toString("dd/MM/yyyy"));
            query.bindValue(":description", _caseInfo->description);
            query.bindValue(":status", _caseInfo->status);

            if (!query.exec())
            {
                gLog("Update case info error  : " + query.lastError().text(), Error);
            }
        }
        this->m_db.close();
        return true;
    }
    return false;
}

bool DataAccess::saveCrimeInfo(CrimeInfo *_crimeInfo)
{
    if (_crimeInfo == NULL)
        return false;

    if (this->m_db.open())
    {
        if (_crimeInfo->id == -1)
        {
            QSqlQuery query;
            query.prepare("INSERT INTO 'Crime'(name, avatar, profile, description, visible, pos_x, pos_y, case_id) VALUES(:name, :avatar, :profile, :description, :visible, :pos_x, :pos_y, :case_id)");
            query.bindValue(":name", _crimeInfo->name);
            query.bindValue(":avatar", _crimeInfo->avatar);
            query.bindValue(":profile", _crimeInfo->profile);
            query.bindValue(":description", _crimeInfo->description);
            query.bindValue(":visible", _crimeInfo->visible);
            query.bindValue(":pos_x", _crimeInfo->pos.x());
            query.bindValue(":pos_y", _crimeInfo->pos.y());
            query.bindValue(":case_id", _crimeInfo->case_id);

            if (!query.exec())
            {
                gLog("Insert crime info error  : " + query.lastError().text(), Error);
            }

            _crimeInfo->id = query.lastInsertId().toLongLong();
        }
        else
        {
            QSqlQuery query;
            query.prepare("UPDATE 'Crime' SET name =:name, avatar =:avatar, profile =:profile, description =:description, visible =:visible, pos_x =:pos_x,"
                          " pos_y =:pos_y, case_id = :case_id"
                          " WHERE id = " + QString::number(_crimeInfo->id));
            query.bindValue(":name", _crimeInfo->name);
            query.bindValue(":avatar", _crimeInfo->avatar);
            query.bindValue(":profile", _crimeInfo->profile);
            query.bindValue(":description", _crimeInfo->description);
            query.bindValue(":visible", _crimeInfo->visible);
            query.bindValue(":pos_x", _crimeInfo->pos.x());
            query.bindValue(":pos_y", _crimeInfo->pos.y());
            query.bindValue(":case_id", _crimeInfo->case_id);

            if (!query.exec())
            {
                gLog("Update crime info error  : " + query.lastError().text(), Error);
            }
        }
        this->m_db.close();
        return true;
    }
    return false;
}

bool DataAccess::saveRelationshipInfo(RelationshipInfo *_relationshipInfo)
{
    if (_relationshipInfo == NULL)
        return false;

    if (this->m_db.open())
    {
        if (_relationshipInfo->id == -1)
        {
            QSqlQuery query;
            query.prepare("INSERT INTO 'Relationship'(name, crime1_id, crime2_id, line_color, line_type, line_size, visible, case_id)"
                          " VALUES(:name, :crime1_id, :crime2_id, :line_color, :line_type, :line_size, :visible, :case_id)");
            query.bindValue(":name", _relationshipInfo->name);
            query.bindValue(":crime1_id", _relationshipInfo->crime_1);
            query.bindValue(":crime2_id", _relationshipInfo->crime_2);
            query.bindValue(":line_color", _relationshipInfo->pen.color().name());
            query.bindValue(":line_type", (int)_relationshipInfo->pen.style());
            query.bindValue(":line_size", _relationshipInfo->pen.width());
            query.bindValue(":visible", _relationshipInfo->visible);
            query.bindValue(":case_id", _relationshipInfo->case_id);

            if (!query.exec())
            {
                gLog("Insert relationship info error  : " + query.lastError().text(), Error);
            }

            _relationshipInfo->id = query.lastInsertId().toLongLong();
        }
        else
        {
            QSqlQuery query;
            query.prepare("UPDATE 'Relationship' SET name =:name, crime1_id =:crime1_id, crime2_id =:crime2_id, line_color =:line_color, visible =:visible, line_type =:line_type,"
                          " visible =:visible, case_id = :case_id"
                          " WHERE id = " + QString::number(_relationshipInfo->id));
            query.bindValue(":name", _relationshipInfo->name);
            query.bindValue(":crime1_id", _relationshipInfo->crime_1);
            query.bindValue(":crime2_id", _relationshipInfo->crime_2);
            query.bindValue(":line_color", _relationshipInfo->pen.color().name());
            query.bindValue(":line_type", (int)_relationshipInfo->pen.style());
            query.bindValue(":line_size", _relationshipInfo->pen.width());
            query.bindValue(":visible", _relationshipInfo->visible);
            query.bindValue(":case_id", _relationshipInfo->case_id);

            if (!query.exec())
            {
                gLog("Update relationship info error  : " + query.lastError().text(), Error);
            }
        }
        this->m_db.close();
        return true;
    }
    return false;
}

bool DataAccess::delCaseInfo(long id)
{
    if (this->m_db.open())
    {
        QSqlQuery query;
        query.prepare("DELETE FROM 'Case' WHERE id = " + QString::number(id));

        if (!query.exec())
        {
            gLog("Delete case info error  : " + query.lastError().text(), Error);
        }

        query.prepare("DELETE FROM 'Crime' WHERE case_id = " + QString::number(id));
        if (!query.exec())
        {
            gLog("Delete crime info error  : " + query.lastError().text(), Error);
        }

        query.prepare("DELETE FROM 'Relationship' WHERE case_id = " + QString::number(id));
        if (!query.exec())
        {
            gLog("Delete relationship info error  : " + query.lastError().text(), Error);
        }
        this->m_db.close();
        return true;
    }
    return false;
}

bool DataAccess::delCrimeInfo(long id)
{
    if (this->m_db.open())
    {
        QSqlQuery query;

        query.prepare("DELETE FROM 'Crime' WHERE id = " + QString::number(id));
        if (!query.exec())
        {
            gLog("Delete crime info error  : " + query.lastError().text(), Error);
        }

        query.prepare("DELETE FROM 'Relationship' WHERE crime1_id = " + QString::number(id) + " OR crime2_id = " + QString::number(id));
        if (!query.exec())
        {
            gLog("Delete relationship info error  : " + query.lastError().text(), Error);
        }
        this->m_db.close();
        return true;
    }
    return false;
}

bool DataAccess::delRelationshipInfo(long id)
{
    if (this->m_db.open())
    {
        QSqlQuery query;

        query.prepare("DELETE FROM 'Relationship' WHERE id = " + QString::number(id));
        if (!query.exec())
        {
            gLog("Delete relationship info error  : " + query.lastError().text(), Error);
        }
        this->m_db.close();
        return true;
    }
    return false;
}
