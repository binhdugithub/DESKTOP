#ifndef CASEMANAGEMENTVIEW_H
#define CASEMANAGEMENTVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPainter>

#include "crimetreeform.h"
#include "flowlayout.h"

class CaseManagementView : public QWidget
{
    Q_OBJECT
public:
    explicit CaseManagementView(QWidget *parent = 0);
    bool setupUi(CrimeTreeForm* crimeTreeForm);
    void paintEvent(QPaintEvent* event);
private:
    QGridLayout*        m_layoutCentral;
    FlowLayout*         m_layoutButton;
    QWidget*            m_widgetButtonGroup;
};

#endif // CASEMANAGEMENTVIEW_H
