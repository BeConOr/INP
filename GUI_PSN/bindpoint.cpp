#include "bindpoint.h"

BindPoint::BindPoint(Figure *par, const QPoint &point) : QPointF(point)
{
    parent = par;
}

void BindPoint::bindPoints(BindPoint *point){
    binded.append(point);
}

QList<BindPoint *> BindPoint::getBindPoints(){
    return binded;
}

Figure* BindPoint::getParent(){
    return parent;
}
