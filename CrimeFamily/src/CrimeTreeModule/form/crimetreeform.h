#ifndef CRIMETREEFORM_H
#define CRIMETREEFORM_H

#include <QObject>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QStyledItemDelegate>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QHash>
#include <QMenu>
#include <QAction>
#include <QSpinBox>

#include "datacommon.h"
#include "treegraphicsview.h"
#include "crimegraphicsitem.h"
#include "relationshipgraphicsitem.h"

class CrimeTreeForm : public QObject
{
    Q_OBJECT
public:
    explicit CrimeTreeForm(QObject *parent = 0);
    void lockControlOnCaseView(bool value);
    void showControlOnCaseView(bool value);

    void addCaseToView(DataCommon* _dataCommon);
    void addCaseInfoToView(CaseInfo* _caseInfo);
    void updateCaseInfoOnView(CaseInfo* _caseInfo);
    void removeCaseInfoOnView(long id);
    void setCaseToView(long id);

    DataCommon*         m_dataCommon;

    // CaseManagementView
    QTableWidget*       tableCase;
    QLabel*             labelCaseName;
    QLabel*             labelTimeBegin;
    QLabel*             labelTimeEnd;
    QLabel*             labelCaseDescription;
    QLabel*             labelCaseStatus;
    QLineEdit*          txtCaseId;
    QLineEdit*          txtCaseName;
    QTimeEdit*          txtCaseTimeBegin;
    QTimeEdit*          txtCaseTimeEnd;
    QDateEdit*          txtCaseDateBegin;
    QDateEdit*          txtCaseDateEnd;
    QPlainTextEdit*     txtCaseDescription;
    QComboBox*          cboCasetatus;
    QPushButton*        btnAddNewCase;
    QPushButton*        btnEditCase;
    QPushButton*        btnDelCase;
    QPushButton*        btnAcceptCase;
    QPushButton*        btnCancelCase;
    QPushButton*        btnCaseDetail;
    QPushButton*        btnExit;

    // CrimeTreeView
    TreeGraphicsView*   graphicsView;
    QGraphicsScene*     graphicsScene;
    QHash<quint64, CrimeGraphicsItem*> hashGraphicsItem;
    QHash<quint64, RelationshipGraphicsItem*> hashRelationshipItem;
    QPushButton*        btnExitOnDetail;
    QPushButton*        btnAddNewCrime;
    QPushButton*        btnAddNewRelationship;
    QPushButton*        btnBackToCaseView;
    QPushButton*        btnUpdateGraphics;
    QCheckBox*          chkShowRelationship;
    QCheckBox*          chkRelationshipIsLine;
    QMenu*              menuContext;
    QAction*            actEditCrime;
    QAction*            actDelCrime;
    QAction*            actEditRelationship;
    QAction*            actDelRelationship;

    // CrimeDetailView
    QLabel*             labelCrimeName;
    QLabel*             labelCrimeAvatar;
    QLabel*             labelCrimePicture;
    QLabel*             labelCrimeProfile;
    QLabel*             labelCrimeDescription;
    QLineEdit*          txtCrimeId;
    QLineEdit*          txtCrimeName;
    QLineEdit*          txtCrimeAvatar;
    QPlainTextEdit*     txtCrimeProfile;
    QPlainTextEdit*     txtCrimeDescription;
    QPushButton*        btnAcceptCrime;
    QPushButton*        btnCancelCrime;
    QPushButton*        btnChoosePicture;

    // RelationshipDetailView
    QLabel*             labelCrime1Id;
    QLabel*             labelCrime2Id;
    QLabel*             labelRelationshipName;
    QLabel*             labelLineColor;
    QLabel*             labelLineType;
    QLabel*             labelLineSize;
    QLabel*             labelPictureColor;
    QComboBox*          cboCrime1Id;
    QComboBox*          cboCrime2Id;
    QComboBox*          cboLineType;
    QLineEdit*          txtRelationshipName;
    QLineEdit*          txtRelationshipId;
    QLineEdit*          txtLineColor;
    QSpinBox*           spnLineSize;
    QPushButton*        btnAcceptRelationship;
    QPushButton*        btnCancelRelationship;
    QPushButton*        btnChooseColor;

private slots:
    void handle_btnAddNewCase_clicked(bool);
    void handle_btnEditCase_clicked(bool);
    void handle_btnDelCase_clicked(bool);
    void handle_btnAcceptCase_clicked(bool);
    void handle_btnCancelCase_clicked(bool);
    void handle_tableCase_itemSelectionChanged();
};

#endif // CRIMETREEFORM_H
