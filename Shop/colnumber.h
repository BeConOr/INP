#ifndef COLNUMBER_H
#define COLNUMBER_H

#include <QWidget>

namespace Ui {
class ColNumber;
}

class ColNumber : public QWidget
{
    Q_OBJECT

public:
    explicit ColNumber(QString name, int number, QWidget *parent = nullptr);
    ~ColNumber();
    QString colorN();
    int number();

private:
    Ui::ColNumber *ui;
    QString colorName;
    int colorNumber;
private slots:
    void chk();
};

#endif // COLNUMBER_H
