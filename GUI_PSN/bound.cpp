#include "bound.h"
#include "ui_bound.h"
#include <QAbstractItemView>

Bound::Bound(QList<Figure *> list, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bound)
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

    connect(ui->DirCheck, &QCheckBox::clicked, this, &Bound::chDir);

    foreach(QRadioButton *check, ui->ManageBox->findChildren<QRadioButton *>()){
        connect(check, &QRadioButton::clicked, this, &Bound::rad);
    }

    ui->DirSecond->hide();
    ui->label_2->hide();

    connect(ui->define, &QPushButton::clicked, this, &Bound::define);
    ui->tableWidget->hide();

    for(int i = 0; i < 4; ++i){
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem());
    }

    connect(ui->treeWidget, &QTreeWidget::itemClicked, this, &Bound::focusOnTree);
}

Bound::~Bound()
{
    delete ui;
}

void Bound::updateTree(){
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
        if(figureList[index]->getGroupId() == 0){
            QTreeWidgetItem *item=new QTreeWidgetItem(topLevels[figureList[index]->getGroupId()]);
                // укажем текст итема
            item->setText(0,figureList[index]->itemName);
            item->setData(1, 0, index);
            qDebug() << item->data(1, 0).toInt();
        }
    }
}


void Bound::chDir(){
    if(ui->DirCheck->isChecked()){
        ui->DirCheck->setText("Linear");
        ui->DirSecond->show();
        ui->label_2->show();
    }else{
        ui->DirCheck->setText("Const");
        ui->DirSecond->hide();
        ui->label_2->hide();
    }
}

void Bound::rad(){
    if(ui->Dirichlet->isChecked()){
        ui->DirCheck->show();
        ui->label_1->setText(QString("U1"));
        ui->label_2->setText(QString("U2"));
    }if(ui->Neumann->isChecked()){
        ui->DirCheck->show();
        ui->label_1->setText(QString("E1"));
        ui->label_2->setText(QString("E2"));
    }if(ui->Newton->isChecked()){
        ui->DirCheck->setChecked(true);
        ui->DirSecond->show();
        ui->label_2->show();
        ui->DirCheck->hide();
        ui->label_1->setText(QString("alpha"));
        ui->label_2->setText(QString("beta"));
    }if(ui->Bounder->isChecked()){
        ui->DirCheck->setChecked(true);
        ui->DirSecond->show();
        ui->label_2->show();
        ui->DirCheck->hide();
        ui->label_1->setText(QString("left"));
        ui->label_2->setText(QString("right"));
    }
}

void Bound::define(){
    //if(ui->treeWidget->findItems(QString("Figures"), Qt::MatchStartsWith)[0]->childCount() != 0){
    if(ui->treeWidget->selectedItems().count() != 0){
        if(ui->treeWidget->topLevelItemCount() != 0){
            bool flag = true;
            int topLevel = 0;
            for(int i=0;i<ui->treeWidget->topLevelItemCount();++i){
                if(ui->treeWidget->currentItem() == ui->treeWidget->topLevelItem(i)){
                    flag = false;
                    topLevel = i;
                    break;
                }
            }
            if(flag){
                int index = ui->treeWidget->currentItem()->data(1, 0).toInt();
                int type = 0;
                if(ui->Dirichlet->isChecked()){
                    type = Bound::Dirichlet;
                }if(ui->Neumann->isChecked()){
                    type = Bound::Neumann;
                }if(ui->Newton->isChecked()){
                    type = Bound::Newtone;
                }if(ui->Bounder->isChecked()){
                    type = Bound::Bounder;
                }
                double value[2] = {ui->DirFirst->value(), ui->DirSecond->value()};
                figureList[index]->setBound(type, ui->DirCheck->isChecked(), value);
                qDebug() << figureList[index]->getBound().type << ", " << figureList[index]->getBound().method << ", " << figureList[index]->getBound().value;
                //}
                updateTree();
            }else{
                if(topLevel != 0){
                    foreach(Figure *fig, figureList){
                        if(fig->getGroupId() == topLevel){
                            int type = 0;
                            if(ui->Dirichlet->isChecked()){
                                type = Bound::Dirichlet;
                            }if(ui->Neumann->isChecked()){
                                type = Bound::Neumann;
                            }if(ui->Newton->isChecked()){
                                type = Bound::Newtone;
                            }if(ui->Bounder->isChecked()){
                                type = Bound::Bounder;
                            }
                            double value[2] = {ui->DirFirst->value(), ui->DirSecond->value()};
                            fig->setBound(type, ui->DirCheck->isChecked(), value);
                            qDebug() << fig->getBound().type << ", " << fig->getBound().method << ", " << fig->getBound().value;
                            //}
                            updateTree();
                        }
                    }
                }
            }
        }
    }
}

