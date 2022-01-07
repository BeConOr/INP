#include "elip_wid.h"
#include "ui_elip_wid.h"

Elip_wid::Elip_wid(QPointF start, QPointF end, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Elip_wid)
{
    ui->setupUi(this);
    qreal x = qAbs(end.x()-start.x());
    qreal y = qAbs(-(end.y()-start.y()));
    //qreal radius = qSqrt(x*x+y*y);
    ui->Cent_x->setValue(start.x());
    ui->Cent_y->setValue(-start.y());
    ui->Axis_a->setValue(x);
    ui->Axis_b->setValue(y);
    connect(ui->Button_ok, &QPushButton::clicked, this, &Elip_wid::emOK);
    connect(ui->Button_canc, &QPushButton::clicked, this, &Elip_wid::emCanc);
}

Elip_wid::~Elip_wid()
{
    delete ui;
}

void Elip_wid::setA(QPointF start, QPointF end){
    qreal x = qAbs(end.x()-start.x());
    qreal y = qAbs(-(end.y()-start.y()));
    //qreal radius = qSqrt(x*x+y*y);
    ui->Cent_x->setValue(start.x());
    ui->Cent_y->setValue(-start.y());
    ui->Axis_a->setValue(x);
    ui->Axis_b->setValue(y);
}

void Elip_wid::emOK(){
    qreal start_x = ui->Cent_x->value();
    qreal start_y = -ui->Cent_y->value();
    qreal end_x;
    qreal end_y;
    end_x = ui->Axis_a->value();
    end_y = ui->Axis_b->value();
    QPointF start(start_x, start_y);
    QPointF end(end_x, end_y);
    emit OK(start, end);
    this->deleteLater();
}

void Elip_wid::emCanc(){
    emit Canc();
}

