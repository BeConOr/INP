#include "geometry.h"
#include "ui_geometry.h"
#include "rec_wid.h"
#include "circ_wid.h"
#include "elip_wid.h"
#include "arc_wid.h"
#include <QStandardItem>
#include <QTreeWidget>
#include "creategroup.h"
#include <QLineEdit>

Geometry::Geometry(QList<Figure *> list, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Geometry)
{
    ui->setupUi(this);

    scene = new PaintScene();
    graphicsView = new View();// Инициализируем графическую сцену
    ui->graphic->addWidget(graphicsView);
    graphicsView->setScene(scene);
    graphicsView->setRenderHint(QPainter::Antialiasing);                // Устанавливаем сглаживание
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключаем скроллбар по вертикали
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали
    graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    //ui->graphicsView->setMouseTracking(true);
//    ui->graphicsView->setScene(scene);
//    ui->graphicsView->setRenderHint(QPainter::Antialiasing);                // Устанавливаем сглаживание
//    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключаем скроллбар по вертикали
//    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);// Отключаем скроллбар по горизонтали
    //ui->graphicsView->setMouseTracking(true);
    ui->treeWidget->header()->hide();
    scene->setSceneRect(0,0, graphicsView->width(), graphicsView->height());
//    scene->setSceneRect(QRectF(QPointF(0, 0), QSizeF(scene->width(), scene->height())));
    scene->setTypeFigure(PaintScene::NoneType);
//    QLineF axis_x;
//    QPainter painter;
//    QPen axisPen = QPen(Qt::black, 2);
//    axisPen.setCosmetic(true);
//    painter.setPen(axisPen);
//    axis_x.setPoints(QPointF(-100,0), QPointF(100, 0));
//    QLineF axis_y;
//    axis_y.setPoints(QPointF(0,-100), QPointF(0, 100));
//    painter.drawLine(axis_x);
//    painter.drawLine(axis_y);
//    scene->addLine(axis_x);
//    scene->addLine(axis_y);

    connect(ui->Line, SIGNAL(clicked()), this, SLOT(line_pushButton_clicked()));
    connect(ui->Circle, SIGNAL(clicked()), this, SLOT(circle_pushButton_clicked()));
    connect(ui->Arc, SIGNAL(clicked()), this, SLOT(arc_pushButton_clicked()));
    connect(ui->Ellipse, SIGNAL(clicked()), this, SLOT(ellipse_pushButton_clicked()));

    connect(scene, &PaintScene::setWidget, this, &Geometry::recieveWidget);
    connect(scene, &PaintScene::sendFigure, this, &Geometry::recieveFigure);

    keyDel = new QShortcut(ui->treeWidget);
    keyDel->setKey(Qt::Key_Delete);
    connect(keyDel, &QShortcut::activated, this, &Geometry::slotShortcutDel);

    keyAddToGroup = new QShortcut(ui->treeWidget);
    keyAddToGroup->setKey(Qt::Key_A);
    connect(keyAddToGroup, &QShortcut::activated, this, &Geometry::addToGroup);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Geometry::slotTimer);
    timer->start(100);

    connect(ui->Generate, &QPushButton::clicked, this, &Geometry::slotGenerate);
    connect(ui->Exit, &QPushButton::clicked, this, &Geometry::slotExit);

    connect(ui->CrGroup, &QPushButton::clicked, this, &Geometry::launchCreate);

    connect(ui->AddToG, &QPushButton::clicked, this, &Geometry::addToGroup);

    connect(ui->DelGr, &QPushButton::clicked, this, &Geometry::deleteGroup);

    connect(ui->ScaleBTN, &QPushButton::clicked, this, &Geometry::scaleScene);


    nameGroup.clear();
    nameGroup.append("Figures");


    if(!figureList.isEmpty()){
        figureList.clear();
    }
    if(!list.isEmpty()){
        foreach(Figure *figure, list){
            if(!nameGroup.contains(figure->getGroupName())){
                nameGroup.insert(figure->getGroupId(), figure->getGroupName());
            }
        }
        foreach(Figure *figure, list){
            scene->addItem(figure);
            recieveFigure(figure);
        }
    }
    foreach(QString name, nameGroup){
        ui->AddList->addItem(name);
    }
    last = figureList.count();
}

