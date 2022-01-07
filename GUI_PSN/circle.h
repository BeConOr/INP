#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>
#include <QGraphicsObject>
#include "figure.h"

class Circle: public Figure
{
    Q_OBJECT
public:
    explicit Circle(QPointF point);
    ~Circle();
    virtual const QString getType(){return QString("Circle");}
    virtual double getLength(){
        double x = endPoint().x() - startPoint().x();
        double y = endPoint().y() - startPoint().y();
        double radius = sqrt(x*x + y*y);
        return 2.0*M_PI*radius;
    }

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
public slots:
    void byButton(QPointF start, QPointF end);
    void updateRomb();
};

#endif // CIRCLE_H
