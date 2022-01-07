#include "arc.h"
#include <QPainter>

Arc::Arc(QPointF point): Figure(point)
{
     Q_UNUSED(point);
}

Arc::~Arc(){

}

void Arc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);

//    qreal cent_x = (endPoint().x()-startPoint().x())/2.0;
//    qreal cent_y = -(endPoint().y()-startPoint().y())/2.0;
//    qreal x = endPoint().x()-cent_x;
//    qreal y = -(endPoint().y()-cent_y);
//    qreal radius = qSqrt(x*x+y*y);
    qreal x = endPoint().x()-startPoint().x();
    qreal y = endPoint().y()-startPoint().y();
    qreal radius = qSqrt(x*x+y*y);

//    painter->drawEllipse(QPointF(cent_x, cent_y), radius, radius);
    QRectF rectangle(startPoint().x(), startPoint().y(), 2*endPoint().x(), 2*endPoint().y());
//    painter->drawArc();


    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void Arc::byButton(QPointF start, QPointF end){
//    qreal start_x = start.x()-end.x();
//    qreal start_y = start.y()+end.y();
//    this->setStartPoint(QPointF(start_x, start_y));
//    qreal end_x = start.x()+end.x();
//    qreal end_y = start.y()-end.y();
//    this->setEndPoint(QPointF(end_x, end_y));
    this->setStartPoint(start);
    qreal end_x = start.x()-end.x()/qSqrt(2.0);
    qreal end_y = start.y()-end.y()/qSqrt(2.0);
    qDebug() << "Startpoint: " << start.x() << ", " << start.y();
    qDebug() << "Radius: " << end.x();
    this->setEndPoint(QPointF(end_x, end_y));
//    this->setEndPoint(end);
}

QRectF Arc::boundingRect() const
{
    /* Возвращаем область, в которой лежит фигура.
     * Обновляемая область зависит от стартовой точки отрисовки и от конечной точки
     * */
    //qreal cent_x = (endPoint().x()-startPoint().x())/2.0;
    //qreal cent_y = -(endPoint().y()-startPoint().y())/2.0;
    qreal x = endPoint().x()-startPoint().x();
    qreal y = endPoint().y()-startPoint().y();
    qreal radius = qSqrt(x*x+y*y);
    return QRectF(QPointF(startPoint().x()-radius, startPoint().y()-radius), QPointF(startPoint().x()+radius, startPoint().y()+radius));
}

void Arc::updateRomb()
{
    // Вызываем обновление области, в которой лежит фигура
    qreal x = endPoint().x()-startPoint().x();
    qreal y = endPoint().y()-startPoint().y();
    qreal radius = qSqrt(x*x+y*y);
    qDebug() << radius;
    this->update(startPoint().x()-radius, startPoint().y()-radius, startPoint().x()+radius, startPoint().y()+radius);
}