Geometry::~Geometry()
{
    delete ui;
}

void Geometry::line_pushButton_clicked()
{
    if(scene->typeFigure() == PaintScene::LineType){
        scene->setTypeFigure(PaintScene::NoneType);
    }else{
        scene->setTypeFigure(PaintScene::LineType);
    }
    scene->setCount(figureList.count());
}

void Geometry::circle_pushButton_clicked()
{
    if(scene->typeFigure() == PaintScene::CircleType){
        scene->setTypeFigure(PaintScene::NoneType);
    }else{
        scene->setTypeFigure(PaintScene::CircleType);
    }
    scene->setCount(figureList.count());
}

void Geometry::arc_pushButton_clicked()
{
    if(scene->typeFigure() == PaintScene::ArcType){
        scene->setTypeFigure(PaintScene::NoneType);
    }else{
        scene->setTypeFigure(PaintScene::ArcType);
    }
    scene->setCount(figureList.count());
}

void Geometry::ellipse_pushButton_clicked()
{
    if(scene->typeFigure() == PaintScene::EllipseType){
        scene->setTypeFigure(PaintScene::NoneType);
    }else{
        scene->setTypeFigure(PaintScene::EllipseType);
    }
    scene->setCount(figureList.count());
}

void Geometry::recieveWidget(QWidget *wid){
    ui->tabWidget->setCurrentIndex(1);
    for (int i = 0; i < ui->Add->count(); ++i)
    {
        QWidget *widget = ui->Add->itemAt(i)->widget();
        if (widget != NULL)
        {
            widget->deleteLater();
        }
    }
    ui->Add->addWidget(wid);
//    QHBoxLayout *figName = new QHBoxLayout();
//    figName->addWidget(new QLabel(QString("Fig. name")));
//    figName->addWidget(new QLineEdit(ui->treeWidget));
//    ui->Add->addLayout(figName);
}

void Geometry::recieveFigure(Figure *fig){
    figureList.append(fig);
//    QString name = fig->getType() + " (%1)";
//    fig->itemName = name.arg(figureList.count());
    ui->treeWidget->clear();
    ui->tabWidget->setCurrentIndex(0);
    QList<QTreeWidgetItem *> topLevels;
    for(int i = 0; i < nameGroup.count(); ++i){
        QTreeWidgetItem *topLevelItem=new QTreeWidgetItem(ui->treeWidget);
        //ui->treeWidget->removeItemWidget()
            // вешаем его на наше дерево в качестве топ узла.
        ui->treeWidget->addTopLevelItem(topLevelItem);
            // укажем текст итема
        topLevelItem->setText(0, nameGroup[i]);
        topLevels.append(topLevelItem);
    }
    for(int index = 0; index<figureList.count(); ++index){
        bool flag = true;
        foreach(int del, delFig){
            if(index == del){
                flag = false;
                break;
            }
        }
        if(flag){
            QTreeWidgetItem *item=new QTreeWidgetItem(topLevels[figureList[index]->getGroupId()]);
                // укажем текст итема
            item->setText(0,figureList[index]->itemName);
            item->setData(1, 0, index);
            qDebug() << item->data(1, 0).toInt();
        }

    }
//    foreach(Figure *fig, figureList){
//        QTreeWidgetItem *item=new QTreeWidgetItem(topLevelItem);
//            // укажем текст итема
//        item->setText(0,fig->getType());
//    }
}

