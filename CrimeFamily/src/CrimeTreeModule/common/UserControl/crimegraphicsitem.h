#ifndef CRIMEGRAPHICSITEM_H
#define CRIMEGRAPHICSITEM_H

#include <QGraphicsItem>

class RelationshipGraphicsItem;

class CrimeGraphicsItem : public QGraphicsItem
{
public:
    CrimeGraphicsItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

    void addRelationship(RelationshipGraphicsItem* relationship);

    QString getCrimeName() const;
    void setCrimeName(const QString &value);

    QString getImgPath() const;
    void setImgPath(const QString &value);

    QString getCrimeTooltip() const;
    void setCrimeTooltip(const QString &value);

    long getCrimeId() const;
    void setCrimeId(long value);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
private:
    long    crimeId;
    QString crimeTooltip;
    QString crimeName;
    QString imgPath;

    QList<RelationshipGraphicsItem *> edgeList;
};

#endif // CRIMEGRAPHICSITEM_H
