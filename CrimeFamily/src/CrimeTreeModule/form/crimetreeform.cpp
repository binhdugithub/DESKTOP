#include "crimetreeform.h"
#include "log.h"

CrimeTreeForm::CrimeTreeForm(QObject *parent) : QObject(parent)
{
    // CaseManagementView
    this->tableCase             = new QTableWidget();
    this->labelCaseName         = new QLabel(QString::fromUtf8("Tên vụ án : "));
    this->labelTimeBegin        = new QLabel(QString::fromUtf8("Thời điểm bắt đầu : "));
    this->labelTimeEnd          = new QLabel(QString::fromUtf8("Thời điểm kết thúc : "));
    this->labelCaseDescription  = new QLabel(QString::fromUtf8("Nội dung : "));
    this->labelCaseStatus       = new QLabel(QString::fromUtf8("Tình trạng : "));
    this->txtCaseId             = new QLineEdit();
    this->txtCaseName           = new QLineEdit();
    this->txtCaseTimeBegin      = new QTimeEdit();
    this->txtCaseTimeEnd        = new QTimeEdit();
    this->txtCaseDateBegin      = new QDateEdit();
    this->txtCaseDateEnd        = new QDateEdit();
    this->txtCaseDescription    = new QPlainTextEdit();
    this->cboCasetatus          = new QComboBox();
    this->btnAddNewCase         = new QPushButton(QString::fromUtf8("Thêm mới"));
    this->btnEditCase           = new QPushButton(QString::fromUtf8("Sửa"));
    this->btnDelCase            = new QPushButton(QString::fromUtf8("Xóa"));
    this->btnAcceptCase         = new QPushButton(QString::fromUtf8("Chấp nhận"));
    this->btnCancelCase         = new QPushButton(QString::fromUtf8("Bỏ qua"));
    this->btnCaseDetail         = new QPushButton(QString::fromUtf8("Chi tiết"));
    this->btnExit               = new QPushButton(QString::fromUtf8("Thoát"));

    // Set QTableWidget properties
    this->tableCase->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->tableCase->setSelectionMode(QAbstractItemView::ExtendedSelection);
    this->tableCase->setColumnCount(4);
    this->tableCase->setHorizontalHeaderLabels(QStringList() << "ID" << "STT" << "Tên vụ án" << "Tình trạng");
    this->tableCase->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->tableCase->horizontalHeader()->setStretchLastSection(true);
    this->tableCase->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    this->tableCase->hideColumn(0);
    this->tableCase->setColumnWidth(1, 50);
    this->tableCase->setColumnWidth(2, 500);
    this->tableCase->setColumnWidth(3, 100);

    // Set input properties
    this->txtCaseTimeBegin->setDisplayFormat("HH:mm");
    this->txtCaseTimeEnd->setDisplayFormat("HH:mm");
    this->txtCaseDateBegin->setDisplayFormat("dd/MM/yyyy");
    this->txtCaseDateEnd->setDisplayFormat("dd/MM/yyyy");

    //
    this->cboCasetatus->setItemDelegate(new QStyledItemDelegate());
    this->cboCasetatus->addItems(QStringList() << "Chưa phá án xong" << "Đã phá án xong");

    // Set stylesheet
    this->labelCaseName->setProperty("text-parameter", true);
    this->labelTimeBegin->setProperty("text-parameter", true);
    this->labelTimeEnd->setProperty("text-parameter", true);
    this->labelCaseDescription->setProperty("text-parameter", true);
    this->labelCaseStatus->setProperty("text-parameter", true);

    // Create connector
    connect(this->btnAcceptCase, SIGNAL(clicked(bool)),
            this, SLOT(handle_btnAcceptCase_clicked(bool)));
    connect(this->btnAddNewCase, SIGNAL(clicked(bool)),
            this, SLOT(handle_btnAddNewCase_clicked(bool)));
    connect(this->btnCancelCase, SIGNAL(clicked(bool)),
            this, SLOT(handle_btnCancelCase_clicked(bool)));
    connect(this->btnDelCase, SIGNAL(clicked(bool)),
            this, SLOT(handle_btnDelCase_clicked(bool)));
    connect(this->btnEditCase, SIGNAL(clicked(bool)),
            this, SLOT(handle_btnEditCase_clicked(bool)));

    connect(this->tableCase, SIGNAL(itemSelectionChanged()),
            this, SLOT(handle_tableCase_itemSelectionChanged()));

    this->showControlOnCaseView(true);

    // CrimeTreeView
    this->graphicsView          = new TreeGraphicsView();
    this->graphicsScene         = new QGraphicsScene();
    this->btnBackToCaseView     = new QPushButton(QString::fromUtf8("Quay lại danh sách vụ án"));
    this->btnExitOnDetail       = new QPushButton(QString::fromUtf8("Thoát"));
    this->btnAddNewCrime        = new QPushButton(QString::fromUtf8("Thêm mới đối tượng"));
    this->btnAddNewRelationship = new QPushButton(QString::fromUtf8("Thêm mới mối quan hệ"));
    this->btnUpdateGraphics     = new QPushButton(QString::fromUtf8("Cập nhật"));
    this->chkShowRelationship   = new QCheckBox();
    this->chkRelationshipIsLine = new QCheckBox();

    this->chkShowRelationship->setText(QString::fromUtf8("Hiển thị mối quan hệ"));
    this->chkRelationshipIsLine->setText(QString::fromUtf8("Hiển thị dạng đường thẳng"));
    this->graphicsView->setScene(this->graphicsScene);

    // CrimeDetailView
    this->labelCrimeName        = new QLabel(QString::fromUtf8("Tên :"));
    this->labelCrimeAvatar      = new QLabel(QString::fromUtf8("Ảnh :"));
    this->labelCrimePicture     = new QLabel();;
    this->labelCrimeProfile     = new QLabel(QString::fromUtf8("Thông tin :"));
    this->labelCrimeDescription = new QLabel(QString::fromUtf8("Ghi chú :"));;
    this->txtCrimeId            = new QLineEdit();
    this->txtCrimeName          = new QLineEdit();
    this->txtCrimeAvatar        = new QLineEdit();
    this->txtCrimeProfile       = new QPlainTextEdit();
    this->txtCrimeDescription   = new QPlainTextEdit();
    this->btnAcceptCrime        = new QPushButton(QString::fromUtf8("Chấp nhận"));
    this->btnCancelCrime        = new QPushButton(QString::fromUtf8("Bỏ qua"));
    this->btnChoosePicture      = new QPushButton(QString::fromUtf8("Chọn ảnh"));
    this->menuContext           = new QMenu(this->graphicsView);
    this->actEditCrime          = new QAction(QString::fromUtf8("Sửa thông tin đối tượng"));
    this->actDelCrime           = new QAction(QString::fromUtf8("Xóa thông tin đối tượng"));
    this->actEditRelationship   = new QAction(QString::fromUtf8("Sửa thông tin quan hệ"));
    this->actDelRelationship    = new QAction(QString::fromUtf8("Xóa thông tin quan hệ"));

    this->labelCrimePicture->setMinimumSize(240, 320);
    this->labelCrimePicture->setStyleSheet("border: 1px solid black");
    QPixmap pixmap = QPixmap::fromImage(QImage(":/images/no_avatar.jpg"));
    this->labelCrimePicture->setPixmap(pixmap.scaled(this->labelCrimePicture->size(), Qt::KeepAspectRatio));
    this->txtCrimeAvatar->setText(":/images/no_avatar.jpg");

    this->menuContext->addAction(this->actEditCrime);
    this->menuContext->addAction(this->actDelCrime);
    this->menuContext->addSeparator();
//    this->menuContext->addAction(this->actEditRelationship);
    this->menuContext->addAction(this->actDelRelationship);


    // RelationshipDetailView
    this->labelCrime1Id             = new QLabel(QString::fromUtf8("Đối tượng 1 :"));
    this->labelCrime2Id             = new QLabel(QString::fromUtf8("Đối tượng 2 :"));
    this->labelRelationshipName     = new QLabel(QString::fromUtf8("Mối quan hệ :"));;
    this->labelLineColor            = new QLabel(QString::fromUtf8("Mầu đường :"));;
    this->labelLineType             = new QLabel(QString::fromUtf8("Loại đường :"));;
    this->labelLineSize             = new QLabel(QString::fromUtf8("Kích thước đường :"));;
    this->labelPictureColor         = new QLabel();
    this->cboCrime1Id               = new QComboBox();
    this->cboCrime2Id               = new QComboBox();
    this->cboLineType               = new QComboBox();
    this->txtRelationshipName       = new QLineEdit();
    this->txtRelationshipId         = new QLineEdit();
    this->txtLineColor              = new QLineEdit();
    this->spnLineSize               = new QSpinBox();
    this->btnAcceptRelationship     = new QPushButton(QString::fromUtf8("Chấp nhận"));
    this->btnCancelRelationship     = new QPushButton(QString::fromUtf8("Bỏ qua"));
    this->btnChooseColor            = new QPushButton(QString::fromUtf8("Chọn mầu"));

    this->labelPictureColor->setMinimumSize(32, 32);
    this->spnLineSize->setRange(2, 99);
    QPixmap pix_color = QPixmap(32, 32);

    QPainter painter_color;

    painter_color.begin(&pix_color);
    painter_color.fillRect(QRect(0, 0, 32, 32), Qt::black);
    painter_color.end();

    this->labelPictureColor->setPixmap(pix_color);

    this->cboLineType->setIconSize(QSize(200, 14));
    this->cboLineType->setEditable(false);
    for (int aaa = Qt::SolidLine; aaa < Qt::CustomDashLine; aaa++)
    {
        QPixmap pix(200,14);
        pix.fill(Qt::white);

        QBrush brush(Qt::black);
        QPen pen(brush, 5 , static_cast<Qt::PenStyle>(aaa));

        QPainter painter(&pix);
        painter.setPen(pen);
        painter.drawLine(2,7,198,7);

        this->cboLineType->addItem(QIcon(pix),"", aaa);
    }
    this->cboLineType->setCurrentIndex(0);

    this->txtLineColor->setText(QColor(0, 0, 0, 0).name());
}

