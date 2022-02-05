#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include "figure.h"

class PaintScene : public QGraphicsScene
{
    Q_OBJECT

    Q_PROPERTY(int typeFigure
                   READ typeFigure WRITE setTypeFigure
                   NOTIFY typeFigureChanged)

public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();

        int typeFigure() const;                 // Возвращение текущего типа
        void setTypeFigure(const int type);     // Установка текущего типа
        void setCount(int numb);

        // Перечисление типов используемых фигур
        enum FigureTypes {
            LineType,
            CircleType,
            EllipseType,
            NoneType,
            ArcType
        };

    signals:
        void typeFigureChanged();               // Сигнал об изменении типа текущей фигуры
        void setWidget(QWidget *widg);
        void sendFigure(Figure *fig);

    private:
        /* Объект для временного хранения рисуемой фигуры
         * Является объектом базового класса для всех трёх типов фигур в примере
         * */
        Figure *tempFigure;
        int m_typeFigure;   // текущий тип фигуры
        QWidget *tempWidg;
        int number = 0;

    private:
        // Для рисования используем события мыши
        void mousePressEvent(QGraphicsSceneMouseEvent * event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//        void keyPressEvent(QKeyEvent *event);
private slots:
        void updateAr(QPointF start, QPointF end);
        void updateArc(QPointF start, double radius, QPointF angles);
        void buttonCanc();
};

#endif // PAINTSCENE_H
