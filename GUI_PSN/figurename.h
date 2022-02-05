#ifndef FIGURENAME_H
#define FIGURENAME_H

#include <QWidget>

namespace Ui {
class FigureName;
}

class FigureName : public QWidget
{
    Q_OBJECT

public:
    explicit FigureName(QWidget *parent = nullptr);
    ~FigureName();
    QString getName();

private:
    Ui::FigureName *ui;
};

#endif // FIGURENAME_H
