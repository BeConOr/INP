#include "currtask.h"
#include <map>
#include "Struck.h"

CurrTask::CurrTask(StartData start, UnitsCoef co, int *order)
{
    start.copy(&saveData);
    setUnits(co, order);
}

void CurrTask::setParam(StartData start){
    start.copy(&saveData);
}

void CurrTask::setUnits(UnitsCoef co, int *order){
    co.copy(&coef);
    for(int i = 0; i < 7; i++){
        unitsOrd[i] = order[i];
    }
}
