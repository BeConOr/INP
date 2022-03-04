#ifndef GRIDMESH_H
#define GRIDMESH_H

#include <QObject>
#include <QGraphicsObject>
#include "figure.h"
#include "paintscene.h"

class GridMesh : public Figure
{
    Q_OBJECT
public:
    explicit GridMesh(PaintScene* parent, QPointF point = QPointF(0.0, 0.0));
    ~GridMesh();
    virtual const QString getType(){return QString("Grid Mesh");}

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    PaintScene* parentRect = NULL;
public slots:
    void updateRomb();

};

#endif // GRIDMESH_H