void Geometry::slotShortcutDel(){
    if(ui->treeWidget->topLevelItemCount() != 0){
        bool flag = true;
        for(int i=0;i<ui->treeWidget->topLevelItemCount();++i){
            if(ui->treeWidget->currentItem() == ui->treeWidget->topLevelItem(i)){
                flag = false;
                break;
            }
        }
        if(flag){
            int index = ui->treeWidget->currentItem()->data(1, 0).toInt();
            QString groupName = figureList[index]->getGroupName();
            int groupId = figureList[index]->getGroupId();
            int currItem = ui->treeWidget->findItems(groupName, Qt::MatchStartsWith)[0]->indexOfChild(ui->treeWidget->currentItem());
    //        figureList[index]->deleteLater();
    //        figureList.remove(index);
            delFig.append(index);
            scene->removeItem(figureList[index]);
            QTreeWidgetItem *item = ui->treeWidget->findItems(groupName, Qt::MatchStartsWith)[0]->child(currItem);
            ui->treeWidget->findItems(groupName, Qt::MatchStartsWith)[0]->removeChild(item);

            if((ui->treeWidget->findItems(groupName, Qt::MatchStartsWith)[0]->childCount() == 0) && (groupId != 0)){
                if(groupId != nameGroup.count()-1){
                    foreach(Figure *fig, figureList){
                        if(fig->getGroupId() > groupId){
                            fig->changeGroup(fig->getGroupId()-1, fig->getGroupName());
                        }
                    }
                }
                nameGroup.remove(groupId);
                ui->AddList->removeItem(groupId);
                updateTree();
            }
            }
    }
    //ui->treeWidget->focusWidget()->deleteLater();
}

void Geometry::slotTimer(){

    //Блок для выделения объекта на геометрической панели по его клику в дереве
    if(ui->treeWidget->topLevelItemCount() != 0){
        for(int i=0;i<ui->treeWidget->topLevelItemCount();++i){
            for(int j=0; j<ui->treeWidget->topLevelItem(i)->childCount(); ++j){
                int index = ui->treeWidget->topLevelItem(i)->child(j)->data(1, 0).toInt();
                figureList[index]->oPen();
                figureList[index]->updateRomb();
            }
        }
        if(ui->treeWidget->selectedItems().count() != 0){
            bool flag = true;
            for(int i=0;i<ui->treeWidget->topLevelItemCount();++i){
                if(ui->treeWidget->currentItem() == ui->treeWidget->topLevelItem(i)){
                    flag = false;
                    break;
                }
            }
            if(flag){
                int index = ui->treeWidget->currentItem()->data(1, 0).toInt();
                figureList[index]->fPen();
                figureList[index]->updateRomb();
            }
        }
    }
    //Изменение цвета кнопок при нажатии
    switch(scene->typeFigure()){
    case PaintScene::LineType:{
        ui->Line->setStyleSheet(QString("background-color: rgb(0,255,0);border: none;"));
        QList<QPushButton *> button = ui->buttonGroup->findChildren<QPushButton *>(QString(), Qt::FindChildrenRecursively);
        foreach(QPushButton *item, button){
            if(item != ui->Line){
                item->setStyleSheet(QString("background-color: rgb(240,240,240);"));
            }
        }
        break;
    }
    case PaintScene::CircleType:{
        ui->Circle->setStyleSheet(QString("background-color: rgb(0,255,0);border: none;"));
        QList<QPushButton *> button = ui->buttonGroup->findChildren<QPushButton *>(QString(), Qt::FindChildrenRecursively);
        foreach(QPushButton *item, button){
            if(item != ui->Circle){
                item->setStyleSheet(QString("background-color: rgb(240,240,240);"));
            }
        }
        break;
    }
    case PaintScene::EllipseType:{
        ui->Ellipse->setStyleSheet(QString("background-color: rgb(0,255,0);border: none;"));
        QList<QPushButton *> button = ui->buttonGroup->findChildren<QPushButton *>(QString(), Qt::FindChildrenRecursively);
        foreach(QPushButton *item, button){
            if(item != ui->Ellipse){
                item->setStyleSheet(QString("background-color: rgb(240,240,240); border = 1"));
            }
        }
        break;
    }
    case PaintScene::ArcType:{
        ui->Arc->setStyleSheet(QString("background-color: rgb(0,255,0);border: none;"));
        QList<QPushButton *> button = ui->buttonGroup->findChildren<QPushButton *>(QString(), Qt::FindChildrenRecursively);
        foreach(QPushButton *item, button){
            if(item != ui->Arc){
                item->setStyleSheet(QString("background-color: rgb(240,240,240); border = 1"));
            }
        }
        break;
    }
    default:{
        QList<QPushButton *> button = ui->buttonGroup->findChildren<QPushButton *>(QString(), Qt::FindChildrenRecursively);
        foreach(QPushButton *item, button){
            item->setStyleSheet(QString("background-color: rgb(240,240,240); border = 1"));
        }
        break;
    }
    }
}


