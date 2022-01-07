#include "order.h"
#include "ui_order.h"
#include <QClipboard>
#include <QMessageBox>

Order::Order(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Order)
{
    ui->setupUi(this);

    ui->label->setText(text);

    connect(ui->pushButton, &QPushButton::clicked, this, &Order::copy);
}

Order::~Order()
{
    delete ui;
}

void Order::copy(){
    if(QClipboard *c = QApplication::clipboard()){
        c->setText(ui->label->text());
    }

    QMessageBox msgBox;
    msgBox.setText(tr("Текст скопирован."));
    msgBox.exec();
}
