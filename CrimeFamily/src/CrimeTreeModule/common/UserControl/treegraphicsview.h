#ifndef TREEGRAPHICSVIEW_H
#define TREEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class TreeGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TreeGraphicsView(QWidget *parent = 0);

#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void scaleView(qreal scaleFactor);

public slots:
    void zoomIn();
    void zoomOut();
};

#endif // TREEGRAPHICSVIEW_H
