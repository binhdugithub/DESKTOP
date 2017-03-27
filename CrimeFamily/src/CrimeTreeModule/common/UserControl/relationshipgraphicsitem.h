#ifndef RELATIONSHIPGRAPHICSITEM_H
#define RELATIONSHIPGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPoint>
#include <QPainter>

class CrimeGraphicsItem;

class RelationshipGraphicsItem : public QGraphicsItem
{

public:
    explicit RelationshipGraphicsItem(CrimeGraphicsItem* sourceNode, CrimeGraphicsItem* destNode);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

    void adjust();

    CrimeGraphicsItem *source, *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
    QPen pen;
};

#endif // RELATIONSHIPGRAPHICSITEM_H
