#ifndef ELIP_WID_H
#define ELIP_WID_H

#include <QWidget>

namespace Ui {
class Elip_wid;
}

class Elip_wid : public QWidget
{
    Q_OBJECT

public:
    explicit Elip_wid(QPointF start, QPointF end, QWidget *parent = nullptr);
    ~Elip_wid();
signals:
    void OK(QPointF start, QPointF end);
    void Canc();

private:
    Ui::Elip_wid *ui;
public slots:
    void setA(QPointF start, QPointF end);

private slots:
    void emOK();
    void emCanc();
};

#endif // ELIP_WID_H
