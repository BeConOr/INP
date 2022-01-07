#include "colorform.h"
#include "ui_colorform.h"
#include <QMessageBox>
#include <QDialog>

ColorForm::ColorForm(QString dbname, Co inf, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorForm)
{
    ui->setupUi(this);
    db = new DataBase(dbname);
//    db->connectToDataBase();

    inform = inf;

    ui->Name->setText(inform.rus);
    ui->Number->setText(QString("%1").arg(inform.number));
    QPixmap inPixmap;
    inPixmap.loadFromData(inform.img,inform.imgName.mid(inform.imgName.lastIndexOf('.')).toLatin1());
    ui->Image_place->setPixmap(inPixmap.scaled(QSize(300, 300), Qt::KeepAspectRatio));

    connect(ui->DeleteBTN, &QPushButton::clicked, this, &ColorForm::deleteBTN);
    connect(ui->EnlargeBTN, &QPushButton::clicked, this, &ColorForm::enlargeBTN);
}

ColorForm::~ColorForm()
{
    delete ui;
}

void ColorForm::deleteBTN(){
    if(QMessageBox::Yes == QMessageBox::question(this, "Внимание.", "Удалить цвет?", QMessageBox::Yes | QMessageBox::No)){
        db->connectToDataBase();
        db->deleteCo(inform.id);
    }
}

void ColorForm::enlargeBTN(){
    QDialog *dial = new QDialog(this);
    QLabel *imgPlace = new QLabel();
    QVBoxLayout *vbox = new QVBoxLayout();
    dial->setLayout(vbox);
    dial->setWindowTitle(inform.rus);
    vbox->addWidget(imgPlace);
    QPixmap inPixmap;
    inPixmap.loadFromData(inform.img,inform.imgName.mid(inform.imgName.lastIndexOf('.')).toLatin1());
    imgPlace->setPixmap(inPixmap.scaled(QSize(600, 600), Qt::KeepAspectRatio));
    dial->exec();
}
