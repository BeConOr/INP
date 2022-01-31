#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "color.h"
#include "knife.h"
#include "knifeform.h"
#include "colorform.h"
#include <QDialog>
#include <QLabel>
#include "order.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->DelivCost->hide();
    ui->FeeCost->hide();
    ui->DolCost->hide();
    ui->ColorLib->hide();
    ui->BaseBTN->hide();
    dbname = QString("");

    db = new DataBase(dbname);
    db->connectToDataBase();

//    ui->Add_colorBTN->setDisabled(true);
//    ui->Add_knBTN->setDisabled(true);
//    ui->UploadBTN->setDisabled(true);
//    ui->CreateOrder->setDisabled(true);

    connect(ui->Add_colorBTN, &QPushButton::clicked, this, &MainWindow::openColor);
    connect(ui->Add_knBTN, &QPushButton::clicked, this, &MainWindow::openKnife);
    connect(ui->CreateOrder, &QPushButton::clicked, this, &MainWindow::createOrder);
    connect(ui->UploadBTN, &QPushButton::clicked, this, &MainWindow::setKnifeList);
//    connect(ui->UploadBTN, &QPushButton::clicked, this, &MainWindow::setColorList);
    connect(ui->DelivCheck, &QCheckBox::clicked, this, &MainWindow::delivChk);
    connect(ui->FeeCheck, &QCheckBox::clicked, this, &MainWindow::feeChk);
    connect(ui->DolCheck, &QCheckBox::clicked, this, &MainWindow::dolChk);
//    connect(ui->BaseBTN, &QPushButton::clicked, this, &MainWindow::openDB);

//    setKnifeList();
//    setColorList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openColor(){
    Color *Dialog = new Color(dbname);
    Dialog->show();
    Dialog->exec();

//    setKnifeList();
//    setColorList();
}

void MainWindow::openKnife(){
    Knife *Dialog = new Knife(dbname);
    Dialog->show();
    Dialog->exec();

//    setKnifeList();
}

void MainWindow::setKnifeList(){
    if(ui->KnifeScroll->findChildren<KnifeForm *>().count() != 0){
        foreach(KnifeForm *form, ui->KnifeScroll->findChildren<KnifeForm *>()){
            form->deleteLater();
        }
    }
    if(ui->KnifeScroll->findChildren<QGridLayout *>().count() != 0){
        foreach(QGridLayout *form, ui->KnifeScroll->findChildren<QGridLayout *>()){
            form->deleteLater();
        }
    }
//    ui->KnifeScroll->findChild<QGridLayout *>()->deleteLater();
    QList<Kn> knifes = db->selectKnife();
    QList<Co> colors = db->selectColor();
    QWidget *w = new QWidget(ui->KnifeScroll);
    ui->KnifeScroll->setWidget(w);
    QGridLayout *vbox = new QGridLayout(w);
    w->setLayout(vbox);
    for(int i = 0; i < qCeil((double)knifes.count()/3.0); ++i){
        for(int j = 0; j < 3; ++j){
            if((3*i+j) < knifes.count()){
                KnifeForm *form = new KnifeForm(dbname, knifes[3*i+j], colors, ui->KnifeScroll);
                vbox->addWidget(form, i, j);
            }
        }
    }
}

void MainWindow::setColorList(){
    if(ui->ColorScroll->findChildren<ColorForm *>().count() != 0){
        foreach(ColorForm *form, ui->ColorScroll->findChildren<ColorForm *>()){
            form->deleteLater();
        }
    }
    if(ui->ColorScroll->findChildren<QVBoxLayout *>().count() != 0){
        foreach(QVBoxLayout *form, ui->ColorScroll->findChildren<QVBoxLayout *>()){
            form->deleteLater();
        }
    }
//    ui->ColorScroll->findChild<QVBoxLayout *>()->deleteLater();
    QList<Co> colors = db->selectColor();
    QWidget *w = new QWidget(ui->ColorScroll);
    ui->ColorScroll->setWidget(w);
    QVBoxLayout *vbox = new QVBoxLayout(w);
    w->setLayout(vbox);
    for(int i = 0; i < colors.count(); ++i){
        ColorForm *form = new ColorForm(dbname, colors[i], ui->ColorScroll);
        vbox->addWidget(form);
    }
}

void MainWindow::createOrder(){
    if(ui->KnifeScroll->findChildren<KnifeForm *>().count() != 0){
        QString all = QString("");
        double cost = 0.0;
        foreach(KnifeForm *form, ui->KnifeScroll->findChildren<KnifeForm *>()){
            QVariantList inform = form->recieveInf(!ui->DolCheck->isChecked());
            if(!inform[0].toString().isEmpty()){
                if(!ui->DolCheck->isChecked()){
                    all += inform[0].toString() + QString(" - %1 руб.\n").arg(inform[1].toDouble());
                }else{
                    all += inform[0].toString() + QString(" - $%1\n").arg(inform[1].toDouble()/ui->DolCost->value());
                }
                cost += inform[1].toDouble();
            }
        }
        if(ui->DelivCheck->isChecked()){
            if(!ui->DolCheck->isChecked()){
                all += QString("Доставка: %1 руб.\n").arg(ui->DelivCost->value());
            }else{
                all += QString("Delivery: $%1\n").arg(ui->DelivCost->value()/ui->DolCost->value());
            }
            cost += ui->DelivCost->value();
        }
        if(ui->FeeCheck->isChecked()){
            double prc = 1.0 - ui->FeeCost->value()/100.0;
            double comm = cost*((1.0/prc)-1);
            if(!ui->DolCheck->isChecked()){
                all += QString("Комиссия PayPal: %1 руб.\n").arg(comm);
            }else{
                all += QString("PayPal commission fee: $%1\n").arg(comm/ui->DolCost->value());
            }
            cost += comm;
        }
        all += QString("----------------------------------\n");
        if(!ui->DolCheck->isChecked()){
            all += QString("Всего: %1 руб.").arg(cost);
        }else{
            all += QString("Total: $%1").arg(cost/ui->DolCost->value());
        }

        Order *dial = new Order(all, this);
        dial->exec();
    }
}

void MainWindow::delivChk(){
    if(ui->DelivCheck->isChecked()){
        ui->DelivCost->show();
    }else{
        ui->DelivCost->hide();
    }
}

void MainWindow::feeChk(){
    if(ui->FeeCheck->isChecked()){
        ui->FeeCost->show();
    }else{
        ui->FeeCost->hide();
    }
}

void MainWindow::dolChk(){
    if(ui->DolCheck->isChecked()){
        ui->DolCost->show();
    }else{
        ui->DolCost->hide();
    }
}

void MainWindow::openDB(){
    dbname = QFileDialog::getOpenFileName(this, tr("Открыть базу данных"), "", tr("DataBase (*.db);;All Files (*)"));
    db = new DataBase(dbname);
    db->connectToDataBase();

    ui->Add_colorBTN->setDisabled(false);
    ui->Add_knBTN->setDisabled(false);
    ui->UploadBTN->setDisabled(false);
    ui->CreateOrder->setDisabled(false);
}
