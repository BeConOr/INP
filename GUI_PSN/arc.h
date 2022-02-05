#ifndef ARC_H
#define ARC_H

#include <QObject>
#include <QGraphicsObject>
#include "figure.h"

class Arc: public Figure
{
    Q_OBJECT
public:
    explicit Arc(QPointF point, bool fl = false);
    ~Arc();
    virtual const QString getType(){return QString("Arc");}
    virtual double getLength(){
        return 2.0*M_PI*radius*(endPoint().x()-endPoint().y())/360.0;
    }

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    double radius = 0.0;
    double startAngle = 30.0;
    double endAngle = 60.0;
    bool flag;

public slots:
    void byButton(QPointF start, double radius, QPointF end);
    void updateRomb();

};

#endif // ARC_H
