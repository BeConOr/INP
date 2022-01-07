#ifndef ARC_H
#define ARC_H

#include <QObject>
#include <QGraphicsObject>
#include "figure.h"

class Arc: public Figure
{
    Q_OBJECT
public:
    explicit Arc(QPointF point);
    ~Arc();
    virtual const QString getType(){return QString("Arc");}

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
public slots:
    void byButton(QPointF start, QPointF end);
    void updateRomb();

};

#endif // ARC_H
