#include "crimetreecontroller.h"
#include "crimetreeform.h"
#include "casemanagementview.h"
#include "crimetreeview.h"
#include "crimedetailview.h"
#include "relationshipdetailview.h"
#include "log.h"
#include <QPen>

CrimeTreeController::CrimeTreeController(QObject *parent) : QObject(parent)
{
    this->m_currentForm         = new CrimeTreeForm();
    this->m_caseManagementView  = NULL;
    this->m_crimeTreeView       = NULL;
    this->m_crimeDetailView     = NULL;
    this->m_relationshipDetailView  = NULL;
    this->m_dataCommon          = NULL;

    connect(this->m_currentForm->btnExit, SIGNAL(clicked(bool)),
            this, SLOT(handle_exit_application(bool)));
    connect(this->m_currentForm->btnExitOnDetail, SIGNAL(clicked(bool)),
            this, SLOT(handle_exit_application(bool)));
    connect(this->m_currentForm->btnCaseDetail, SIGNAL(clicked(bool)),
            this, SLOT(handle_buttonCaseDetail_clicked(bool)));
    connect(this->m_currentForm->btnBackToCaseView, SIGNAL(clicked(bool)),
            this, SLOT(handle_buttonCaseManagement_clicked(bool)));
    connect(this->m_currentForm->btnAddNewCrime, SIGNAL(clicked(bool)),
            this, SLOT(handle_buttonCrimeDetail_clicked(bool)));
    connect(this->m_currentForm->btnAcceptCrime, SIGNAL(clicked(bool)),
            this, SLOT(handle_buttonCrimeAccept_clicked(bool)));
    connect(this->m_currentForm->btnCancelCrime, SIGNAL(clicked(bool)),
            this, SLOT(handle_buttonCrimeCancel_clicked(bool)));
    connect(this->m_currentForm->btnUpdateGraphics, SIGNAL(clicked(bool)),
            this, SLOT(handle_buttonCaseUpdate_clicked(bool)));
    connect(this->m_currentForm->btnChoosePicture, SIGNAL(clicked(bool)),
            this, SLOT(handle_buttonCrimeChooseAvatar_clicked(bool)));
    connect(this->m_currentForm->btnAddNewRelationship, SIGNAL(clicked(bool)),
            this, SLOT(handle_buttonRelationshipDetail_clicked(bool)));
    connect(this->m_currentForm->btnAcceptRelationship, SIGNAL(clicked(bool)),
            this, SLOT(handle_buttonRelationshipAccept_clicked(bool)));
    connect(this->m_currentForm->btnCancelRelationship, SIGNAL(clicked(bool)),
            this, SLOT(handle_buttonRelationshipCancel_clicked(bool)));
    connect(this->m_currentForm->btnChooseColor, SIGNAL(clicked(bool)),
            this, SLOT(handle_buttonChooseColor_clicked(bool)));

    connect(this->m_currentForm->graphicsView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(handle_showMenuContext(QPoint)));
    connect(this->m_currentForm->actEditCrime, SIGNAL(triggered(bool)),
            this, SLOT(handle_actEditCrime_triggered(bool)));
    connect(this->m_currentForm->actDelCrime, SIGNAL(triggered(bool)),
            this, SLOT(handle_actDelCrime_triggered(bool)));


}

void CrimeTreeController::setDataCommon(DataCommon *_dataCommon)
{
    this->m_dataCommon = _dataCommon;
}

void CrimeTreeController::addCaseToView()
{
    this->m_currentForm->addCaseToView(this->m_dataCommon);
}

CaseManagementView *CrimeTreeController::caseManagementView()
{
    if (this->m_caseManagementView == NULL)
    {
        this->m_caseManagementView  = new CaseManagementView();
        this->m_caseManagementView->setupUi(this->m_currentForm);
    }
    return m_caseManagementView;
}

CrimeTreeView *CrimeTreeController::crimeTreeView()
{
    if (this->m_crimeTreeView == NULL)
    {
        this->m_crimeTreeView  = new CrimeTreeView();
        this->m_crimeTreeView->setupUi(this->m_currentForm);
    }
    return m_crimeTreeView;
}

