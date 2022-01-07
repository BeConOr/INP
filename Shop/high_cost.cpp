#include "high_cost.h"
#include "ui_high_cost.h"

High_cost::High_cost(QString name, QWidget *parent, double cost) :
    QWidget(parent),
    ui(new Ui::High_cost)
{
    ui->setupUi(this);
    ui->checkBox->setText(name);
    ui->Cost->setValue(cost);
    ui->checkBox->setChecked((cost - 0.0) > 0.001);
}

High_cost::~High_cost()
{
    delete ui;
}

QVariantList High_cost::getParam(){
    QVariantList data;
    data.append(ui->checkBox->text());
    data.append(ui->Cost->value());
    qDebug() << ui->checkBox->text() << ui->Cost->value();
    return data;
}

bool High_cost::chk(){
    return ui->checkBox->isChecked();
}
