#include "crimegraphicsitem.h"
#include "relationshipgraphicsitem.h"
#include <QtWidgets>

CrimeGraphicsItem::CrimeGraphicsItem()
{
    setFlags(ItemIsSelectable | ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setAcceptHoverEvents(true);
    crimeTooltip = "";
    this->setZValue(1000);
}

QRectF CrimeGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, 300, 400);
}

void CrimeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    painter->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );

    if (this->imgPath.at(0) == ':')
    {
        painter->drawPixmap(30, 0, QPixmap::fromImage(QImage(":/images/no_avatar.jpg")));
    }
    else
    {
        QFile file(this->imgPath);

        if(!file.exists())
        {
            painter->drawPixmap(30, 0, QPixmap::fromImage(QImage(":/images/no_avatar.jpg")));
        }
        else
        {
            QImage img(this->imgPath);

            painter->drawPixmap(30, 0, QPixmap::fromImage(img.scaled(240, 320, Qt::KeepAspectRatio)));
        }
    }
    QFont font("times", 12);
    QFontMetrics fm(font);
    int pixelsWidth = fm.width(this->crimeName);
    int pixelsHigh = fm.height();

    painter->setRenderHints( QPainter::Antialiasing | QPainter::TextAntialiasing );
    painter->setPen(Qt::black);
    painter->setFont(font);

    painter->drawText(0, 320, 300, 80, Qt::AlignVCenter | Qt::AlignHCenter, this->crimeName);
}

void CrimeGraphicsItem::addRelationship(RelationshipGraphicsItem *relationship)
{
    edgeList << relationship;
    relationship->adjust();
}

void CrimeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void CrimeGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

void CrimeGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    this->setToolTip(crimeTooltip);
}

long CrimeGraphicsItem::getCrimeId() const
{
    return crimeId;
}

void CrimeGraphicsItem::setCrimeId(long value)
{
    crimeId = value;
}

QVariant CrimeGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (RelationshipGraphicsItem *edge, edgeList)
            edge->adjust();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

QString CrimeGraphicsItem::getCrimeTooltip() const
{
    return crimeTooltip;
}

void CrimeGraphicsItem::setCrimeTooltip(const QString &value)
{
    crimeTooltip = value;
}

QString CrimeGraphicsItem::getImgPath() const
{
    return imgPath;
}

void CrimeGraphicsItem::setImgPath(const QString &value)
{
    imgPath = value;
}

QString CrimeGraphicsItem::getCrimeName() const
{
    return crimeName;
}

void CrimeGraphicsItem::setCrimeName(const QString &value)
{
    crimeName = value;
}
