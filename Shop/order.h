#ifndef ORDER_H
#define ORDER_H

#include <QDialog>

namespace Ui {
class Order;
}

class Order : public QDialog
{
    Q_OBJECT

public:
    explicit Order(QString text, QWidget *parent = nullptr);
    ~Order();

private:
    Ui::Order *ui;
private slots:
    void copy();
};

#endif // ORDER_H
