#ifndef BOUND_H
#define BOUND_H

#include <QWidget>
#include "figure.h"

namespace Ui {
class Bound;
}

class Bound : public QWidget
{
    Q_OBJECT

public:
    explicit Bound(QList<Figure *> list, QWidget *parent = nullptr);
    ~Bound();

    enum BoundTypes {
        None,
        Dirichlet,
        Neumann,
        Newtone,
        Bounder
    };

private:
    Ui::Bound *ui;
    QList<QString> nameGroup;
    QList<Figure *> figureList;
    void updateTree();

private slots:
    void chDir();
    void rad();
    void define();
    void focusOnTree();
};

#endif // BOUND_H
