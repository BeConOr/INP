#ifndef CURRTASK_H
#define CURRTASK_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <map>
#include <string>
#include "Struck.h"

using namespace std;
class CurrTask
{
public:
    CurrTask(StartData start, UnitsCoef co, int *order);
    void setParam(StartData start);
    void setUnits(UnitsCoef co, int *order);
private:
    StartData saveData;
    UnitsCoef coef;
    int unitsOrd[7];
};

#endif // CURRTASK_H
