#include "seqelement.h"
#include "ui_seqelement.h"

SeqElement::SeqElement(QString name, SeqCond curr, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeqElement)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->doubleSpinBox->setValue(curr.coord);
    ui->spinBox->setValue(curr.seqNumb);
    connect(ui->pushButton, &QPushButton::clicked, this, &SeqElement::delBTN);
}

SeqElement::~SeqElement()
{
    delete ui;
}

SeqCond SeqElement::giveCond(){
    return (SeqCond){ui->doubleSpinBox->value(), ui->spinBox->value()};
}

void SeqElement::delBTN(){
    emit deleteSignals();
    delete(this);
}