void CrimeTreeForm::lockControlOnCaseView(bool value)
{
    if (value)
    {
        this->btnCaseDetail->setEnabled(false);
        this->btnEditCase->setEnabled(false);
        this->btnDelCase->setEnabled(false);
    }
    else
    {
        this->btnCaseDetail->setEnabled(true);
        this->btnEditCase->setEnabled(true);
        this->btnDelCase->setEnabled(true);
    }
}

void CrimeTreeForm::showControlOnCaseView(bool value)
{
    if (value)
    {
        this->btnAddNewCase->show();
        this->btnEditCase->show();
        this->btnDelCase->show();
        this->btnCaseDetail->show();
        this->btnExit->show();
        this->btnAcceptCase->hide();
        this->btnCancelCase->hide();
    }
    else
    {
        this->btnAddNewCase->hide();
        this->btnEditCase->hide();
        this->btnDelCase->hide();
        this->btnCaseDetail->hide();
        this->btnExit->hide();
        this->btnAcceptCase->show();
        this->btnCancelCase->show();
    }

    this->tableCase->setEnabled(value);
    this->txtCaseName->setEnabled(!value);
    this->txtCaseTimeBegin->setEnabled(!value);
    this->txtCaseTimeEnd->setEnabled(!value);
    this->txtCaseDateBegin->setEnabled(!value);
    this->txtCaseDateEnd->setEnabled(!value);
    this->txtCaseDescription->setEnabled(!value);
    this->cboCasetatus->setEnabled(!value);
}

