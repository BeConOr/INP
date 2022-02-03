#include "ellipse.h"
#include <QPainter>

Ellips::Ellips(QPointF point): Figure(point)
{
    Q_UNUSED(point);

}

Ellips::~Ellips(){

}

void Ellips::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);

//    qreal cent_x = (endPoint().x()-startPoint().x())/2.0;
//    qreal cent_y = -(endPoint().y()-startPoint().y())/2.0;
//    qreal x = endPoint().x()-cent_x;
//    qreal y = -(endPoint().y()-cent_y);
//    qreal radius = qSqrt(x*x+y*y);
    qreal x = endPoint().x()-startPoint().x();
    qreal y = endPoint().y()-startPoint().y();

//    painter->drawEllipse(QPointF(cent_x, cent_y), radius, radius);
    painter->drawEllipse(QPointF(startPoint().x(), startPoint().y()), x, y);


    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void Ellips::byButton(QPointF start, QPointF end){
//    qreal start_x = start.x()-end.x();
//    qreal start_y = start.y()+end.y();
//    this->setStartPoint(QPointF(start_x, start_y));
//    qreal end_x = start.x()+end.x();
//    qreal end_y = start.y()-end.y();
//    this->setEndPoint(QPointF(end_x, end_y));
    this->setStartPoint(start);
//    qreal end_x = qAbs(start.x()+end.x());
//    qreal end_y = qAbs(start.y()+end.y());
    qreal end_x = start.x() + end.x();//Нужно исправить
    qreal end_y = start.y() - end.y();
    qDebug() << "Startpoint: " << start.x() << ", " << start.y();
    qDebug() << "Axis a: " << end.x() << "Axis b: " << end.y();
    this->setEndPoint(QPointF(end_x, end_y));

    paramValue[0] = end.x();
    paramValue[2] = end.y();
    paramValue[1] = start.x();
    paramValue[3] = start.y();
//    this->setEndPoint(end);
}

QRectF Ellips::boundingRect() const
{
    /* Возвращаем область, в которой лежит фигура.
     * Обновляемая область зависит от стартовой точки отрисовки и от конечной точки
     * */
    //qreal cent_x = (endPoint().x()-startPoint().x())/2.0;
    //qreal cent_y = -(endPoint().y()-startPoint().y())/2.0;
    qreal x = qAbs(endPoint().x()-startPoint().x());
    qreal y = qAbs(endPoint().y()-startPoint().y());
    //qreal radius = qSqrt(x*x+y*y);
    return QRectF(QPointF(startPoint().x()-x, startPoint().y()-y), QPointF(startPoint().x()+x, startPoint().y()+y));
}

void Ellips::updateRomb()
{
    // Вызываем обновление области, в которой лежит фигура
    qreal x = qAbs(endPoint().x()-startPoint().x());
    qreal y = qAbs(endPoint().y()-startPoint().y());
    //qreal radius = qSqrt(x*x+y*y);
    //qDebug() << radius;
    this->update(startPoint().x()-x, startPoint().y()-y, startPoint().x()+x, startPoint().y()+y);
    paramValue[0] = (double)x;
    paramValue[2] = (double)y;
    paramValue[1] = startPoint().x();
    paramValue[3] = startPoint().y();
}
