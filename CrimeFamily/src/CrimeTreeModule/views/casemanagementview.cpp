#include "casemanagementview.h"

CaseManagementView::CaseManagementView(QWidget *parent) : QWidget(parent)
{

}

bool CaseManagementView::setupUi(CrimeTreeForm *crimeTreeForm)
{
    this->m_layoutCentral       = new QGridLayout();
    this->m_layoutButton        = new FlowLayout();
    this->m_widgetButtonGroup   = new QWidget();

    this->m_layoutButton->addWidget(crimeTreeForm->btnAddNewCase);
    this->m_layoutButton->addWidget(crimeTreeForm->btnEditCase);
    this->m_layoutButton->addWidget(crimeTreeForm->btnDelCase);
    this->m_layoutButton->addWidget(crimeTreeForm->btnCaseDetail);
    this->m_layoutButton->addWidget(crimeTreeForm->btnExit);
    this->m_layoutButton->addWidget(crimeTreeForm->btnAcceptCase);
    this->m_layoutButton->addWidget(crimeTreeForm->btnCancelCase);
    this->m_widgetButtonGroup->setLayout(this->m_layoutButton);

    this->m_layoutCentral->addWidget(crimeTreeForm->tableCase, 0, 0, 10, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelCaseName, 0, 1, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->txtCaseName, 0, 2, 1, 2);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelTimeBegin, 1, 1, 1, 1);
//    this->m_layoutCentral->addWidget(crimeTreeForm->txtCaseTimeBegin, 1, 2, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->txtCaseDateBegin, 1, 2, 1, 2);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelTimeEnd, 2, 1, 1, 1);
//    this->m_layoutCentral->addWidget(crimeTreeForm->txtCaseTimeEnd, 2, 2, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->txtCaseDateEnd, 2, 2, 1, 2);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelCaseDescription, 3, 1, 1, 2);
    this->m_layoutCentral->addWidget(crimeTreeForm->txtCaseDescription, 4, 1, 3, 3);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelCaseStatus, 8, 1, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->cboCasetatus, 8, 2, 1, 3);
    this->m_layoutCentral->addWidget(this->m_widgetButtonGroup, 9, 1, 1, 3);
    this->m_layoutCentral->setSpacing(5);
    this->m_layoutCentral->setRowStretch(4, 10);
    this->m_layoutCentral->setColumnStretch(0, 5);
    this->m_layoutCentral->setColumnStretch(3, 5);
    this->setLayout(this->m_layoutCentral);

    this->setProperty("bg-dark", true);

    return true;
}

void CaseManagementView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
}
