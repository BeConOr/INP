#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QObject>
#include <QGraphicsObject>
#include "figure.h"

class Ellips: public Figure
{
    Q_OBJECT
public:
    explicit Ellips(QPointF point);
    ~Ellips();
    virtual const QString getType(){return QString("Ellipse");}
    virtual double getLength(){
        double x = abs(endPoint().x() - startPoint().x());
        double y = abs(endPoint().y() - startPoint().y());
        return M_PI*(x + y);
    }

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
public slots:
    void byButton(QPointF start, QPointF end);
    void updateRomb();
};

#endif // ELLIPSE_H
