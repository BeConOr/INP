#include "gridmesh.h"
#include <QPainter>

GridMesh::GridMesh(PaintScene* parent, QPointF point): Figure(point)
{
    Q_UNUSED(point)
    parentRect = parent;
}

GridMesh::~GridMesh()
{

}

// Реализуем метод отрисовки
void GridMesh::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setPen(QPen(Qt::blue, 2));
    pen.setColor(Qt::red);
    pen.setStyle(Qt::DashLine);
    pen.setWidth(1);
    painter->setPen(pen);

//    for(int i = 0; i <= parentRect->width(); ++i){
//        painter->drawLine(i, -parentRect->height(), i, parentRect->height());
//    }
//    for(int i = 0; i >= -parentRect->width(); --i){
//        painter->drawLine(i, -parentRect->height(), i, parentRect->height());
//    }

//    for(int i = 0; i <= parentRect->height(); ++i){
//        painter->drawLine(-parentRect->width(), i, parentRect->width(), i);
//    }
//    for(int i = 0; i >= -parentRect->height(); --i){
//        painter->drawLine(-parentRect->width(), i, parentRect->width(), i);
//    }
    painter->drawLine(0, parentRect->sceneRect().topLeft().y(), 0, parentRect->sceneRect().bottomLeft().y());
    painter->drawLine(parentRect->sceneRect().topLeft().x(), 0, parentRect->sceneRect().topRight().x(), 0);
//    painter->drawLine(0, -100, 0, 100);
//    painter->drawLine(-100, 0, 100, 0);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF GridMesh::boundingRect() const
{
    /* Возвращаем область, в которой лежит фигура.
     * Обновляемая область зависит от стартовой точки отрисовки и от конечной точки
     * */
    return QRectF(-1000, -1000, 1000, 1000);
    qDebug() << parentRect->height() << " - " << parentRect->width();
}

void GridMesh::updateRomb()
{
    // Вызываем обновление области, в которой лежит фигура
    this->update(parentRect->sceneRect());
    qDebug() << parentRect->height() << " - " << parentRect->width();
}