void CrimeTreeForm::addCaseToView(DataCommon *_dataCommon)
{
    this->m_dataCommon = _dataCommon;
    QMapIterator<qint64, CaseInfo*> iterator(_dataCommon->hashCase);

    //    this->tableCase->setRowCount(_dataCommon->hashCase.count());
    int i = 0;
    while (iterator.hasNext())
    {
        iterator.next();
        this->tableCase->insertRow(i);

        QTableWidgetItem* iId = new QTableWidgetItem(QString::number(iterator.value()->id));
        QTableWidgetItem* iSTT = new QTableWidgetItem(QString::number(i+1));
        QTableWidgetItem* iName = new QTableWidgetItem(iterator.value()->name);
        QTableWidgetItem* iStatus = new QTableWidgetItem(iterator.value()->status);

        iId->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        iSTT->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        iName->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        iStatus->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        this->tableCase->setItem(i, 0, iId);
        this->tableCase->setItem(i, 1, iSTT);
        this->tableCase->setItem(i, 2, iName);
        this->tableCase->setItem(i, 3, iStatus);
        i++;
    }

    //
    lockControlOnCaseView(true);
}

void CrimeTreeForm::addCaseInfoToView(CaseInfo *_caseInfo)
{
    int i = this->tableCase->rowCount();
    this->tableCase->insertRow(i);

    QTableWidgetItem* iId = new QTableWidgetItem(QString::number(_caseInfo->id));
    QTableWidgetItem* iSTT = new QTableWidgetItem(QString::number(i + 1));
    QTableWidgetItem* iName = new QTableWidgetItem(_caseInfo->name);
    QTableWidgetItem* iStatus = new QTableWidgetItem(_caseInfo->status);

    iId->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    iSTT->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    iName->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    iStatus->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    this->tableCase->setItem(i, 0, iId);
    this->tableCase->setItem(i, 1, iSTT);
    this->tableCase->setItem(i, 2, iName);
    this->tableCase->setItem(i, 3, iStatus);
}

