#ifndef FIGURE_H
#define FIGURE_H
#include <QGraphicsObject>
#include <QTimer>
#include <math.h>
#include <QObject>
#include <QPen>


struct BoundaryCond{
    int type;
    bool method;
    double value[2];
};

class Figure : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF startPoint READ startPoint WRITE setStartPoint NOTIFY pointChanged)
    Q_PROPERTY(QPointF endPoint READ endPoint WRITE setEndPoint NOTIFY pointChanged)
    friend QDataStream &operator>>(QDataStream &, Figure * &);
public:
    explicit Figure(QPointF point);
    ~Figure();

    QPointF startPoint() const;
    QPointF endPoint() const;

    void setStartPoint(const QPointF point);    // Установка стартовой точки
    void setEndPoint(const QPointF point);      // Установка конечной точки
    virtual const QString getType(){return QString("Figure");}
    virtual double getLength(){
        double x = endPoint().x() - startPoint().x();
        double y = endPoint().y() - startPoint().y();
        return sqrt(x*x + y*y);
    }

    int getGroupId();
    QString getGroupName();
    void changeGroup(int id, QString name);
    void cancelGroup();

    QString itemName = "Figure";

    void fPen();
    void oPen();

    void setBound(int type, bool method, double *value);
    BoundaryCond getBound();

    double* getCoeff();
    double* getAngles();
    int* getDevide();
    void setDevide(int div, int kvadr);


signals:
    void pointChanged(QPointF start, QPointF end);    // Сигнал об изменении точки

private:
    QPointF m_startPoint;   // Стартовая точка
    QPointF m_endPoint;     // Конечная точка

    QRectF boundingRect() const;    // Область, в которой содержится фигура

    int groupId;
    int lastId;
    QString groupName;

    BoundaryCond condition;

protected:
    QPen pen = QPen(Qt::blue, 2);

    double paramValue[4] = {0.0, 0.0, 0.0, 0.0};
    double angles[2] = {0.0, 1.0};
    int devide[2] = {6, 9};

public slots:
    virtual void updateRomb();     // Слот обновления области, в которой содержится фигура

};

QDataStream &operator<<(QDataStream &, const Figure * &);
QDataStream &operator>>(QDataStream &, Figure * &);
#endif // FIGURE_H