void Geometry::slotGenerate(){
    foreach(int index, delFig){
        figureList[index]->deleteLater();
        figureList.remove(index);
    }
    emit sendList(figureList);
    ui->treeWidget->clear();
    delFig.clear();
    this->close();
}

void Geometry::slotExit(){
    for(int i = last; i < figureList.count(); i++){
        figureList[i]->deleteLater();
        figureList.remove(i);
    }
    emit Exit();
    delFig.clear();
    ui->treeWidget->clear();
}

void Geometry::create(QList<Figure *> list, QString name){
    nameGroup.append(name);
    ui->AddList->addItem(name);
    qDebug() << "Group Name: " << nameGroup;
    if(!figureList.isEmpty()){
        foreach(Figure *figure, figureList){
            scene->removeItem(figure);
        }
        figureList.clear();
    }
    if(!list.isEmpty()){
        for(int index = 0; index<list.count(); ++index){
            bool flag = true;
            foreach(int del, delFig){
                if(index == del){
                    flag = false;
                    break;
                }
            }
            if(flag){
            scene->addItem(list[index]);
            }
            recieveFigure(list[index]);
        }
    }
    //last = figureList.count();
    foreach(Figure *fig, list){
        qDebug() << "id: " << fig->getGroupId() << ", Group Name: " << fig->getGroupName();
    }
    foreach(Figure *fig, figureList){
        qDebug() << "id: " << fig->getGroupId() << ", Group Name: " << fig->getGroupName();
    }
}

void Geometry::launchCreate(){
    CreateGroup *Group = new CreateGroup(figureList, nameGroup, delFig);
    connect(Group, &CreateGroup::addGroupSignal, this, &Geometry::create);
    if (Group->exec() == QDialog::Accepted) {

    }
            delete Group;
}

void Geometry::addToGroup(){
    //if(ui->treeWidget->findItems(QString("Figures"), Qt::MatchStartsWith)[0]->childCount() != 0){
    int index = ui->treeWidget->currentItem()->data(1, 0).toInt();
    figureList[index]->changeGroup(ui->AddList->currentIndex(), ui->AddList->currentText());
    qDebug() << "AddTo. index: " << figureList[index]->getGroupId() << ", name: " << figureList[index]->getGroupName();
    //}
    updateTree();
}

void Geometry::updateTree(){
    ui->treeWidget->clear();
    ui->tabWidget->setCurrentIndex(0);
    QList<QTreeWidgetItem *> topLevels;
    for(int i = 0; i < nameGroup.count(); ++i){
        QTreeWidgetItem *topLevelItem=new QTreeWidgetItem(ui->treeWidget);
        //ui->treeWidget->removeItemWidget()
            // вешаем его на наше дерево в качестве топ узла.
        ui->treeWidget->addTopLevelItem(topLevelItem);
            // укажем текст итема
        topLevelItem->setText(0, nameGroup[i]);
        topLevels.append(topLevelItem);
    }
    for(int index = 0; index<figureList.count(); ++index){
        bool flag = true;
        foreach(int del, delFig){
            if(index == del){
                flag = false;
                break;
            }
        }
        if(flag){
            QTreeWidgetItem *item=new QTreeWidgetItem(topLevels[figureList[index]->getGroupId()]);
                // укажем текст итема
            item->setText(0,figureList[index]->getType());
            item->setData(1, 0, index);
            qDebug() << item->data(1, 0).toInt();
        }
    }
}

void Geometry::deleteGroup(){
    if(ui->AddList->currentIndex() != 0){
        foreach(Figure *fig, figureList){
            if(fig->getGroupId() == ui->AddList->currentIndex()){
                fig->changeGroup(0, QString("Figures"));
            }
        }

        if(ui->AddList->currentIndex() != nameGroup.count()-1){
            foreach(Figure *fig, figureList){
                if(fig->getGroupId() > ui->AddList->currentIndex()){
                    fig->changeGroup(fig->getGroupId()-1, fig->getGroupName());
                }
            }
        }
        nameGroup.remove(ui->AddList->currentIndex());
        ui->AddList->removeItem(ui->AddList->currentIndex());
        updateTree();
    }
}

void Geometry::scaleScene(){
    scene->setSceneRect(scene->itemsBoundingRect());
}
