#ifndef COLORFORM_H
#define COLORFORM_H

#include <QWidget>
#include "database.h"

namespace Ui {
class ColorForm;
}

class ColorForm : public QWidget
{
    Q_OBJECT

public:
    explicit ColorForm(QString dbname, Co inf, QWidget *parent = nullptr);
    ~ColorForm();

private:
    Ui::ColorForm *ui;
    DataBase *db;
    Co inform;
private slots:
    void deleteBTN();
    void enlargeBTN();
};

#endif // COLORFORM_H
