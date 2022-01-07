#ifndef COLOR_H
#define COLOR_H

#include <QDialog>
#include <QFile>
#include "database.h"

namespace Ui {
class Color;
}

class Color : public QDialog
{
    Q_OBJECT

public:
    explicit Color(QString dbname, QWidget *parent = nullptr);
    ~Color();

private:
    Ui::Color *ui;

    void loadFile(const QString &fileName);

    QByteArray inByteArray;
    DataBase *db;
    QString fileName;

private slots:
    void open();
    void OK_slot();
};

#endif // COLOR_H