void Bound::focusOnTree(){
    if(ui->treeWidget->selectedItems().count() != 0){
        ui->tableWidget->show();
        if(ui->treeWidget->topLevelItemCount() != 0){
            bool flag = true;
            int topLevel = 0;
            for(int i=0;i<ui->treeWidget->topLevelItemCount();++i){
                if(ui->treeWidget->currentItem() == ui->treeWidget->topLevelItem(i)){
                    flag = false;
                    topLevel = i;
                    break;
                }
            }
            BoundaryCond bounder;
            if(flag){
                int index = ui->treeWidget->currentItem()->data(1, 0).toInt();
                bounder = figureList[index]->getBound();

            }else{
                if(topLevel != 0){
                    foreach(Figure *fig, figureList){
                        if(fig->getGroupId() == topLevel){
                            bounder = fig->getBound();
                            break;
                        }
                    }
                }else{
                    bounder = {0, false, {0.0, 0.0}};
                }

            }
            switch (bounder.type) {
            case Bound::Dirichlet:
                ui->tableWidget->item(0, 0)->setText(QString("Dirichlet"));
                ui->tableWidget->verticalHeaderItem(2)->setText(QString("U1"));
                ui->tableWidget->verticalHeaderItem(3)->setText(QString("U2"));
                break;
            case Bound::Neumann:
                ui->tableWidget->item(0, 0)->setText(QString("Neumann"));
                ui->tableWidget->verticalHeaderItem(2)->setText(QString("E1"));
                ui->tableWidget->verticalHeaderItem(3)->setText(QString("E2"));
                break;
            case Bound::Newtone:
                ui->tableWidget->item(0, 0)->setText(QString("Newtone"));
                ui->tableWidget->verticalHeaderItem(2)->setText(QString("alpha"));
                ui->tableWidget->verticalHeaderItem(3)->setText(QString("beta"));
                break;
            case Bound::Bounder:
                ui->tableWidget->item(0, 0)->setText(QString("Bounder"));
                ui->tableWidget->verticalHeaderItem(2)->setText(QString("left"));
                ui->tableWidget->verticalHeaderItem(3)->setText(QString("right"));
                break;
            default:
                ui->tableWidget->item(0, 0)->setText(QString("None"));
                ui->tableWidget->verticalHeaderItem(2)->setText(QString("first"));
                ui->tableWidget->verticalHeaderItem(3)->setText(QString("second"));
                break;
            }
            if(bounder.method){
                ui->tableWidget->item(1, 0)->setText(QString("Linear"));
                ui->tableWidget->item(2, 0)->setText(QString("%1").arg(bounder.value[0]));
                ui->tableWidget->item(3, 0)->setText(QString("%1").arg(bounder.value[1]));
            }else{
                ui->tableWidget->item(1, 0)->setText(QString("Constant"));
                ui->tableWidget->item(2, 0)->setText(QString("%1").arg(bounder.value[0]));
                ui->tableWidget->item(3, 0)->setText(QString("None"));
            }
        }
    }
}
