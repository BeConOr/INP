#include <QtWidgets>
#include "Struck.h"

void StartData::copy(StartData *a){
    a->typeT = typeT;
    a->geomT = geomT;
    a->matrix = matrix;
    a->field = field;
    a->trace = trace;
    a->Q = Q;
    a->E = E;
    a->H = H;
    a->stream = stream;
    a->step = step;
    a->numb = numb;
    a->umin = umin;
    a->umax = umax;
}

void UnitsCoef::copy(UnitsCoef *a){
    a->len = len;
    a->pot = pot;
    a->mag = mag;
    a->time = time;
    a->curr = curr;
    a->ch = ch;
    a->cond = cond;
}

int MeshCond::meshNodeNumb(){
    int zSum = 0;
    int rSum = 0;
    int zCount = z.count();
    int rCount = r.count();
    if(z.count() > 1){
        for(int i = 0; i < zN.count(); ++i){
            zSum += zN[i];
        }
    }else{
        zCount = 0;
    }
    if(r.count() > 1){
        for(int i = 0; i < rN.count(); ++i){
            rSum += rN[i];
        }
    }else{
        rCount = 0;
    }
    return (zCount + zSum)*(rCount + rSum);
}
