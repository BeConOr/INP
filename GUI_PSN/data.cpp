#include "data.h"
#include "ui_data.h"
#include <string>
#include "Struck.h"

using namespace std;

Data::Data(InitData init, StartData str, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Data)
{
    ui->setupUi(this);
    connect(ui->Ok_butt, SIGNAL(clicked()), this, SLOT(passParam()));
    connect(ui->MeshQ, SIGNAL(clicked()), this, SLOT(MeshQ()));
    connect(ui->MeshE, SIGNAL(clicked()), this, SLOT(MeshE()));
    connect(ui->MeshH, SIGNAL(clicked()), this, SLOT(MeshH()));
    //
    ui->TypeTask->addItems(init.typeT);
    ui->GeomT->addItems(init.geomT);
    ui->Matrix->addItems(init.meshArr);
    ui->Field->addItems(init.meshArr);
    ui->Trace->addItems(init.meshArr);
    //Set initial value
    ui->TypeTask->setCurrentIndex(str.typeT);
    ui->GeomT->setCurrentIndex(str.geomT);
    ui->Matrix->setCurrentIndex(str.matrix);
    ui->Field->setCurrentIndex(str.field);
    ui->Trace->setCurrentIndex(str.trace);
    ui->MeshQ->setChecked(str.Q);
    ui->MeshE->setChecked(str.E);
    ui->MeshH->setChecked(str.H);
    ui->StreamL->setValue(str.stream);
    ui->Step->setValue(str.step);
    ui->Numb->setValue(str.numb);
    ui->Umax->setValue(str.umax);
    ui->Umin->setValue(str.umin);
    if(str.Q){ui->MeshQ->setText("Yes");}
    if(str.E){ui->MeshE->setText("Yes");}
    if(str.H){ui->MeshH->setText("Yes");}

    str.copy(&pass);
}

Data::~Data()
{
    delete ui;
}

void Data::passParam(){
    pass = {ui->TypeTask->currentIndex(),
                           ui->GeomT->currentIndex(),
                           ui->Matrix->currentIndex(),
                           ui->Field->currentIndex(),
                           ui->Trace->currentIndex(),
                           ui->MeshQ->isChecked(),
                           ui->MeshE->isChecked(),
                           ui->MeshH->isChecked(),
                           ui->StreamL->value(),
                           ui->Step->value(),
                           ui->Numb->value(),
                           ui->Umin->value(),
                          ui->Umax->value()};
}

StartData Data::getPar(){
    return pass;
}

void Data::MeshQ(){
    if(ui->MeshQ->isChecked()){
        ui->MeshQ->setText("Yes");
    }
    else{
        ui->MeshQ->setText("No");
    }
}

void Data::MeshE(){
    if(ui->MeshE->isChecked()){
        ui->MeshE->setText("Yes");
    }
    else{
        ui->MeshE->setText("No");
    }
}

void Data::MeshH(){
    if(ui->MeshH->isChecked()){
        ui->MeshH->setText("Yes");
    }
    else{
        ui->MeshH->setText("No");
    }
}