CrimeDetailView *CrimeTreeController::crimeDetailView()
{
    if (this->m_crimeDetailView == NULL)
    {
        this->m_crimeDetailView = new CrimeDetailView();
        this->m_crimeDetailView->setupUi(this->m_currentForm);
    }

    return this->m_crimeDetailView;
}

RelationshipDetailView *CrimeTreeController::relationshipDetailView()
{
    if (this->m_relationshipDetailView == NULL)
    {
        this->m_relationshipDetailView = new RelationshipDetailView();
        this->m_relationshipDetailView->setupUi(this->m_currentForm);
    }

    return this->m_relationshipDetailView;
}

void CrimeTreeController::handle_exit_application(bool)
{
    emit exit_application();
}

void CrimeTreeController::handle_saveCaseInfo(long id, int mode)
{
    if (!this->m_dataCommon->hashCase.contains(id))
        return;
    CaseInfo* caseInfo = this->m_dataCommon->hashCase.value(id);

    if (mode == 0) // Add new
    {
        this->m_currentForm->addCaseInfoToView(caseInfo);
    }
    else
    {
        this->m_currentForm->updateCaseInfoOnView(caseInfo);
    }
}

void CrimeTreeController::handle_removeCaseInfo(long id)
{
    this->m_currentForm->removeCaseInfoOnView(id);
}

void CrimeTreeController::handle_displayCase(long id)
{
    this->m_currentForm->graphicsScene->clear();
    if (!this->m_dataCommon->hashCase.contains(id))
        return;
    CaseInfo* caseInfo = this->m_dataCommon->hashCase.value(id);

    QHashIterator<qint64, CrimeInfo*> iterator(caseInfo->hashCrime);
    while(iterator.hasNext())
    {
        iterator.next();
        CrimeGraphicsItem* item = new CrimeGraphicsItem();
        item->setCrimeId(iterator.value()->id);
        item->setPos(iterator.value()->pos);
        item->setCrimeTooltip(iterator.value()->profile);
        item->setCrimeName(iterator.value()->name);
        item->setImgPath(iterator.value()->avatar);
        this->m_currentForm->graphicsScene->addItem(item);

        this->m_currentForm->hashGraphicsItem.insert(iterator.value()->id, item);
    }

    QHashIterator<qint64, RelationshipInfo*> it(caseInfo->hashRelationship);

    while(it.hasNext())
    {
        it.next();
        RelationshipInfo* relationshipInfo = it.value();
        // Get ra 2 CrimeGraphicsItem
        CrimeGraphicsItem* item1 = this->m_currentForm->hashGraphicsItem.value(relationshipInfo->crime_1);
        CrimeGraphicsItem* item2 = this->m_currentForm->hashGraphicsItem.value(relationshipInfo->crime_2);
        RelationshipGraphicsItem* item = new RelationshipGraphicsItem(item1, item2);
        item->pen = relationshipInfo->pen;
        qDebug() << item->pen.color().name() << item->pen.width() << item->pen.style();
        this->m_currentForm->graphicsScene->addItem(item);

        this->m_currentForm->hashRelationshipItem.insert(relationshipInfo->id, item);
    }
}

void CrimeTreeController::handle_saveCrimeInfo(long id, int mode)
{
    if (!this->m_dataCommon->hashCrime.contains(id))
        return;
    CrimeInfo* crimeInfo = this->m_dataCommon->hashCrime.value(id);

    if (mode == 0) // Add new
    {
        CrimeGraphicsItem* item = new CrimeGraphicsItem();
        item->setCrimeId(crimeInfo->id);
        item->setPos(crimeInfo->pos);
        item->setCrimeTooltip(crimeInfo->profile);
        item->setCrimeName(crimeInfo->name);
        item->setImgPath(crimeInfo->avatar);
        this->m_currentForm->graphicsScene->addItem(item);

        this->m_currentForm->hashGraphicsItem.insert(crimeInfo->id, item);
    }
    else
    {
        CrimeGraphicsItem* item = this->m_currentForm->hashGraphicsItem.value(id);
        item->setCrimeId(crimeInfo->id);
        item->setPos(crimeInfo->pos);
        item->setCrimeTooltip(crimeInfo->profile);
        item->setCrimeName(crimeInfo->name);
        item->setImgPath(crimeInfo->avatar);
        item->update();
    }
}

