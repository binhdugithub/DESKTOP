#include "crimetreewindow.h"

CrimeTreeWindow::CrimeTreeWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setupUi();
    this->setupConnector();

    // Start thread and get data from database
    this->m_databaseController->startThread();
}

CrimeTreeWindow::~CrimeTreeWindow()
{
    if (this->m_databaseController != NULL)
    {
        this->m_databaseController->quit();
        if (this->m_databaseController->wait(3000))
        {
            this->m_databaseController->terminate();
            this->m_databaseController->wait();
        }
    }
}

bool CrimeTreeWindow::setupUi()
{
    this->setWindowTitle(QString::fromUtf8("Biểu đồ cây tội phạm - v1.0"));
    this->setWindowIcon(QIcon("://images/icon.png"));
    this->setMinimumSize(800, 600);

    // Create widget
    this->m_widgetCentral           = new SlidingStackedWidget();
    this->m_widgetWaiting           = new WaitingSpinnerWidget(Qt::ApplicationModal, this, true, true);

    // Create controller and data common
    this->m_databaseController      = new DatabaseController();
    this->m_crimeTreeController     = new CrimeTreeController();
    this->m_dataCommon              = new DataCommon();

    // Create waiting spinner
    this->m_widgetWaiting->setRoundness(100.0);
    this->m_widgetWaiting->setMinimumTrailOpacity(15.0);
    this->m_widgetWaiting->setTrailFadePercentage(70.0);
    this->m_widgetWaiting->setNumberOfLines(12);
    this->m_widgetWaiting->setLineLength(20);
    this->m_widgetWaiting->setLineWidth(5);
    this->m_widgetWaiting->setInnerRadius(10);
    this->m_widgetWaiting->setRevolutionsPerSecond(1);
    this->m_widgetWaiting->setColor(QColor(39, 169, 224));

    // Set central widget
    this->setCentralWidget(this->m_widgetCentral);
    this->m_widgetCentral->setAnimation(QEasingCurve::Linear);
    this->m_widgetCentral->addWidget(this->m_crimeTreeController->caseManagementView());
    this->m_widgetCentral->addWidget(this->m_crimeTreeController->crimeTreeView());

    // Set data common
    this->m_databaseController->setDataCommon(m_dataCommon);
    this->m_crimeTreeController->setDataCommon(m_dataCommon);

    return true;
}

bool CrimeTreeWindow::setupConnector()
{
    connect(this->m_crimeTreeController, SIGNAL(display_waitting(bool)),
                this, SLOT(handle_display_waiting_form(bool)));
    connect(this->m_crimeTreeController, SIGNAL(exit_application()),
                this, SLOT(handle_application_quit()));
    connect(this->m_crimeTreeController, SIGNAL(display_caseDetail(long)),
                this, SLOT(handle_displayCaseDetail(long)));
    connect(this->m_crimeTreeController, SIGNAL(display_casemanagement()),
                this, SLOT(handle_displayCaseManagement()));

    connect(this->m_databaseController, SIGNAL(display_waitting(bool)),
                this, SLOT(handle_display_waiting_form(bool)));
    connect(this->m_databaseController, SIGNAL(getDataFinish(bool)),
                this, SLOT(handle_getDataFromDatabase_success(bool)));
    connect(this->m_databaseController, SIGNAL(display_message(QString)),
                this, SLOT(handle_display_message(QString)));

    connect(this->m_databaseController, SIGNAL(update_caseInfo(long,int)),
                this->m_crimeTreeController, SLOT(handle_saveCaseInfo(long,int)));
    connect(this->m_databaseController, SIGNAL(remove_caseInfo(long)),
                this->m_crimeTreeController, SLOT(handle_removeCaseInfo(long)));
    connect(this->m_databaseController, SIGNAL(update_crimeInfo(long,int)),
                this->m_crimeTreeController, SLOT(handle_saveCrimeInfo(long,int)));
    connect(this->m_databaseController, SIGNAL(remove_crimeInfo(long)),
                this->m_crimeTreeController, SLOT(handle_removeCrimeInfo(long)));
    connect(this->m_databaseController, SIGNAL(update_relationshipInfo(long,int)),
                this->m_crimeTreeController, SLOT(handle_saveRelationshipInfo(long,int)));
    return true;
}

void CrimeTreeWindow::handle_display_message(QString message)
{
    if (message.contains(QString::fromUtf8("Lỗi")))
    {
        QMessageBox::critical(this, QString::fromUtf8("Báo lỗi !"), message,
                              QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this, QString::fromUtf8("Thông báo !"), message,
                              QMessageBox::Ok);
    }
}

void CrimeTreeWindow::handle_display_waiting_form(bool value)
{
    if (value)
        this->m_widgetWaiting->start();
    else
        this->m_widgetWaiting->stop();
}

void CrimeTreeWindow::handle_application_quit()
{
    qApp->quit();
}

void CrimeTreeWindow::handle_getDataFromDatabase_success(bool value)
{
    if (value)
    {
        this->m_crimeTreeController->addCaseToView();
    }
    else
    {
        QMessageBox::critical(this, QString::fromUtf8("Báo lỗi !"),
                              QString::fromUtf8("Lỗi không lấy được dữ liệu từ DB.Vui lòng liên hệ quản trị viên."),
                              QMessageBox::Ok);
    }
}

void CrimeTreeWindow::handle_displayCaseDetail(long id)
{
    this->m_crimeTreeController->handle_displayCase(id);
    this->m_widgetCentral->setCurrentWidget(this->m_crimeTreeController->crimeTreeView());
}

void CrimeTreeWindow::handle_displayCaseManagement()
{
    this->m_widgetCentral->setCurrentWidget(this->m_crimeTreeController->caseManagementView());
}
