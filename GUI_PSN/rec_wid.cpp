#include "rec_wid.h"
#include "ui_rec_wid.h"

Rec_wid::Rec_wid(QPointF start, QPointF end, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rec_wid)
{
    ui->setupUi(this);
    ui->Start_x->setValue(start.x());
    ui->Start_y->setValue(-start.y());
    ui->End_x->setValue(end.x());
    ui->End_y->setValue(-end.y());
    qreal y = (-end.y()+start.y());
    qreal x = (end.x()-start.x());
    ui->Angle->setValue(qAtan2(y,x)*180.0/M_PI);
    ui->Length->setValue(qSqrt(y*y+x*x));
    connect(ui->Button_ok, &QPushButton::clicked, this, &Rec_wid::emOK);
    connect(ui->Button_canc, &QPushButton::clicked, this, &Rec_wid::emCanc);
    connect(ui->checkBox, &QCheckBox::clicked, this, &Rec_wid::slotCheck);
}

Rec_wid::~Rec_wid()
{
    delete ui;
}

void Rec_wid::setA(QPointF start, QPointF end){
    ui->Start_x->setValue(start.x());
    ui->Start_y->setValue(-start.y());
    ui->End_x->setValue(end.x());
    ui->End_y->setValue(-end.y());
    qreal y = (-end.y()+start.y());
    qreal x = (end.x()-start.x());
    ui->Angle->setValue(qAtan2(y,x)*180.0/M_PI);
    ui->Length->setValue(qSqrt(y*y+x*x));
}

void Rec_wid::emOK(){
    qreal start_x = ui->Start_x->value();
    qreal start_y = -ui->Start_y->value();
    qreal end_x;
    qreal end_y;
    if(ui->checkBox->isChecked()){
        end_x = ui->Length->value();
        end_y = ui->Angle->value();
    }else{
        end_x = ui->End_x->value();
        end_y = -ui->End_y->value();
    }
    QPointF start(start_x, start_y);
    QPointF end(end_x, end_y);
    emit OK(start, end, ui->checkBox->isChecked());
    this->deleteLater();
}

void Rec_wid::emCanc(){
    emit Canc();
}

void Rec_wid::slotCheck(){
    if(ui->checkBox->isChecked()){
        ui->checkBox->setText(QString("Parameters"));
        ui->End_x->setDisabled(true);
        ui->End_y->setDisabled(true);
        ui->Length->setDisabled(false);
        ui->Angle->setDisabled(false);
    }else{
        ui->checkBox->setText(QString("End Point"));
        ui->End_x->setDisabled(false);
        ui->End_y->setDisabled(false);
        ui->Length->setDisabled(true);
        ui->Angle->setDisabled(true);
    }
}
