#include "arc.h"
#include <QPainter>
#include <math.h>

Arc::Arc(QPointF point, bool fl): Figure(point)
{
     Q_UNUSED(point);
    flag = fl;
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
    if(!flag){
    qreal x = endPoint().x()-startPoint().x();
    qreal y = -(endPoint().y()-startPoint().y());
    radius = qSqrt(x*x+y*y);
    startAngle = atan2(y, x) * 180.0/M_PI;
    endAngle = startAngle + 30.0;
    }

    QVector<qreal> dashes;
    double step = (2.0*M_PI*radius*(qAbs(endAngle-startAngle)/360.0)/((double)(devide[0]+1))) - 0.5;
    dashes << 0.5 << step/4.0;
    qDebug() << tr("Length: %1, step: %2").arg(2*M_PI*radius).arg(2.0*M_PI*radius/((double)devide[0]));
    penDot.setDashPattern(dashes);

//    painter->drawEllipse(QPointF(cent_x, cent_y), radius, radius);
    QRectF r1 = QRectF (startPoint().x()-radius, startPoint().y()-radius, 2.0*radius, 2.0*radius);
    painter->drawArc(r1, startAngle*16.0, (endAngle - startAngle)*16.0);
    painter->setPen(penDot);
    painter->drawArc(r1, (startAngle-1.0+((endAngle - startAngle)/(double)devide[0]))*16.0, (endAngle - startAngle)*16.0);


    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void Arc::byButton(QPointF start, double radius, QPointF end){
//    qreal start_x = start.x()-end.x();
//    qreal start_y = start.y()+end.y();
//    this->setStartPoint(QPointF(start_x, start_y));
//    qreal end_x = start.x()+end.x();
//    qreal end_y = start.y()-end.y();
//    this->setEndPoint(QPointF(end_x, end_y));
    flag = true;
    this->setStartPoint(start);
    this->radius = radius;
//    qreal end_x = start.x()+radius/qSqrt(2.0);
//    qreal end_y = start.y()+radius/qSqrt(2.0);
    startAngle = end.x();
    endAngle = end.y();
    qDebug() << "Arc parameters:";
    qDebug() << "Startpoint: " << startPoint().x() << ", " << -startPoint().y();
    qDebug() << "Radius: " << this->radius;
    qDebug() << "Angles: " << startAngle << ", " << endAngle;
    this->setEndPoint(QPointF(radius, radius));

    paramValue[0] = this->radius;
    paramValue[2] = this->radius;
    paramValue[1] = start.x();
    paramValue[3] = -start.y();
    angles[0] = M_PI * startAngle / 180.0;
    angles[1] = M_PI * endAngle /180.0;
}

QRectF Arc::boundingRect() const
{
    /* Возвращаем область, в которой лежит фигура.
     * Обновляемая область зависит от стартовой точки отрисовки и от конечной точки
     * */
    return QRectF(QPointF(startPoint().x()-radius, startPoint().y()-radius), QPointF(startPoint().x()+radius, startPoint().y()+radius));
}

void Arc::updateRomb()
{
    // Вызываем обновление области, в которой лежит фигура
    this->update(startPoint().x()-radius, startPoint().y()-radius, startPoint().x()+radius, startPoint().y()+radius);
    paramValue[0] = radius;
    paramValue[2] = radius;
    paramValue[1] = startPoint().x();
    paramValue[3] = startPoint().y();
}
