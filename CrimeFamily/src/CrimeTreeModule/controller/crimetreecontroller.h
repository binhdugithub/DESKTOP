#ifndef CRIMETREECONTROLLER_H
#define CRIMETREECONTROLLER_H

#include <QObject>
#include <QFileDialog>
#include <QHashIterator>
#include <QTimer>
#include <QColorDialog>

#include "datacommon.h"

class CaseManagementView;
class CrimeTreeView;
class CrimeTreeForm;
class CrimeDetailView;
class RelationshipDetailView;

class CrimeTreeController : public QObject
{
    Q_OBJECT
public:
    explicit CrimeTreeController(QObject *parent = 0);
    void setDataCommon(DataCommon*  _dataCommon);
    void addCaseToView();

    CaseManagementView *caseManagementView();
    CrimeTreeView* crimeTreeView();
    CrimeDetailView* crimeDetailView();
    RelationshipDetailView* relationshipDetailView();

public slots:
    void handle_exit_application(bool);
    void handle_saveCaseInfo(long id, int mode);
    void handle_removeCaseInfo(long id);
    void handle_displayCase(long id);
    void handle_saveCrimeInfo(long id, int mode);
    void handle_removeCrimeInfo(long id);
    void handle_saveRelationshipInfo(long id, int mode);
    void handle_removeRelationshipInfo(long id)
;
private slots:
    void handle_buttonCaseDetail_clicked(bool);
    void handle_buttonCaseManagement_clicked(bool);
    void handle_buttonCrimeDetail_clicked(bool);
    void handle_buttonCrimeAccept_clicked(bool);
    void handle_buttonCrimeCancel_clicked(bool);
    void handle_buttonCrimeChooseAvatar_clicked(bool);
    void handle_buttonCaseUpdate_clicked(bool);
    void handle_buttonRelationshipDetail_clicked(bool);
    void handle_buttonRelationshipAccept_clicked(bool);
    void handle_buttonRelationshipCancel_clicked(bool);
    void handle_buttonChooseColor_clicked(bool);
    void handle_showMenuContext(QPoint pt);
    void handle_actEditCrime_triggered(bool);
    void handle_actDelCrime_triggered(bool);

signals:
    void display_waitting(bool value);
    void exit_application();
    void display_caseDetail(long id);
    void display_casemanagement();

private:
    CrimeTreeForm*      m_currentForm;
    CaseManagementView* m_caseManagementView;
    CrimeDetailView*    m_crimeDetailView;
    CrimeTreeView*      m_crimeTreeView;
    RelationshipDetailView *m_relationshipDetailView;
    DataCommon*         m_dataCommon;
    QPoint              m_pGlobal;
    QPointF             m_pScene;
};

#endif // CRIMETREECONTROLLER_H