void CrimeTreeController::handle_removeCrimeInfo(long id)
{
    if (!this->m_currentForm->hashGraphicsItem.contains(id))
        return;
    CrimeGraphicsItem* item = this->m_currentForm->hashGraphicsItem.value(id);

    this->m_currentForm->graphicsScene->removeItem(item);
    this->m_currentForm->graphicsScene->update();
}

void CrimeTreeController::handle_saveRelationshipInfo(long id, int mode)
{
    if (!this->m_dataCommon->hashRelationship.contains(id))
        return;
    RelationshipInfo* relationshipInfo = this->m_dataCommon->hashRelationship.value(id);

    if (mode == 0) // Add new
    {
        // Get ra 2 CrimeGraphicsItem
        CrimeGraphicsItem* item1 = this->m_currentForm->hashGraphicsItem.value(relationshipInfo->crime_1);
        CrimeGraphicsItem* item2 = this->m_currentForm->hashGraphicsItem.value(relationshipInfo->crime_2);
        RelationshipGraphicsItem* item = new RelationshipGraphicsItem(item1, item2);
        item->pen = relationshipInfo->pen;
        //        item->id = relationshipInfo->id;
        //        item->crime1_id = relationshipInfo->crime_1;
        //        item->crime2_id = relationshipInfo->crime_2;
        //        item->pen = relationshipInfo->pen;
        //        item->name = relationshipInfo->name;



        //        item->pos1 = item1->pos().toPoint();
        //        item->pos2 = item2->pos().toPoint();
        //        item->setPos(item1->pos());
        this->m_currentForm->graphicsScene->addItem(item);

        this->m_currentForm->hashRelationshipItem.insert(relationshipInfo->id, item);
    }
    else
    {
    }
}

void CrimeTreeController::handle_removeRelationshipInfo(long id)
{

}

void CrimeTreeController::handle_buttonCaseDetail_clicked(bool)
{
    emit display_caseDetail(this->m_currentForm->txtCaseId->text().toLong());
}

void CrimeTreeController::handle_buttonCaseManagement_clicked(bool)
{
    emit display_casemanagement();
}

void CrimeTreeController::handle_buttonCrimeDetail_clicked(bool)
{
    this->m_currentForm->txtCrimeId->setText("-1");
    this->crimeDetailView()->setWindowTitle(QString::fromUtf8("Thêm mới đối tượng"));
    this->crimeDetailView()->exec();
}

void CrimeTreeController::handle_buttonCrimeAccept_clicked(bool)
{
    CrimeInfo* crimeInfo = new CrimeInfo();
    crimeInfo->id = this->m_currentForm->txtCrimeId->text().toLong();
    crimeInfo->name = this->m_currentForm->txtCrimeName->text();
    crimeInfo->profile = this->m_currentForm->txtCrimeProfile->toPlainText();
    crimeInfo->description = this->m_currentForm->txtCrimeDescription->toPlainText();
    crimeInfo->case_id = this->m_currentForm->txtCaseId->text().toLong();
    crimeInfo->pos = QPoint(0, 0);
    crimeInfo->visible = true;
    crimeInfo->avatar = this->m_currentForm->txtCrimeAvatar->text();
    this->m_dataCommon->addCrimeInfoToQueue(crimeInfo);

    this->crimeDetailView()->reject();
}

void CrimeTreeController::handle_buttonCrimeCancel_clicked(bool)
{
    this->crimeDetailView()->reject();
}

