#ifndef DEVIDECOND_H
#define DEVIDECOND_H

#include <QDialog>
#include "figure.h"

namespace Ui {
class DevideCond;
}

class DevideCond : public QDialog
{
    Q_OBJECT

public:
    explicit DevideCond(QList<Figure *> list, QWidget *parent = nullptr);
    ~DevideCond();

private:
    Ui::DevideCond *ui;
    QList<QString> nameGroup;
    QList<Figure *> figureList;
    void updateTree();

private slots:
    void define();
    void focusOnTree();
};

#endif // DEVIDECOND_H
