#include "crimedetailview.h"

CrimeDetailView::CrimeDetailView(QWidget *parent) : QDialog(parent)
{

}

bool CrimeDetailView::setupUi(CrimeTreeForm *crimeTreeForm)
{
    this->m_layoutCentral       = new QGridLayout();
    this->m_layoutCentral->addWidget(crimeTreeForm->labelCrimeName, 0, 0, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->txtCrimeName, 0, 1, 1, 3);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelCrimeAvatar, 1, 0, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelCrimePicture, 1, 1, 1, 3);
    this->m_layoutCentral->addWidget(crimeTreeForm->btnChoosePicture, 2, 3, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelCrimeProfile, 3, 0, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->txtCrimeProfile, 3, 1, 1, 3);
    this->m_layoutCentral->addWidget(crimeTreeForm->labelCrimeDescription, 4, 0, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->txtCrimeDescription, 4, 1, 1, 3);
    this->m_layoutCentral->addWidget(crimeTreeForm->btnAcceptCrime, 5, 2, 1, 1);
    this->m_layoutCentral->addWidget(crimeTreeForm->btnCancelCrime, 5, 3, 1, 1);

    this->setLayout(this->m_layoutCentral);
    return true;
}
