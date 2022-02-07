#ifndef BINDPOINT_H
#define BINDPOINT_H

#include <QObject>
#include <QPointF>
#include "figure.h"

class BindPoint : public QPointF
{
    Q_OBJECT
public:
    explicit BindPoint(Figure *par, const QPoint &point);

signals:
private:
    Figure *parent;
    QList<BindPoint *> binded;

public:
    void bindPoints(BindPoint *point);
    Figure* getParent();
    QList<BindPoint *> getBindPoints();

};

#endif // BINDPOINT_H
