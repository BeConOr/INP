#include "figurename.h"
#include "ui_figurename.h"

FigureName::FigureName(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FigureName)
{
    ui->setupUi(this);
}

FigureName::~FigureName()
{
    delete ui;
}

QString FigureName::getName(){
    return ui->FigName->text();
}
