#include "knife.h"
#include "ui_knife.h"
#include <QMessageBox>
#include <QDir>
#include <QBuffer>
#include <QFileDialog>
#include <QMessageBox>
#include "high_cost.h"

Knife::Knife(QString dbname, int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Knife)
{
    ui->setupUi(this);

    db = new DataBase(dbname);
    db->connectToDataBase();

    kid = id;

    ui->scrollArea->hide();

    connect(ui->ImageBTN, &QPushButton::clicked, this, &Knife::open);
    connect(ui->OkBTN, &QPushButton::clicked, this, &Knife::OK_slot);

    connect(ui->checkBox, &QCheckBox::clicked, this, &Knife::check);
    connect(ui->KnifeCheck, &QCheckBox::clicked, this, &Knife::knCheck);

    if(kid != 0){
        Kn data = db->selectK(kid);
        ui->Rus_name->setText(data.rus);
        ui->Eng_name->setText(data.eng);
        if(!data.img.isEmpty()){
            QPixmap inPixmap;
            inPixmap.loadFromData(data.img,data.imgName.mid(data.imgName.lastIndexOf('.')).toLatin1());
            ui->Image_place->setPixmap(inPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
        }
        ui->doubleSpinBox->setValue(data.cost);
        if(data.isKnife == 0){
            ui->KnifeCheck->setChecked(false);
            ui->KnifeCheck->setText(tr("Набор"));
            ui->checkBox->setDisabled(true);
        }else{
            QStringList nameCol = data.colHigh.split(QString(","));
            QStringList nameCos = data.cosHigh.split(QString(","));
            set(nameCol, nameCos);
        }
    }
}

Knife::~Knife()
{
    delete ui;
}

void Knife::loadFile(const QString &fileName)
//! [42] //! [43]
{
    QString res = fileName.mid(fileName.indexOf(QString("."))+1);
    QPixmap inPixmap(fileName);      // Сохраняем его в изображение объекта QPixmap                             // Создаём объект QByteArray для сохранения изображения
    QBuffer inBuffer(&inByteArray);                   // Сохранение изображения производим через буффер
    inBuffer.open( QIODevice::WriteOnly );              // Открываем буффер
    inPixmap.save(&inBuffer, res.toLatin1());
    QPixmap lowPixmap = inPixmap.scaled(QSize(200, 200), Qt::KeepAspectRatio);
    ui->Image_place->setPixmap(inPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
    QBuffer lowBuffer(&lowByteArray);
    lowBuffer.open( QIODevice::WriteOnly );
    lowPixmap.save(&lowBuffer, res.toLatin1());
}

void Knife::open()
//! [7] //! [8]
{
    fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void Knife::OK_slot(){
    QVariantList data;
    data.append(ui->Rus_name->text());
    data.append(ui->Eng_name->text());
    QString colA;
    QString cosA;
    if(ui->checkBox->isChecked()){
        foreach(High_cost *widg, ui->scrollArea->findChildren<High_cost *>()){
            if(widg->chk()){
                QVariantList arr = widg->getParam();
                QString text = arr[0].toString();
                double cost = arr[1].toDouble();
                qDebug() << text << cost;
                colA += QString("%1,").arg(text);
                cosA += QString("%1,").arg(cost);
            }
        }
    }
    data.append(colA);
    data.append(cosA);
    data.append(fileName.mid(fileName.lastIndexOf(QString("/"))+1));
    data.append(inByteArray);
    data.append(ui->doubleSpinBox->value());
    data.append(ui->KnifeCheck->isChecked());
    data.append(lowByteArray);

    if(kid == 0){
        db->insertIntoKnife(data);

        QMessageBox msgBox;
        msgBox.setText(tr("Добавлен новый нож: %1.").arg(ui->Rus_name->text()));
        msgBox.exec();
        ui->Rus_name->clear();
        ui->Eng_name->clear();
        ui->doubleSpinBox->setValue(0.0);
        ui->Image_place->clear();
        ui->KnifeCheck->setChecked(true);
        knCheck();
    }else{
        db->updateKnife(data, kid);

        QMessageBox msgBox;
        msgBox.setText(tr("Обнавлена информация о ноже: %1.").arg(ui->Rus_name->text()));
        msgBox.exec();
        ui->Rus_name->clear();
        ui->Eng_name->clear();
        ui->doubleSpinBox->setValue(0.0);
        ui->Image_place->clear();
        ui->KnifeCheck->setChecked(true);
        knCheck();
    }
}

void Knife::check(){
    if(ui->checkBox->isChecked()){
        ui->scrollArea->show();
        QList<Co> colors = db->selectColor();
        QWidget *w = new QWidget(ui->scrollArea);
        ui->scrollArea->setWidget(w);
        QVBoxLayout *vbox = new QVBoxLayout(w);
        w->setLayout(vbox);
        for(int i = 0; i < colors.count(); ++i){
            High_cost *color_pan = new High_cost(colors[i].rus + QString(" (%1)").arg(colors[i].number), ui->scrollArea);
//            QHBoxLayout *color_pan = new QHBoxLayout(ui->listWidget);
//            color_pan->setSpacing(1);
//            QCheckBox *check_color = new QCheckBox(QString(""), ui->listWidget);
//            QLabel *name_col = new QLabel(colors[i].rus, ui->listWidget);
//            QDoubleSpinBox *cos_col = new QDoubleSpinBox(ui->listWidget);
//            cos_col->setMaximum(10000.0);
//            color_pan->addWidget(check_color);
//            color_pan->addWidget(name_col);
//            color_pan->addWidget(cos_col);
            vbox->addWidget(color_pan);
        }
    }else{
        ui->scrollArea->hide();
        if(ui->scrollArea->findChildren<High_cost *>().count() != 0){
            foreach(High_cost* child, ui->scrollArea->findChildren<High_cost *>()){
                child->deleteLater();
            }
        }
        if(ui->scrollArea->findChildren<QWidget *>().count() != 0){
            foreach(QWidget* child, ui->scrollArea->findChildren<QWidget *>()){
                child->deleteLater();
            }
        }
//        ui->scrollArea->findChild<QWidget *>()->deleteLater();
    }
}

void Knife::set(QStringList names, QStringList costs){
    ui->scrollArea->show();
    QList<Co> colors = db->selectColor();
    QWidget *w = new QWidget(ui->scrollArea);
    ui->scrollArea->setWidget(w);
    QVBoxLayout *vbox = new QVBoxLayout(w);
    w->setLayout(vbox);
    for(int i = 0; i < colors.count(); ++i){
        double cost = 0.0;
        for(int i = 0; i < names.count()-1; ++i){
            QString name = colors[i].rus + QString(" (%1)").arg(colors[i].number);
            if(name == names[i]){
                cost = costs[i].toDouble();
                break;
            }
        }
        High_cost *color_pan = new High_cost(colors[i].rus + QString(" (%1)").arg(colors[i].number), ui->scrollArea, cost);
//            QHBoxLayout *color_pan = new QHBoxLayout(ui->listWidget);
//            color_pan->setSpacing(1);
//            QCheckBox *check_color = new QCheckBox(QString(""), ui->listWidget);
//            QLabel *name_col = new QLabel(colors[i].rus, ui->listWidget);
//            QDoubleSpinBox *cos_col = new QDoubleSpinBox(ui->listWidget);
//            cos_col->setMaximum(10000.0);
//            color_pan->addWidget(check_color);
//            color_pan->addWidget(name_col);
//            color_pan->addWidget(cos_col);
        vbox->addWidget(color_pan);
    }
}

void Knife::knCheck(){
    if(ui->KnifeCheck->isChecked()){
        ui->KnifeCheck->setText(tr("Нож"));
        ui->checkBox->setDisabled(false);
    }else{
        ui->KnifeCheck->setText(tr("Набор"));
        ui->checkBox->setDisabled(true);
    }
    ui->checkBox->setChecked(false);
    ui->scrollArea->hide();
}
