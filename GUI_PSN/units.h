#ifndef UNITS_H
#define UNITS_H

#include <QDialog>
#include "Struck.h"

namespace Ui {
class Units;
}

class Units : public QDialog
{
    Q_OBJECT

public:
    explicit Units(InitUnits init, int *order, QWidget *parent = nullptr);
    ~Units();
    void passUnits(UnitsCoef *coef, int *order);

private:
    Ui::Units *ui;
};

#endif // UNITS_H
