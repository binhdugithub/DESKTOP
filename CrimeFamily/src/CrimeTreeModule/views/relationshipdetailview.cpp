#include "relationshipdetailview.h"

RelationshipDetailView::RelationshipDetailView(QWidget *parent) : QDialog(parent)
{

}

bool RelationshipDetailView::setupUi(CrimeTreeForm *crimeTreeForm)
{
    this->m_layoutCentral       = new QGridLayout();
    this->m_layoutCentral->addWidget(crimeTreeForm->labelRelationshipName, 0, 0, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->txtRelationshipName, 0, 1, 1, 3);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelCrime1Id, 1, 0, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->cboCrime1Id, 1, 1, 1, 3);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelCrime2Id, 2, 0, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->cboCrime2Id, 2, 1, 1, 3);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelLineColor, 3, 0, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelPictureColor, 3, 1, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->btnChooseColor, 3, 3, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelLineType, 4, 0, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->cboLineType, 4, 1, 1, 3);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelLineSize, 5, 0, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->spnLineSize, 5, 1, 1, 3);
    this->m_layoutCentral->addWidget(crimeTreeForm->btnAcceptRelationship, 6, 2, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->btnCancelRelationship, 6, 3, 1, 1);

    this->setLayout(this->m_layoutCentral);
    return true;
}
