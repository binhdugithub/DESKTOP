#ifndef RELATIONSHIPDETAILVIEW_H
#define RELATIONSHIPDETAILVIEW_H

#include <QDialog>
#include <QGridLayout>
#include "crimetreeform.h"

class RelationshipDetailView : public QDialog
{
    Q_OBJECT
public:
    explicit RelationshipDetailView(QWidget *parent = 0);
    bool setupUi(CrimeTreeForm* crimeTreeForm);

private:
    QGridLayout*    m_layoutCentral;
};

#endif // RELATIONSHIPDETAILVIEW_H
