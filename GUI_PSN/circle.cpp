#include "circle.h"
#include <QPainter>
#include <math.h>

Circle::Circle(QPointF point): Figure(point)
{
    Q_UNUSED(point);

}

Circle::~Circle(){

}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    QVector<qreal> dashes;
    double step = (2.0*M_PI*radius/((double)devide[0])) - 0.5;
    dashes << 0.5 << step/4.0;
    qDebug() << tr("Length: %1, step: %2").arg(2*M_PI*radius).arg(2.0*M_PI*radius/((double)devide[0]));
    penDot.setDashPattern(dashes);

//    painter->drawEllipse(QPointF(cent_x, cent_y), radius, radius);
    painter->drawEllipse(QPointF(startPoint().x(), startPoint().y()), radius, radius);
    painter->setPen(penDot);
    painter->drawEllipse(QPointF(startPoint().x(), startPoint().y()), radius, radius);

//    for(int i = 1; i <= devide[0]; ++i){
//        double step = 2.0*M_PI/((double)devide[0]);
//        double y = startPoint().y() - radius*sin(step*(double)i);
//        double x = startPoint().x() + radius*cos(step*(double)i);;
//        painter->setPen(penDot);
//        painter->drawPoint(x, y);
//    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void Circle::byButton(QPointF start, QPointF end){
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

    paramValue[0] = end.x();
    paramValue[2] = end.x();
    paramValue[1] = start.x();
    paramValue[3] = -start.y();
//    this->setEndPoint(end);
}

QRectF Circle::boundingRect() const
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

void Circle::updateRomb()
{
    // Вызываем обновление области, в которой лежит фигура
    qreal x = endPoint().x()-startPoint().x();
    qreal y = endPoint().y()-startPoint().y();
    qreal radius = qSqrt(x*x+y*y);
    qDebug() << radius;
    this->update(startPoint().x()-radius, startPoint().y()-radius, startPoint().x()+radius, startPoint().y()+radius);
    paramValue[0] = radius;
    paramValue[2] = radius;
    paramValue[1] = startPoint().x();
    paramValue[3] = startPoint().y();
}
