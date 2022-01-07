#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QGraphicsObject>
#include "figure.h"

class Line: public Figure
{
    Q_OBJECT
public:
    explicit Line(QPointF point);
    ~Line();
    virtual const QString getType(){return QString("Line");}

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public slots:
    void byButton(QPointF start, QPointF end, bool check);
};

#endif // LINE_H
