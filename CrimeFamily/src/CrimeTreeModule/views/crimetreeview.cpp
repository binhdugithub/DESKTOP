#include "crimetreeview.h"

CrimeTreeView::CrimeTreeView(QWidget *parent) : QWidget(parent)
{

}

bool CrimeTreeView::setupUi(CrimeTreeForm *crimeTreeForm)
{
    this->m_layoutCentral       = new QGridLayout();

    this->m_layoutCentral->addWidget(crimeTreeForm->graphicsView, 0, 0, 8, 1);
//    this->m_layoutCentral->addWidget(crimeTreeForm->chkShowRelationship, 0, 1, 1, 1);
//    this->m_layoutCentral->addWidget(crimeTreeForm->chkRelationshipIsLine, 1, 1, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->btnAddNewCrime, 1, 1, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->btnAddNewRelationship, 2, 1, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->btnUpdateGraphics, 3, 1, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->btnBackToCaseView, 6, 1, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->btnExitOnDetail, 7, 1, 1, 1);
    this->setLayout(this->m_layoutCentral);
    this->setProperty("bg-dark", true);
    return true;
}

void CrimeTreeView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
}
