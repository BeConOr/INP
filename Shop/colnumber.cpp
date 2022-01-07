#include "colnumber.h"
#include "ui_colnumber.h"

ColNumber::ColNumber(QString name, int number, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColNumber)
{
    ui->setupUi(this);

    colorName = name + QString(" (%1)").arg(number);
    colorNumber = number;

    ui->checkBox->setText(QString("№%1").arg(number));
    ui->spinBox->setDisabled(true);
    connect(ui->checkBox, &QCheckBox::clicked, this, &ColNumber::chk);
}

ColNumber::~ColNumber()
{
    delete ui;
}

void ColNumber::chk(){
    ui->spinBox->setDisabled(!ui->checkBox->isChecked());
}

QString ColNumber::colorN(){
    if(ui->checkBox->isChecked()){
        return colorName + tr(" - %1").arg(ui->spinBox->value());
    }else{
        return QString("");
    }
}

int ColNumber::number(){
    return colorNumber;
}
