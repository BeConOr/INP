#include "order.h"
#include "ui_order.h"
#include <QClipboard>
#include <QMessageBox>
#include <QFileDialog>

Order::Order(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Order)
{
    ui->setupUi(this);

    ui->label->setText(text);

    ui->label->setWordWrap(true);

    connect(ui->pushButton, &QPushButton::clicked, this, &Order::copy);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Order::saveBTN);
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

void Order::saveBTN(){
    QFileDialog dialog(this, tr("Open File"), "/Заказ", tr("Work file (*.txt)"));
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() == QDialog::Accepted){
        QString fName = dialog.selectedFiles().first();
        QString fileN = fName.mid(0, fName.indexOf(".", 0));
        QFile file(fileN + ".txt");
        file.open(QFile::WriteOnly | QFile::Text);
        QTextStream out(&file);
        out << ui->label->text();
        file.close();
    }
}
