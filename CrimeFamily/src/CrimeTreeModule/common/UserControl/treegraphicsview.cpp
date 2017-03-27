#include "treegraphicsview.h"

TreeGraphicsView::TreeGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    this->setRenderHint(QPainter::Antialiasing, true);
    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
}

#ifndef QT_NO_WHEELEVENT
//! [5]
void TreeGraphicsView::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
//! [5]
#endif

void TreeGraphicsView::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void TreeGraphicsView::zoomIn()
{

}

void TreeGraphicsView::zoomOut()
{

}
