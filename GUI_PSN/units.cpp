#include "units.h"
#include "ui_units.h"
#include "Struck.h"

Units::Units(InitUnits init, int *order, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Units)
{
    ui->setupUi(this);
//    QStringList typeL = {"m", "cm", "mm"};
//    double coefL[3] = {1.0, 0.01, 0.001};
//    ui->Length->addItems(typeL);
//    for(int i = 0; i < 3; i++){
//        ui->Length->setItemData(i, coefL[i]);
//    }
//    QStringList typeP = {"V", "kV", "MV"};
//    double coefP[3] = {1.0, 1000.0, 1000000.0};
//    ui->Pot->addItems(typeP);
//    for(int i = 0; i < 3; i++){
//        ui->Pot->setItemData(i, coefP[i]);
//    }
//    QStringList typeM = {"T", "kG"};
//    double coefM[2] = {1.0, 0.1};
//    ui->MagInd->addItems(typeM);
//    for(int i = 0; i < 2; i++){
//        ui->MagInd->setItemData(i, coefM[i]);
//    }
//    QStringList typeT = {"s", "ms", "mcs", "ns"};
//    double coefT[4] = {1.0, 0.001, 0.000001, 0.000000001};
//    ui->Time->addItems(typeT);
//    for(int i = 0; i < 4; i++){
//        ui->Time->setItemData(i, coefT[i]);
//    }
//    QStringList typeCur = {"a/m*m", "ka/m*m"};
//    double coefCu[2] = {1.0, 1000};
//    ui->Curr->addItems(typeCur);
//    for(int i = 0; i < 2; i++){
//        ui->Curr->setItemData(i, coefCu[i]);
//    }
//    QStringList typeCh = {"C", "kC", "MC"};
//    double coefCh[3] = {1.0, 1000.0, 1000000.0};
//    ui->Char->addItems(typeCh);
//    for(int i = 0; i < 3; i++){
//        ui->Char->setItemData(i, coefCh[i]);
//    }
//    QStringList typeCon = {"S/m", "kS/m", "MS/m"};
//    double coefCon[3] = {1.0, 1000.0, 1000000.0};
//    ui->Cond->addItems(typeCon);
//    for(int i = 0; i < 3; i++){
//        ui->Cond->setItemData(i, coefCon[i]);
//    }
    QList<QComboBox *> box = ui->layoutWidget->findChildren<QComboBox *>(QString(), Qt::FindChildrenRecursively);
    for(int i = 0; i < box.size(); i++){
        box[i]->addItems(init.namelist[i]);
        for(int j = 0; j < init.namelist[i].size(); j++){
            box[i]->setItemData(j, init.coef[i][j]);
        }
    }
    for(int i = 0; i < box.size(); i++){
        box[i]->setCurrentIndex(order[i]);
    }
}

Units::~Units()
{
    delete ui;
}

void Units::passUnits(UnitsCoef *coef, int *order){
    coef->len = ui->Length->currentData().toDouble();
    coef->pot = ui->Pot->currentData().toDouble();
    coef->mag = ui->MagInd->currentData().toDouble();
    coef->time = ui->Time->currentData().toDouble();
    coef->curr = ui->Curr->currentData().toDouble();
    coef->ch = ui->Char->currentData().toDouble();
    coef->cond = ui->Cond->currentData().toDouble();

    QList<QComboBox *> box = ui->layoutWidget->findChildren<QComboBox *>(QString(), Qt::FindChildrenRecursively);
    for(int i = 0; i < box.size(); i++){
        order[i] = box[i]->currentIndex();
    }
}
