#include "line.h"
#include <QPainter>

Line::Line(QPointF point): Figure(point)
{
    Q_UNUSED(point)
}

Line::~Line()
{

}

// Реализуем метод отрисовки
void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setPen(QPen(Qt::blue, 2));
    painter->setPen(pen);

    QLineF line;

    line.setPoints(startPoint(), endPoint());

    painter->drawLine(line);

    for(int i = 1; i < devide[0] + 1; ++i){
//        QLineF unit = line.unitVector();
//        double ky = endPoint().y() - startPoint().y();
//        double kx = endPoint().x() - startPoint().x();
//        double y = startPoint().y() + ky*(double)i/(devide[0]+1.0);
//        double x = startPoint().x() + kx*(double)i/((double)(devide[0]+1));
        painter->setPen(penDot);
        painter->drawPoint(line.pointAt((double)i/((double)(devide[0] + 1))));
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void Line::byButton(QPointF start, QPointF end, bool check){
    if(check){
        this->setStartPoint(start);
        qreal end_x = start.x()+ end.x()*qCos(end.y()*M_PI/180.0);
        qreal end_y = start.y()-end.x()*qSin(end.y()*M_PI/180.0);
        this->setEndPoint(QPointF(end_x, end_y));
        paramValue[1] = end_x;
        paramValue[3] = -end_y;
    }else{
        this->setStartPoint(start);
        this->setEndPoint(end);
        paramValue[1] = end.x();
        paramValue[3] = -end.y();
    }

    paramValue[0] = start.x();
    paramValue[2] = -start.y();
}
