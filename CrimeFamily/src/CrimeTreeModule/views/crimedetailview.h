#ifndef CRIMEDETAILVIEW_H
#define CRIMEDETAILVIEW_H

#include <QDialog>
#include <QGridLayout>
#include "crimetreeform.h"

class CrimeDetailView : public QDialog
{
    Q_OBJECT
public:
    explicit CrimeDetailView(QWidget *parent = 0);
    bool setupUi(CrimeTreeForm* crimeTreeForm);

private:
    QGridLayout*    m_layoutCentral;
};

#endif // CRIMEDETAILVIEW_H
