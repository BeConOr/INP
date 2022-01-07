#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>

class View: public QGraphicsView
{
    Q_OBJECT
public:
    View();
    ~View();

private:
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    //void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);
};

#endif // VIEW_H
