#include "view.h"

View::View(): QGraphicsView()
{
    //setDragMode(QGraphicsView::ScrollHandDrag);
}

View::~View(){

}

void View::wheelEvent(QWheelEvent *event){
    if (event->modifiers().testFlag(Qt::ControlModifier)){ // zoom only when CTRL key pressed

        //QPoint numPixels = event->pixelDelta() / 150;
        QPoint numDegrees = event->angleDelta();
        //qDebug() << numPixels;
        qDebug() << numDegrees;

//        if (!numPixels.isNull()) {
//            this->scale(numPixels.x()/150, numPixels.y()/150);
//        } else if (!numDegrees.isNull()) {
//            QPoint numSteps = numDegrees;
//            this->scale(numSteps.x(), numSteps.y());
//        }
        if(numDegrees.y() > 0){
           this->scale(1.2, 1.2);
        }else{
            this->scale(0.8, 0.8);
        }
        //event->accept();
    }
}

void View::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Left:{
        this->scene()->setSceneRect(QRectF(100, 0, this->scene()->width()+100, this->scene()->height()));
        break;
    }
    case Qt::Key_Right:{
        this->scene()->setSceneRect(QRectF(-100, 0, this->scene()->width()-100, this->scene()->height()));
        break;
    }
    case Qt::Key_Up:{
        this->scene()->setSceneRect(QRectF(0, 100, this->scene()->width(), this->scene()->height()+100));
        break;
    }
    case Qt::Key_Down:{
        this->scene()->setSceneRect(QRectF(0, -100, this->scene()->width(), this->scene()->height()-100));
        break;
    }
    }
}

//void View::mousePressEvent(QMouseEvent *event){
//    if(event->button() == Qt::RightButton){
//        this->centerOn(event->pos());
//    }
//}
