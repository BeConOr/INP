#ifndef KNIFE_H
#define KNIFE_H

#include <QDialog>
#include <QFile>
#include "database.h"

namespace Ui {
class Knife;
}

class Knife : public QDialog
{
    Q_OBJECT

public:
    explicit Knife(QString dbname, int id = 0, QWidget *parent = nullptr);
    ~Knife();

private:
    Ui::Knife *ui;

    void loadFile(const QString &fileName);

    QByteArray inByteArray;
    QByteArray lowByteArray;
    DataBase *db;
    QString fileName;
    int kid;
    void set(QStringList names, QStringList costs);

private slots:
    void open();
    void OK_slot();
    void check();
    void knCheck();
};

#endif // KNIFE_H
