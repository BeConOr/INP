#include "knifeform.h"
#include "ui_knifeform.h"
#include <QMessageBox>
#include "colnumber.h"
#include <QDialog>
#include <QRegularExpression>
#include "knife.h"

KnifeForm::KnifeForm(QString dbname, Kn inf, QList<Co> colors, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KnifeForm)
{
    ui->setupUi(this);
    db = new DataBase(dbname);
//    db->connectToDataBase();

    inform = inf;

    dbn = dbname;

    ui->Name->setText(inform.rus);
    if(!inform.img.isEmpty()){
        QPixmap inPixmap;
        inPixmap.loadFromData(inform.img,inform.imgName.mid(inform.imgName.lastIndexOf('.')).toLatin1());
        ui->Image_place->setPixmap(inPixmap.scaled(QSize(200, 200), Qt::KeepAspectRatio));
    }else{
        ui->Image_place->hide();
    }

    connect(ui->delBTN, &QPushButton::clicked, this, &KnifeForm::deleteBTN);
    connect(ui->enlBTN, &QPushButton::clicked, this, &KnifeForm::enlargeBTN);
    connect(ui->openList, &QPushButton::clicked, this, &KnifeForm::openBTN);
    connect(ui->editBTN, &QPushButton::clicked, this, &KnifeForm::editBTN);

    ui->Numbers->hide();
    ui->scrollArea->hide();

    if(inform.isKnife){
//        ui->Numbers->hide();
//        ui->scrollArea->show();
//        QList<Co> colors = db->selectColor();
        QWidget *w = new QWidget(ui->scrollArea);
        ui->scrollArea->setWidget(w);
        QVBoxLayout *vbox = new QVBoxLayout(w);
        w->setLayout(vbox);
        for(int i = 0; i < colors.count(); ++i){
            ColNumber *color_pan = new ColNumber(colors[i].rus, colors[i].number, ui->scrollArea);
            vbox->addWidget(color_pan);
        }
    }else{
//        ui->Numbers->show();
//        ui->scrollArea->hide();
        if(ui->scrollArea->findChildren<ColNumber *>().count() != 0){
            foreach(ColNumber* child, ui->scrollArea->findChildren<ColNumber *>()){
                child->deleteLater();
            }
        }
        if(ui->scrollArea->findChildren<QVBoxLayout *>().count() != 0){
            foreach(QVBoxLayout* child, ui->scrollArea->findChildren<QVBoxLayout *>()){
                child->deleteLater();
            }
        }
//        ui->scrollArea->findChild<QVBoxLayout *>()->deleteLater();
    }
}

KnifeForm::~KnifeForm()
{
    delete ui;
}

void KnifeForm::deleteBTN(){
    if(QMessageBox::Yes == QMessageBox::question(this, "Внимание.", "Удалить нож?", QMessageBox::Yes | QMessageBox::No)){
        db->connectToDataBase();
        db->deleteKn(inform.id);
    }
}

void KnifeForm::enlargeBTN(){
    db->connectToDataBase();
    QByteArray img = db->getLowKnife(inform.id);
    if(!img.isNull()){
        QDialog *dial = new QDialog(this);
        QLabel *imgPlace = new QLabel();
        QVBoxLayout *vbox = new QVBoxLayout();
        dial->setLayout(vbox);
        dial->setWindowTitle(inform.rus);
        vbox->addWidget(imgPlace);
        QPixmap inPixmap;
        inPixmap.loadFromData(img,inform.imgName.mid(inform.imgName.lastIndexOf('.')).toLatin1());
        imgPlace->setPixmap(inPixmap.scaled(QSize(600, 600), Qt::KeepAspectRatio));
        dial->exec();
    }
}

QVariantList KnifeForm::recieveInf(bool engFlag){
    QVariantList data;
    QString str = QString("");
    double cost = 0.0;
    if(inform.isKnife == 1){
        QStringList nameCol = inform.colHigh.split(QString(","));
        QStringList nameCos = inform.cosHigh.split(QString(","));
        foreach(ColNumber *numb, ui->scrollArea->findChildren<ColNumber *>()){
//            double currCost = 0.0;
            if(!numb->colorN().isEmpty()){
                str += QString("№%1").arg(numb->number());
                QStringList parCol = numb->colorN().split(QString(" - "));
                QString name = parCol[0];
                str += QString(" - ") + parCol[1];
                double skol = parCol[1].toDouble();
                bool flag = true;
                for(int i = 0; i < nameCol.count()-1; ++i){
                    if(name == nameCol[i]){
                        cost += (skol*nameCos[i].toDouble());
//                        currCost += (skol*nameCos[i].toDouble());
                        flag = false;
                        break;
                    }
                }
                if(flag){
                    cost += (skol*inform.cost);
//                    currCost += (skol*inform.cost);
                }
            }
            if(!numb->colorN().isEmpty()){
//                str += QString(" шт. (%1 руб.);\n").arg(currCost);
                if(engFlag){
                    str += QString(" шт.; ");
                }else{
                    str += QString(" pc.; ");
                }
            }
        }
        if(!str.isEmpty()){
            if(engFlag){
                str = inform.rus + QString(" (%1)").arg(str);
            }else{
                str = inform.eng + QString(" (%1)").arg(str);
            }
        }
    }else{
        if(ui->Numbers->value() != 0){
            cost += ui->Numbers->value()*inform.cost;
            if(engFlag){
                str += inform.rus + QString(" %1 шт.").arg(ui->Numbers->value());
            }else{
                str += inform.eng + QString(" %1 pc.").arg(ui->Numbers->value());
            }
        }
    }
    data.append(str);
    data.append(cost);
    return data;
}

void KnifeForm::openBTN(){
    openFlag = !openFlag;
    if(openFlag){
        if(inform.isKnife){
            ui->Numbers->hide();
            ui->scrollArea->show();
            ui->Image_place->hide();
        }else{
            ui->Numbers->show();
            ui->scrollArea->hide();
        }
    }else{
        ui->Numbers->hide();
        ui->scrollArea->hide();
        if(!inform.img.isEmpty()){
            ui->Image_place->show();
        }
    }
}

void KnifeForm::editBTN(){
    Knife *Dialog = new Knife(dbn, inform.id);
    Dialog->show();
    Dialog->exec();
}
