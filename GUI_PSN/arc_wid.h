#ifndef ARC_WID_H
#define ARC_WID_H

#include <QWidget>

namespace Ui {
class Arc_wid;
}

class Arc_wid : public QWidget
{
    Q_OBJECT

public:
    explicit Arc_wid(QWidget *parent = nullptr);
    ~Arc_wid();

signals:
    void OK(QPointF start, double radius, QPointF angles);
    void Canc();

private slots:
    void emOK();
    void emCanc();

private:
    Ui::Arc_wid *ui;
};

#endif // ARC_WID_H
