#ifndef DATA_H
#define DATA_H

#include <QDialog>
#include "currtask.h"
#include "Struck.h"

namespace Ui {
class Data;
}

class Data : public QDialog
{
    Q_OBJECT

public:
    explicit Data(InitData init, StartData str, QWidget *parent = nullptr);
    ~Data();
    StartData getPar();

private:
    Ui::Data *ui;
    StartData pass;
public slots:
    void passParam();
    void MeshQ();
    void MeshE();
    void MeshH();
};

#endif // DATA_H
