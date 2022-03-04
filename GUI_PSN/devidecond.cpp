#include "devidecond.h"
#include "ui_devidecond.h"
#include <QAbstractItemView>

DevideCond::DevideCond(QList<Figure *> list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DevideCond)
{
    ui->setupUi(this);
    ui->treeWidget->header()->hide();

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
            figureList.append(figure);
        }
    }
    updateTree();

    connect(ui->set, &QPushButton::clicked, this, &DevideCond::define);
    ui->tableWidget->hide();

    for(int i = 0; i < 2; ++i){
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem());
    }

    connect(ui->treeWidget, &QTreeWidget::itemClicked, this, &DevideCond::focusOnTree);
}

DevideCond::~DevideCond()
{
    delete ui;
}

void DevideCond::updateTree(){
    ui->treeWidget->clear();
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
        QTreeWidgetItem *item=new QTreeWidgetItem(topLevels[figureList[index]->getGroupId()]);
            // укажем текст итема
        item->setText(0,figureList[index]->itemName);
        item->setData(1, 0, index);
        qDebug() << item->data(1, 0).toInt();
    }
}


void DevideCond::define(){
    //if(ui->treeWidget->findItems(QString("Figures"), Qt::MatchStartsWith)[0]->childCount() != 0){
    if(ui->treeWidget->selectedItems().count() != 0){
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
                figureList[index]->setDevide(ui->Segm->value(), ui->Quadr->value());
                qDebug() << figureList[index]->getDevide()[0] << ", " << figureList[index]->getDevide()[1];
                //}
                updateTree();
            }
            ui->Segm->setValue(6);
            ui->Quadr->setValue(9);
        }
    }
}

void DevideCond::focusOnTree(){
    if(ui->treeWidget->selectedItems().count() != 0){
        ui->tableWidget->show();
        if(ui->treeWidget->topLevelItemCount() != 0){
            bool flag = true;
            for(int i=0;i<ui->treeWidget->topLevelItemCount();++i){
                if(ui->treeWidget->currentItem() == ui->treeWidget->topLevelItem(i)){
                    flag = false;
                    break;
                }
            }
            int* bounder = NULL;
            if(flag){
                int index = ui->treeWidget->currentItem()->data(1, 0).toInt();
                bounder = figureList[index]->getDevide();

            }
            if(bounder != NULL){
                ui->tableWidget->item(0, 0)->setText(QString("%1").arg(bounder[0]));
                ui->tableWidget->item(1, 0)->setText(QString("%1").arg(bounder[1]));
            }else{
                ui->tableWidget->item(0, 0)->setText(QString("None"));
                ui->tableWidget->item(1, 0)->setText(QString("None"));
            }
        }
    }
}
