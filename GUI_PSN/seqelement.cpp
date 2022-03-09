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
    if(nextEl != NULL){
        nextEl->setName(ui->label->text());
        nextEl->setLastEl(lastEl);
    }
    if(lastEl != NULL){
        lastEl->setNextEl(nextEl);
    }
    emit deleteSignals(lastEl);
//    emit newNameSignals(ui->label->text());
    delete(this);
}

void SeqElement::changeName(QString newName){
    ui->label->setText(newName);
    emit newNameSignals(tr("%1%2").arg(newName[0]).arg(newName.mid(1).toInt()+1));
}

void SeqElement::setNextEl(SeqElement* el){
    nextEl = el;
}

void SeqElement::setLastEl(SeqElement *el){
    lastEl = el;
}

void SeqElement::setName(QString newName){
    ui->label->setText(newName);
    if(nextEl != NULL){
        nextEl->setName(tr("%1%2").arg(newName[0]).arg(newName.mid(1).toInt()+1));
    }
}

SeqElement* SeqElement::getNextEl(){
    return nextEl;
}
