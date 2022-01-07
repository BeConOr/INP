#include "color.h"
#include "ui_color.h"
#include <QMessageBox>
#include <QDir>
#include <QBuffer>
#include <QFileDialog>
#include <QMessageBox>

Color::Color(QString dbname, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Color)
{
    ui->setupUi(this);
    db = new DataBase(dbname);
    db->connectToDataBase();
    connect(ui->ImageBTN, &QPushButton::clicked, this, &Color::open);
    connect(ui->OkBTN, &QPushButton::clicked, this, &Color::OK_slot);
}

Color::~Color()
{
    delete ui;
}

void Color::loadFile(const QString &fileName)
//! [42] //! [43]
{
    QString res = fileName.mid(fileName.indexOf(QString("."))+1);
    QPixmap inPixmap(fileName);      // Сохраняем его в изображение объекта QPixmap                             // Создаём объект QByteArray для сохранения изображения
    QBuffer inBuffer(&inByteArray);                   // Сохранение изображения производим через буффер
    inBuffer.open( QIODevice::WriteOnly );              // Открываем буффер
    inPixmap.save(&inBuffer, res.toLatin1());
    ui->Image_place->setPixmap(inPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
}

void Color::open()
//! [7] //! [8]
{
    fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void Color::OK_slot(){
    QVariantList data;
    data.append(ui->Rus_name->text());
    data.append(fileName.mid(fileName.lastIndexOf(QString("//"))+1));
    data.append(inByteArray);
    data.append(ui->ColorNumb->value());

    db->insertIntoColor(data);

    QMessageBox msgBox;
    msgBox.setText(tr("Добавлен новый цвет: %1.").arg(ui->Rus_name->text()));
    msgBox.exec();
    ui->Rus_name->clear();
    ui->Image_place->clear();
    ui->ColorNumb->setValue(0);
}
