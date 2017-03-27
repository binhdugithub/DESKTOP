#ifndef CRIMETREEVIEW_H
#define CRIMETREEVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPainter>
#include "crimetreeform.h"
#include "datacommon.h"

class CrimeTreeView : public QWidget
{
    Q_OBJECT
public:
    explicit CrimeTreeView(QWidget *parent = 0);
    bool setupUi(CrimeTreeForm* crimeTreeForm);
    void paintEvent(QPaintEvent* event);

private:
    QGridLayout*        m_layoutCentral;
};

#endif // CRIMETREEVIEW_H
