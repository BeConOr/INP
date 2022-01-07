#ifndef CIRC_WID_H
#define CIRC_WID_H

#include <QWidget>

namespace Ui {
class Circ_wid;
}

class Circ_wid : public QWidget
{
    Q_OBJECT

public:
    explicit Circ_wid(QPointF start, QPointF end, QWidget *parent = nullptr);
    ~Circ_wid();
signals:
    void OK(QPointF start, QPointF end);
    void Canc();

private:
    Ui::Circ_wid *ui;
public slots:
    void setA(QPointF start, QPointF end);

private slots:
    void emOK();
    void emCanc();
};

#endif // CIRC_WID_H