void CrimeTreeController::handle_buttonCrimeChooseAvatar_clicked(bool)
{
    QString fileName = QFileDialog::getOpenFileName(NULL,
                                                    QString::fromUtf8("Chọn ảnh"), QDir::currentPath() , tr("Image Files (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty())
    {
        QPixmap pixmap = QPixmap::fromImage(QImage(fileName));
        this->m_currentForm->labelCrimePicture->setPixmap(pixmap.scaled(this->m_currentForm->labelCrimePicture->size(), Qt::KeepAspectRatio));

        this->m_currentForm->txtCrimeAvatar->setText(fileName);
    }
}

void CrimeTreeController::handle_buttonCaseUpdate_clicked(bool)
{
    QHashIterator<quint64, CrimeGraphicsItem*> it(this->m_currentForm->hashGraphicsItem);
    while(it.hasNext())
    {
        it.next();
        CrimeGraphicsItem* item = it.value();
        CrimeInfo* crimeInfo = this->m_dataCommon->hashCrime.value(item->getCrimeId());
        CrimeInfo* crimeTemp = new CrimeInfo();
        crimeTemp->id = crimeInfo->id;
        crimeTemp->name = crimeInfo->name;
        crimeTemp->avatar = crimeInfo->avatar;
        crimeTemp->profile = crimeInfo->profile;
        crimeTemp->description = crimeInfo->description;
        crimeTemp->visible = crimeInfo->visible;
        crimeTemp->pos = item->pos().toPoint();
        crimeTemp->case_id = crimeInfo->case_id;

        this->m_dataCommon->addCrimeInfoToQueue(crimeTemp);

    }
}

void CrimeTreeController::handle_buttonRelationshipDetail_clicked(bool)
{
    this->m_currentForm->txtRelationshipId->setText("-1");
    long case_id = this->m_currentForm->txtCaseId->text().toLong();

    if (this->m_dataCommon->hashCase.contains(case_id))
    {
        CaseInfo* caseInfo = this->m_dataCommon->hashCase.value(case_id);
        if (caseInfo->hashCrime.count() < 2)
        {
            QMessageBox::warning(NULL, QString::fromUtf8("Thông báo"), QString::fromUtf8("Có ít hơn 2 đối tượng để tạo mối quan hệ"), QMessageBox::Ok);
            return;
        }
        this->m_currentForm->cboCrime1Id->clear();
        this->m_currentForm->cboCrime2Id->clear();
        QHashIterator<qint64, CrimeInfo*> iterator(caseInfo->hashCrime);

        while(iterator.hasNext())
        {
            iterator.next();
            this->m_currentForm->cboCrime1Id->addItem(iterator.value()->name, iterator.value()->id);
            this->m_currentForm->cboCrime2Id->addItem(iterator.value()->name, iterator.value()->id);
        }
        this->relationshipDetailView()->setWindowTitle(QString::fromUtf8("Thêm mới quan hệ"));
        this->relationshipDetailView()->exec();
    }
}

void CrimeTreeController::handle_buttonRelationshipAccept_clicked(bool)
{
    if (this->m_currentForm->cboCrime1Id->currentIndex() == this->m_currentForm->cboCrime2Id->currentIndex())
    {
        QMessageBox::warning(NULL, QString::fromUtf8("Thông báo"), QString::fromUtf8("Không thể tạo quan hệ cho cùng 1 đối tượng"), QMessageBox::Ok);
        return;
    }

    QHashIterator<qint64, RelationshipInfo*> iterator(this->m_dataCommon->hashCase.value(this->m_currentForm->txtCaseId->text().toLong())->hashRelationship);
    bool check = false;
    while (iterator.hasNext())
    {
        iterator.next();

        if ((iterator.value()->crime_1 == this->m_currentForm->cboCrime1Id->currentData().toLongLong() &&
             iterator.value()->crime_2 == this->m_currentForm->cboCrime2Id->currentData().toLongLong()) ||
                (iterator.value()->crime_2 == this->m_currentForm->cboCrime1Id->currentData().toLongLong() &&
                 iterator.value()->crime_1 == this->m_currentForm->cboCrime2Id->currentData().toLongLong()))
        {
            check = true;
            break;
        }
    }

    if (check)
    {
        QMessageBox::warning(NULL, QString::fromUtf8("Thông báo"), QString::fromUtf8("Đã tồn tại mối quan hệ này rồi !"), QMessageBox::Ok);
        return;
    }
    RelationshipInfo* relationshipInfo = new RelationshipInfo();
    relationshipInfo->id = this->m_currentForm->txtRelationshipId->text().toLong();
    relationshipInfo->case_id = this->m_currentForm->txtCaseId->text().toLong();
    relationshipInfo->name = this->m_currentForm->txtRelationshipName->text();
    relationshipInfo->visible = true;
    relationshipInfo->crime_1 = this->m_currentForm->cboCrime1Id->currentData().toLongLong();
    relationshipInfo->crime_2 = this->m_currentForm->cboCrime2Id->currentData().toLongLong();
    relationshipInfo->pen = QPen(QColor(this->m_currentForm->txtLineColor->text()),
                                 this->m_currentForm->spnLineSize->value(),
                                 static_cast<Qt::PenStyle>(this->m_currentForm->cboLineType->currentData().toInt()));

    this->m_dataCommon->addRelationshipInfoToQueue(relationshipInfo);
    this->relationshipDetailView()->reject();
}

void CrimeTreeController::handle_buttonRelationshipCancel_clicked(bool)
{
    this->relationshipDetailView()->reject();
}

void CrimeTreeController::handle_buttonChooseColor_clicked(bool)
{
    QColor color = QColorDialog::getColor(Qt::yellow, NULL );
    if(color.isValid())
    {
        this->m_currentForm->txtLineColor->setText(color.name());
        QPixmap pix_color = QPixmap(32, 32);

        QPainter painter_color;

        painter_color.begin(&pix_color);
        painter_color.fillRect(QRect(0, 0, 32, 32), color);
        painter_color.end();

        this->m_currentForm->labelPictureColor->setPixmap(pix_color);
    }
}

void CrimeTreeController::handle_showMenuContext(QPoint pt)
{
    m_pGlobal = this->m_currentForm->graphicsView->mapToGlobal(pt);
    m_pScene = this->m_currentForm->graphicsView->mapToScene(pt);

    QGraphicsItem* item = this->m_currentForm->graphicsScene->itemAt(m_pScene, this->m_currentForm->graphicsView->transform());
    if (item)
        this->m_currentForm->menuContext->exec(m_pGlobal);
}

void CrimeTreeController::handle_actEditCrime_triggered(bool)
{
    CrimeGraphicsItem* item = (CrimeGraphicsItem*)this->m_currentForm->graphicsScene->itemAt(m_pScene, this->m_currentForm->graphicsView->transform());
    if (item)
    {
        CrimeInfo* crime_info = this->m_dataCommon->hashCrime.value(item->getCrimeId());
        this->m_currentForm->txtCrimeId->setText(QString::number(crime_info->id));
        this->m_currentForm->txtCrimeName->setText(crime_info->name);
        this->m_currentForm->txtCrimeProfile->setPlainText(crime_info->profile);
        this->m_currentForm->txtCrimeDescription->setPlainText(crime_info->description);
        this->m_currentForm->txtCrimeAvatar->setText(crime_info->avatar);

        QPixmap pixmap = QPixmap::fromImage(QImage(crime_info->avatar));
        this->m_currentForm->labelCrimePicture->setPixmap(pixmap.scaled(this->m_currentForm->labelCrimePicture->size(), Qt::KeepAspectRatio));

        this->crimeDetailView()->setWindowTitle(QString::fromUtf8("Sửa thông tin đối tượng"));
        this->crimeDetailView()->exec();
    }
}

void CrimeTreeController::handle_actDelCrime_triggered(bool)
{
    CrimeGraphicsItem* item = (CrimeGraphicsItem*)this->m_currentForm->graphicsScene->itemAt(m_pScene, this->m_currentForm->graphicsView->transform());
    if (item)
    {
        QMessageBox::StandardButton reply =
                QMessageBox::question(NULL, QString::fromUtf8("Thông báo !"),
                                      QString::fromUtf8("Bạn chắc chắn muốn xóa thông tin đối tượng : ") + item->getCrimeName(),
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            this->m_dataCommon->addCrimeIdToList(item->getCrimeId());
        }
    }
}
