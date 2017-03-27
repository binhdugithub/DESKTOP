#include "datacommon.h"

DataCommon::DataCommon(QObject *parent) : QObject(parent)
{

}

void DataCommon::addCaseInfoToQueue(CaseInfo *caseInfo)
{
    if (!caseInfo)
        return;

    this->caseMutex.lock();
    this->queueCase.enqueue(caseInfo);
    this->caseMutex.unlock();
}

CaseInfo *DataCommon::getCaseInfoFromQueue()
{
    CaseInfo* caseInfo = NULL;

    this->caseMutex.lock();
    if (!this->queueCase.empty())
    {
        caseInfo = this->queueCase.dequeue();
    }
    this->caseMutex.unlock();

    return caseInfo;
}

void DataCommon::addCrimeInfoToQueue(CrimeInfo *crimeInfo)
{
    if (!crimeInfo)
        return;
    this->crimeMutex.lock();
    this->queueCrime.enqueue(crimeInfo);
    this->crimeMutex.unlock();
}

CrimeInfo *DataCommon::getCrimeInfoFromQueue()
{
    CrimeInfo* crimeInfo = NULL;
    this->crimeMutex.lock();
    if (!this->queueCrime.empty())
    {
        crimeInfo = this->queueCrime.dequeue();
    }
    this->crimeMutex.unlock();

    return crimeInfo;
}

void DataCommon::addRelationshipInfoToQueue(RelationshipInfo *relationshipInfo)
{
    if (!relationshipInfo)
        return;
    this->relationshipMutex.lock();
    this->queueRelationship.enqueue(relationshipInfo);
    this->relationshipMutex.unlock();
}

RelationshipInfo *DataCommon::getRelationshipInfoFromQueue()
{
    RelationshipInfo* relationshipInfo = NULL;
    this->relationshipMutex.lock();
    if (!this->queueRelationship.empty())
    {
        relationshipInfo = this->queueRelationship.dequeue();
    }
    this->relationshipMutex.unlock();

    return relationshipInfo;
}

void DataCommon::addCaseIdToList(long id)
{
    this->caseMutex.lock();
    this->listCaseId.append(id);
    this->caseMutex.unlock();
}

long DataCommon::takeCaseIdFromList()
{
    long output = -1;
    this->caseMutex.lock();
    if (this->listCaseId.count() > 0)
        output = this->listCaseId.takeFirst();
    this->caseMutex.unlock();

    return output;
}

void DataCommon::addCrimeIdToList(long id)
{
    this->crimeMutex.lock();
    this->listCrimeId.append(id);
    this->crimeMutex.unlock();
}

long DataCommon::takeCrimeIdFromList()
{
    long output = -1;
    this->crimeMutex.lock();
    if (this->listCrimeId.count() > 0)
        output = this->listCrimeId.takeFirst();
    this->crimeMutex.unlock();

    return output;
}
