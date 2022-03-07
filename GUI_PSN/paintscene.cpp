#include "paintscene.h"
#include "line.h"
#include "circle.h"
#include "ellipse.h"
#include "rec_wid.h"
#include "circ_wid.h"
#include "elip_wid.h"
#include "arc_wid.h"
#include "arc.h"
#include "figurename.h"
#include <QVBoxLayout>
#include "gridmesh.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    tempFigure = 0;
//    GridMesh* mesh = new GridMesh(this);
//    this->addItem(mesh);
}

PaintScene::~PaintScene()
{

}

int PaintScene::typeFigure() const
{
    return m_typeFigure;
}

void PaintScene::setTypeFigure(const int type)
{
    m_typeFigure = type;
    if(tempFigure != 0){
        //tempFigure->deleteLater();
        this->removeItem(tempFigure);
        tempFigure = 0;
    }
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_typeFigure != NoneType){
        /* Устанавливаем конечную координату положения мыши
         * в текущую отрисовываемую фигуру
         * */
        tempFigure->setEndPoint(event->scenePos());
        /* Обновляем содержимое сцены,
         * необходимо для устранения артефактов при отрисовке фигур
         * */
        this->update(QRectF(0,0,this->width(), this->height()));
    }
//    else{
////        int x = event->scenePos().x();
////        int y = event->scenePos().y();
////        QPointF point = event->scenePos() - event->buttonDownScenePos(Qt::LeftButton);
////        int x = point.x();
////        int y = point.y();
//        int x_start = this->sceneRect().center().x() - this->width();
//        int y_start = this->sceneRect().center().y() - this->height();
//        int x = event->scenePos().x();
//        int y = event->scenePos().y();
//        this->setSceneRect(QRectF(x_start+x, y_start+y,x_start+this->width()+x, y_start+this->height()+y));
//    }
}

/* Как только нажали кнопку мыши, создаём фигуру одного из трёх типов
 * и помещаем её на сцену, сохранив указатель на неё в переменной
 * tempFigure
 * */
void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_typeFigure != NoneType){
        if(tempFigure != 0){
            //tempFigure->deleteLater();
            this->removeItem(tempFigure);
            tempFigure = 0;
        }
        switch (m_typeFigure) {
    //    case SquareType: {
    //        Square *item = new Square(event->scenePos());
    //        item->setPos(event->pos());
    //        tempFigure = item;
    //        break;
    //    }
        case LineType: {
            Line *item = new Line(event->scenePos());
            item->setPos(event->pos());
            tempFigure = item;
            this->addItem(tempFigure);
            Rec_wid *workPanel = new Rec_wid(item->startPoint(), item->endPoint());
            tempWidg = workPanel;
            emit setWidget(workPanel);
            connect(item, &Line::pointChanged, workPanel, &Rec_wid::setA);
            connect(workPanel, &Rec_wid::OK,item, &Line::byButton);
            connect(workPanel, &Rec_wid::OK,this, &PaintScene::updateAr);
            connect(workPanel, &Rec_wid::Canc,this, &PaintScene::buttonCanc);
            break;
        }
        case CircleType: {
            Circle *item = new Circle(event->scenePos());
            item->setPos(event->pos());
            tempFigure = item;
            this->addItem(tempFigure);
            Circ_wid *workPanel = new Circ_wid(item->startPoint(), item->endPoint());
            tempWidg = workPanel;
            emit setWidget(workPanel);
            connect(item, &Circle::pointChanged, workPanel, &Circ_wid::setA);
            connect(workPanel, &Circ_wid::OK,item, &Circle::byButton);
            connect(workPanel, &Circ_wid::OK,this, &PaintScene::updateAr);
            connect(workPanel, &Circ_wid::Canc,this, &PaintScene::buttonCanc);
            break;
        }
        case EllipseType: {
            Ellips *item = new Ellips(event->scenePos());
            item->setPos(event->pos());
            tempFigure = item;
            this->addItem(tempFigure);
            Elip_wid *workPanel = new Elip_wid(item->startPoint(), item->endPoint());
            tempWidg = workPanel;
            emit setWidget(workPanel);
            connect(item, &Ellips::pointChanged, workPanel, &Elip_wid::setA);
            connect(workPanel, &Elip_wid::OK,item, &Ellips::byButton);
            connect(workPanel, &Elip_wid::OK,this, &PaintScene::updateAr);
            connect(workPanel, &Elip_wid::Canc,this, &PaintScene::buttonCanc);
            break;
        }
        case ArcType: {
            Arc *item = new Arc(event->scenePos());
            item->setPos(event->pos());
            tempFigure = item;
            this->addItem(tempFigure);
            Arc_wid *workPanel = new Arc_wid(item->startPoint(), item->endPoint());
            tempWidg = workPanel;
            emit setWidget(workPanel);
            connect(item, &Arc::pointChanged, workPanel, &Arc_wid::setA);
            connect(workPanel, &Arc_wid::OK,item, &Arc::byButton);
            connect(workPanel, &Arc_wid::OK,this, &PaintScene::updateArc);
            connect(workPanel, &Arc_wid::Canc,this, &PaintScene::buttonCanc);
            break;
        }
    //    default:{
    //        Square *item = new Square(event->scenePos());
    //        item->setPos(event->pos());
    //        tempFigure = item;
    //        break;
    //    }
        }
        if(tempWidg != 0){
            tempWidg->findChild<QVBoxLayout *>()->insertWidget(1, new FigureName(tempWidg));
        }
    }
}

void PaintScene::updateAr(QPointF start, QPointF end){
    Q_UNUSED(start);
    Q_UNUSED(end);
    this->update(QRectF(0,0,this->width(), this->height()));
    QString name = tempWidg->findChild<FigureName *>()->getName();
    if(name.isEmpty()){
        tempFigure->itemName = tempFigure->getType() + tr(" (%1)").arg(number+1);
    }else{
        tempFigure->itemName = name;
    }
    ++number;
    emit sendFigure(tempFigure);
    tempFigure = 0;
    tempWidg->deleteLater();
    tempWidg = 0;
}

void PaintScene::updateArc(QPointF start, double radius, QPointF angles){
    Q_UNUSED(radius);
    updateAr(start, angles);
}

void PaintScene::buttonCanc(){
    this->removeItem(tempFigure);
    tempFigure->deleteLater();
    tempFigure = 0;
    tempWidg->deleteLater();
    tempWidg = 0;
}

//void PaintScene::keyPressEvent(QKeyEvent *event){
//    switch (event->key()) {
//    case Qt::Key_Left:{
//        this->setSceneRect(QRectF(100, 0, this->width()+100, this->height()));
//        break;
//    }
//    case Qt::Key_Right:{
//        this->setSceneRect(QRectF(-100, 0, this->width()-100, this->height()));
//        break;
//    }
//    case Qt::Key_Up:{
//        this->setSceneRect(QRectF(0, 100, this->width(), this->height()+100));
//        break;
//    }
//    case Qt::Key_Down:{
//        this->setSceneRect(QRectF(0, -100, this->width(), this->height()-100));
//        break;
//    }
//    }
//}

void PaintScene::setCount(int numb){
    number = numb;
}

