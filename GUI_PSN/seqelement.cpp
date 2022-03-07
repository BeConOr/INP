#include "seqelement.h"
#include "ui_seqelement.h"

SeqElement::SeqElement(QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeqElement)
{
    ui->setupUi(this);
    ui->label->setText(name);
}

SeqElement::~SeqElement()
{
    delete ui;
}

SeqCond SeqElement::giveCond(){
    return (SeqCond){ui->doubleSpinBox->value(), ui->spinBox->value()};
}
