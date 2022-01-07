#ifndef HIGH_COST_H
#define HIGH_COST_H

#include <QWidget>

namespace Ui {
class High_cost;
}

class High_cost : public QWidget
{
    Q_OBJECT

public:
    explicit High_cost(QString name, QWidget *parent = nullptr, double cost = 0.0);
    ~High_cost();
    QVariantList getParam();
    bool chk();

private:
    Ui::High_cost *ui;
};

#endif // HIGH_COST_H
