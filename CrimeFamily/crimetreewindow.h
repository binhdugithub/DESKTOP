#ifndef CRIMETREEWINDOW_H
#define CRIMETREEWINDOW_H

#include <QMainWindow>
#include <DatabaseModule>
#include <CrimeTreeModule>
#include <QApplication>
#include <QMessageBox>

#include "datacommon.h"
#include "slidingstackedwidget.h"
#include "waitingspinnerwidget.h"

class CrimeTreeWindow : public QMainWindow
{
    Q_OBJECT

public:
    CrimeTreeWindow(QWidget *parent = 0);
    ~CrimeTreeWindow();

    bool setupUi();
    bool setupConnector();

public slots:
    void handle_display_message(QString message);
    void handle_display_waiting_form(bool value);
    void handle_application_quit();
    void handle_getDataFromDatabase_success(bool value);
    void handle_displayCaseDetail(long id);
    void handle_displayCaseManagement();

private:
    DatabaseController*     m_databaseController;
    CrimeTreeController*    m_crimeTreeController;
    DataCommon*             m_dataCommon;

    SlidingStackedWidget*   m_widgetCentral;
    WaitingSpinnerWidget*   m_widgetWaiting;
};

#endif // CRIMETREEWINDOW_H
