#include "arc_wid.h"
#include "ui_arc_wid.h"

Arc_wid::Arc_wid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Arc_wid)
{
    ui->setupUi(this);
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
    int radius;
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
