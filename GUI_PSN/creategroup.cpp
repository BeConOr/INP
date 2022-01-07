#include "creategroup.h"
#include "ui_creategroup.h"

CreateGroup::CreateGroup(QList<Figure *> figures, QList<QString> names, QList<int> del, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGroup)
{
    ui->setupUi(this);
    ui->AddTree->header()->hide();
    ui->AllTree->header()->hide();
    figureList = figures;
    delFig = del;
    group = names;
    addGroup.append(QString("New Group"));
    for(int i = 0; i < figureList.count(); ++i){
        bool flag = true;
        foreach(int d, delFig){
            if(i == d){
                flag = false;
                break;
            }
        }
        if(flag){
            All.append(i);
        }
    }
    qDebug()<<All;
    createTree(All, ui->AllTree, group);
    createTree(Add, ui->AddTree, addGroup);
    connect(ui->Add, &QPushButton::clicked, this, &CreateGroup::addButton);
    connect(ui->Remove, &QPushButton::clicked, this, &CreateGroup::removeButton);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CreateGroup::okSlot);
}

CreateGroup::~CreateGroup()
{
    delete ui;
}

void CreateGroup::createTree(QList<int> curList, QTreeWidget *treeWidget, QList<QString> nameGroup){
    treeWidget->clear();
    if(curList.count() != 0){
        QList<QTreeWidgetItem *> topLevels;
        for(int i = 0; i < nameGroup.count(); ++i){
            QTreeWidgetItem *topLevelItem=new QTreeWidgetItem(treeWidget);
            //ui->treeWidget->removeItemWidget()
                // вешаем его на наше дерево в качестве топ узла.
            treeWidget->addTopLevelItem(topLevelItem);
                // укажем текст итема
            topLevelItem->setText(0,nameGroup[i]);
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
            qDebug() << flag;
            if(flag){
                foreach(int item, curList){
                    qDebug() << "item: " << item;
                    qDebug() << "index: " << index;
                    if(index != item){
                        flag = false;
                    }else{
                        flag = true;
                        break;
                    }
                }
            }
            qDebug() << flag;
            if(flag){
                QTreeWidgetItem *item=new QTreeWidgetItem(topLevels[figureList[index]->getGroupId()]);
                    // укажем текст итема
                item->setData(1, 0, index);
                item->setText(0,figureList[index]->itemName);
                qDebug() << item->data(1, 0).toInt();
            }
        }
    }
}

void CreateGroup::addButton(){
    int index = ui->AllTree->currentItem()->data(1, 0).toInt();
    figureList[index]->changeGroup(0, figureList[index]->getGroupName());
    Add.append(index);
    for(int i = 0; i < All.count(); ++i){
        if(All[i] == index){
            All.remove(i);
        }
    }

    ui->AllTree->clear();
    ui->AddTree->clear();

    createTree(All, ui->AllTree, group);
    createTree(Add, ui->AddTree, addGroup);
}

void CreateGroup::removeButton(){
    int index = ui->AddTree->currentItem()->data(1, 0).toInt();
    figureList[index]->cancelGroup();
    All.append(index);
    for(int i = 0; i < Add.count(); ++i){
        if(Add[i] == index){
            Add.remove(i);
        }
    }

    ui->AllTree->clear();
    ui->AddTree->clear();

    createTree(All, ui->AllTree, group);
    createTree(Add, ui->AddTree, addGroup);
}


void CreateGroup::okSlot(){
    foreach(int index, Add){
        figureList[index]->cancelGroup();
        figureList[index]->changeGroup(group.count(), ui->GroupName->text());
        qDebug() << "index in dialog: " << figureList[index]->getGroupId();
    }
    emit addGroupSignal(figureList, ui->GroupName->text());
}
