#include "relationshipgraphicsitem.h"
#include "crimegraphicsitem.h"
#include <math.h>
#include <QDebug>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

RelationshipGraphicsItem::RelationshipGraphicsItem(CrimeGraphicsItem* sourceNode, CrimeGraphicsItem* destNode)
{
    source = sourceNode;
    dest = destNode;
    arrowSize = 10;
    pen = QPen(Qt::black, 2, Qt::SolidLine);
    source->addRelationship(this);
    dest->addRelationship(this);
    adjust();

}

QRectF RelationshipGraphicsItem::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

void RelationshipGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    if (!source || !dest)
        return;

    // Draw the line
    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;
    painter->setRenderHints( QPainter::Antialiasing);
    painter->setPen(pen);

    painter->drawLine(line);

    // Draw the arrows
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;

    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
                                              cos(angle - Pi / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                              cos(angle - Pi + Pi / 3) * arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}

void RelationshipGraphicsItem::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 150, 200), mapFromItem(dest, 150, 200));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.))
    {
        QPointF edgeOffset((line.dx() * 5) / length, (line.dy() * 5) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    }
    else
    {
        sourcePoint = destPoint = line.p1();
    }
}
