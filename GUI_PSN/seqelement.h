#ifndef SEQELEMENT_H
#define SEQELEMENT_H

#include <QWidget>

namespace Ui {
class SeqElement;
}

struct SeqCond{
    double coord;
    int seqNumb;
};

class SeqElement : public QWidget
{
    Q_OBJECT

public:
    explicit SeqElement(QString name, QWidget *parent = nullptr);
    ~SeqElement();
    SeqCond giveCond();


private:
    Ui::SeqElement *ui;
};

#endif // SEQELEMENT_H
