#include "circ_wid.h"
#include "ui_circ_wid.h"

Circ_wid::Circ_wid(QPointF start, QPointF end, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Circ_wid)
{
    ui->setupUi(this);
    qreal x = end.x()-start.x();
    qreal y = -(end.y()-start.y());
    qreal radius = qSqrt(x*x+y*y);
    ui->Cent_x->setValue(start.x());
    ui->Cent_y->setValue(-start.y());
    ui->Radius->setValue(radius);
    connect(ui->Button_ok, &QPushButton::clicked, this, &Circ_wid::emOK);
    connect(ui->Button_canc, &QPushButton::clicked, this, &Circ_wid::emCanc);
}

Circ_wid::~Circ_wid()
{
    delete ui;
}

void Circ_wid::setA(QPointF start, QPointF end){
    qreal x = end.x()-start.x();
    qreal y = -(end.y()-start.y());
    qreal radius = qSqrt(x*x+y*y);
    ui->Cent_x->setValue(start.x());
    ui->Cent_y->setValue(-start.y());
    ui->Radius->setValue(radius);
}

void Circ_wid::emOK(){
    qreal start_x = ui->Cent_x->value();
    qreal start_y = -ui->Cent_y->value();
    qreal end_x;
    qreal end_y;
    end_x = ui->Radius->value();
    end_y = ui->Radius->value();
    QPointF start(start_x, start_y);
    QPointF end(end_x, end_y);
    emit OK(start, end);
    this->deleteLater();
}

void Circ_wid::emCanc(){
    emit Canc();
}


