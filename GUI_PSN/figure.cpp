#include "figure.h"
#include <QPainter>

Figure::Figure(QPointF point) : QGraphicsObject()
{
    // Устанавливаем стартовую координату для отрисовки фигуры
        this->setStartPoint(mapFromScene(point));
        this->setEndPoint(mapFromScene(point));
        /* Подключаем сигнал изменения координат к слоту запуска обновления содержимого объекта
         * Сигнал и слот присутствуют в базовом классе
         * */
        connect(this, &Figure::pointChanged, this, &Figure::updateRomb);

        groupId = 0;
        lastId = 0;
        groupName = "Figures";
        condition = {0, false, {0.0, 0.0}};

        pen.setCosmetic(true);
        penDot.setCosmetic(true);
        penDot.setCapStyle(Qt::RoundCap);
}

Figure::~Figure(){

}

QRectF Figure::boundingRect() const
{
    /* Возвращаем область, в которой лежит фигура.
     * Обновляемая область зависит от стартовой точки отрисовки и от конечной точки
     * */
    return QRectF((endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x()) - 5,
                  (endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y()) - 5,
                  qAbs(endPoint().x() - startPoint().x()) + 10,
                  qAbs(endPoint().y() - startPoint().y()) + 10);
}

void Figure::updateRomb()
{
    // Вызываем обновление области, в которой лежит фигура
    this->update((endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x()) - 5,
                 (endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y()) - 5,
                 qAbs(endPoint().x() - startPoint().x()) + 10,
                 qAbs(endPoint().y() - startPoint().y()) + 10);
    paramValue[1] = endPoint().y();
    paramValue[3] = endPoint().x();
    paramValue[0] = startPoint().y();
    paramValue[2] = startPoint().x();
}

void Figure::setStartPoint(const QPointF point)
{
    m_startPoint = mapFromScene(point);
    emit pointChanged(m_startPoint, m_endPoint);
}

void Figure::setEndPoint(const QPointF point)
{
    m_endPoint = mapFromScene(point);
    emit pointChanged(m_startPoint, m_endPoint);
}

QPointF Figure::startPoint() const
{
    return m_startPoint;
}

QPointF Figure::endPoint() const
{
    return m_endPoint;
}

QDataStream &operator<<(QDataStream &out, const Figure * &item)
{
    QDataStream::FloatingPointPrecision prev = out.floatingPointPrecision();
    out.setFloatingPointPrecision(QDataStream::DoublePrecision);
    out << item->startPoint() << item->endPoint();
    out.setFloatingPointPrecision(prev);
    return out;
}

QDataStream &operator>>(QDataStream &in, Figure * &item)
{
    in >> item->m_startPoint << item->m_endPoint;
    return in;
}

int Figure::getGroupId(){
    return groupId;
}

QString Figure::getGroupName(){
    return groupName;
}

void Figure::changeGroup(int id, QString name){
    lastId = groupId;
    groupId = id;
    groupName = name;
}

void Figure::cancelGroup(){
    groupId = groupId + lastId;
    lastId = groupId - lastId;
    groupId = groupId - lastId;
}

void Figure::fPen(){
//    pen = QPen(Qt::green, 2);
    pen.setColor(Qt::green);
}

void Figure::oPen(){
//    pen = QPen(Qt::blue, 2);
    pen.setColor(Qt::blue);
}

void Figure::setBound(int type, bool method, double *value){
    condition.type = type;
    condition.method = method;
    for(int i = 0; i < 2; ++i){
        condition.value[i] = value[i];
    }
}
BoundaryCond Figure::getBound(){
    return condition;
}

double* Figure::getCoeff(){
    return paramValue;
}

double* Figure::getAngles(){
    return angles;
}

int* Figure::getDevide(){
    return devide;
}

void Figure::setDevide(int div, int kvadr){
    devide[0] = div;
    devide[1] = kvadr;
}
