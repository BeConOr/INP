#include "arc_wid.h"
#include "ui_arc_wid.h"
#include <math.h>

Arc_wid::Arc_wid(QPointF start, QPointF angles, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Arc_wid)
{
    ui->setupUi(this);

    qreal x = angles.x()-start.x();
    qreal y = -(angles.y()-start.y());
    qreal radius = qSqrt(x*x+y*y);
    double startAngle = atan2(y, x) * 180.0/M_PI;
    double endAngle = startAngle + 30.0;

    ui->Cent_x->setValue(start.x());
    ui->Cent_y->setValue(-start.y());
    ui->StAng->setValue(startAngle);
    ui->EnAng->setValue(endAngle);
    ui->Radius->setValue(radius);

    connect(ui->OK, &QPushButton::clicked, this, &Arc_wid::emOK);
    connect(ui->Cancel, &QPushButton::clicked, this, &Arc_wid::emCanc);
}

Arc_wid::~Arc_wid()
{
    delete ui;
}

void Arc_wid::emOK(){
    qreal start_x = ui->Cent_x->value();
    qreal start_y = -ui->Cent_y->value();
    double radius;
    radius = ui->Radius->value();
    qreal st = ui->StAng->value();
    qreal en = ui->EnAng->value();
    QPointF start(start_x, start_y);
    QPointF angles(st, en);
    emit OK(start, radius, angles);
    this->deleteLater();
}

void Arc_wid::emCanc(){
    emit Canc();
}

void Arc_wid::setA(QPointF start, QPointF angles){
    qreal x = angles.x()-start.x();
    qreal y = -(angles.y()-start.y());
    qreal radius = qSqrt(x*x+y*y);
    double startAngle = atan2(y, x) * 180.0/M_PI;

    if(startAngle >= 0){
        ui->StAng->setValue(startAngle);
        double endAngle = startAngle + 30.0;
        ui->EnAng->setValue(endAngle);
    }
    else{
        ui->StAng->setValue(360.0 + startAngle);
        double endAngle = 360.0 + startAngle + 30.0;
        ui->EnAng->setValue(endAngle);
    }
    ui->Cent_x->setValue(start.x());
    ui->Cent_y->setValue(-start.y());
    ui->Radius->setValue(radius);
}
