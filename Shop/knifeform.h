#ifndef KNIFEFORM_H
#define KNIFEFORM_H

#include <QWidget>
#include "database.h"

namespace Ui {
class KnifeForm;
}

class KnifeForm : public QWidget
{
    Q_OBJECT

public:
    explicit KnifeForm(QString dbname, Kn inf,  QList<Co> colors, QWidget *parent = nullptr);
    ~KnifeForm();
    QVariantList recieveInf(bool engFlag);

private:
    Ui::KnifeForm *ui;
    DataBase *db;
    Kn inform;
    bool openFlag = false;
    QString dbn;
private slots:
    void deleteBTN();
    void enlargeBTN();
    void openBTN();
    void editBTN();
};

#endif // KNIFEFORM_H
