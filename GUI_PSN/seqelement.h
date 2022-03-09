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
    void setNextEl(SeqElement* el);
    void setLastEl(SeqElement* el);
    void setName(QString newName);
    SeqElement* getNextEl();


private:
    Ui::SeqElement *ui;
    SeqElement *nextEl = NULL;
    SeqElement *lastEl = NULL;


public slots:
    void changeName(QString newName);
    void delBTN();
signals:
    void deleteSignals(SeqElement* el);
    void newNameSignals(QString newName);
};

#endif // SEQELEMENT_H
