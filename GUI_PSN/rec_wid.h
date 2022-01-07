#ifndef REC_WID_H
#define REC_WID_H

#include <QWidget>

namespace Ui {
class Rec_wid;
}

class Rec_wid : public QWidget
{
    Q_OBJECT

public:
    explicit Rec_wid(QPointF start, QPointF end, QWidget *parent = nullptr);
    ~Rec_wid();

signals:
    void OK(QPointF start, QPointF end, bool check);
    void Canc();

private:
    Ui::Rec_wid *ui;
public slots:
    void setA(QPointF start, QPointF end);

private slots:
    void emOK();
    void emCanc();
    void slotCheck();
};

#endif // REC_WID_H
