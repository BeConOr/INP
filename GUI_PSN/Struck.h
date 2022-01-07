#ifndef STRUCK_H
#define STRUCK_H
#include <QtWidgets>

struct InitData{
    QStringList typeT;
    QStringList geomT;
    QStringList meshArr;
};

struct StartData{
    int typeT;
    int geomT;
    int matrix;
    int field;
    int trace;
    bool Q;
    bool E;
    bool H;
    int stream;
    double step;
    int numb;
    double umin;
    double umax;
    void copy(StartData *a);
};

struct UnitsCoef{
    double len;
    double pot;
    double mag;
    double time;
    double curr;
    double ch;
    double cond;
    void copy(UnitsCoef *a);
};

struct InitUnits{
    QList<QStringList> namelist = {
        {"m", "cm", "mm"},
        {"V", "kV", "MV"},
        {"T", "kG"},
        {"s", "ms", "mcs", "ns"},
        {"a/m*m", "ka/m*m"},
        {"C", "kC", "MC"},
        {"S/m", "kS/m", "MS/m"}
    };
    double coef[7][4] = {
        {1.0, 0.01, 0.001},
        {1.0, 1000.0, 1000000.0},
        {1.0, 0.1},
        {1.0, 0.001, 0.000001, 0.000000001},
        {1.0, 1000},
        {1.0, 1000.0, 1000000.0},
        {1.0, 1000.0, 1000000.0}
    };
};

#endif // STRUCK_H
