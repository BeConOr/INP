#ifndef SEQELEMENT_H
#define SEQELEMENT_H

#include <QWidget>
#include "Struck.h"

namespace Ui {
class SeqElement;
}

class SeqElement : public QWidget
{
    Q_OBJECT

public:
    explicit SeqElement(QString name, SeqCond curr, QWidget *parent = nullptr);
    ~SeqElement();
    SeqCond giveCond();


private:
    Ui::SeqElement *ui;
private slots:
    void delBTN();

public slots:
    void changeName(QString newName);
signals:
    void deleteSignals();
    void newNameSignals(QString newName);
};

#endif // SEQELEMENT_H