void CrimeTreeForm::updateCaseInfoOnView(CaseInfo *_caseInfo)
{
    int i = 0;
    for ( ; i < this->tableCase->rowCount() ; i++)
    {
        QTableWidgetItem* iID = this->tableCase->item(i, 0);

        if (iID->text().toLong() == _caseInfo->id)
        {
            break;
        }
    }

    QTableWidgetItem* iName = this->tableCase->item(i, 2);
    QTableWidgetItem* iStatus = this->tableCase->item(i, 3);

    iName->setText(_caseInfo->name);
    iStatus->setText(_caseInfo->status);
}

void CrimeTreeForm::removeCaseInfoOnView(long id)
{
    int i = 0;
    for ( ; i < this->tableCase->rowCount() ; i++)
    {
        QTableWidgetItem* iID = this->tableCase->item(i, 0);

        if (iID->text().toLong() == id)
        {
            break;
        }
    }

    for (int j = 0 ; j < this->tableCase->columnCount() ; j++)
    {
        QTableWidgetItem* item = this->tableCase->item(i, j);
        delete item;
        item = NULL;
    }
    this->tableCase->removeRow(i);

    for (; i < this->tableCase->rowCount() ; i++)
    {
        QTableWidgetItem* iID = this->tableCase->item(i, 1);

        iID->setText(QString::number(i + 1));
    }
}

void CrimeTreeForm::setCaseToView(long id)
{
    if (this->m_dataCommon->hashCase.contains(id))
    {
        CaseInfo* caseInfo = this->m_dataCommon->hashCase.value(id);
        if (caseInfo)
        {
            this->txtCaseId->setText(QString::number(caseInfo->id));
            this->txtCaseName->setText(caseInfo->name);
            this->txtCaseDescription->setPlainText(caseInfo->description);
            this->txtCaseDateBegin->setDate(caseInfo->timebegin);
            this->txtCaseDateEnd->setDate(caseInfo->timeend);
            this->cboCasetatus->setCurrentText(caseInfo->status);
        }
    }
    else
    {
        this->txtCaseId->setText("-1");
        this->txtCaseName->setText("");
        this->txtCaseDescription->setPlainText("");
        this->txtCaseDateBegin->setDate(QDate::currentDate());
        this->txtCaseDateEnd->setDate(QDate::currentDate());
    }
}

void CrimeTreeForm::handle_btnAddNewCase_clicked(bool)
{
    this->setCaseToView(-1);
    this->showControlOnCaseView(false);
}

void CrimeTreeForm::handle_btnEditCase_clicked(bool)
{
    this->showControlOnCaseView(false);
}

void CrimeTreeForm::handle_btnDelCase_clicked(bool)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(NULL, "Xác nhận !", "Bạn có muốn xóa các vụ án đã chọn ? ",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QList<QTableWidgetItem*> lstItem = this->tableCase->selectedItems();

        for (int i = 0 ; i < lstItem.count() ; i+=3)
        {
            long id = this->tableCase->item(lstItem.at(i)->row(), 0)->text().toLong();
            this->m_dataCommon->addCaseIdToList(id);
        }
    }
}

void CrimeTreeForm::handle_btnAcceptCase_clicked(bool)
{
    //
    CaseInfo* caseInfo = new CaseInfo();

    caseInfo->id = this->txtCaseId->text().toLong();
    caseInfo->name = this->txtCaseName->text();
    caseInfo->timebegin = this->txtCaseDateBegin->date();
    caseInfo->timeend = this->txtCaseDateEnd->date();
    caseInfo->status = this->cboCasetatus->currentText();
    caseInfo->description = this->txtCaseDescription->toPlainText();

    this->m_dataCommon->addCaseInfoToQueue(caseInfo);
    this->showControlOnCaseView(true);
}

void CrimeTreeForm::handle_btnCancelCase_clicked(bool)
{
    this->showControlOnCaseView(true);
    if (this->tableCase->rowCount() != 0)
        this->tableCase->selectRow(0);
}

void CrimeTreeForm::handle_tableCase_itemSelectionChanged()
{
    QTableWidgetItem* item  = NULL;
    long id                 = -1;
    if (this->tableCase->selectedItems().count() == 0)
    {
        lockControlOnCaseView(true);
    }
    else
    {
        lockControlOnCaseView(false);
        item = this->tableCase->selectedItems().last();
    }

    if (item != NULL)
    {
        int row = item->row();

        id = this->tableCase->item(row, 0)->text().toLong();
    }
    this->setCaseToView(id);
}

