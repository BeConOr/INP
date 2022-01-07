#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QShortcut>

#include "paintscene.h"
#include "figure.h"
#include "view.h"
#include "creategroup.h"


namespace Ui {
class Geometry;
}

class Geometry : public QWidget
{
    Q_OBJECT

public:
    explicit Geometry(QList<Figure *> list, QWidget *parent = nullptr);
    ~Geometry();

signals:
    void sendList(QList<Figure *> list);
    void Exit();

private:
    PaintScene *scene;  // Объявляем кастомную графическую сцену
    Ui::Geometry *ui;
    QList<Figure *> figureList;
    QShortcut *keyDel;
    QShortcut *keyAddToGroup; //key A
    QTimer *timer;
    View *graphicsView;
    QList<int> delFig;
    int last = 0;
    QList<QString> nameGroup;
    void updateTree();

private slots:
    // Таймер для изменения размеров сцены при изменении размеров Окна приложения
    void line_pushButton_clicked();
    void circle_pushButton_clicked();
    void ellipse_pushButton_clicked();// Включаем отрисовку Линии
    void recieveWidget(QWidget *wid);
    void recieveFigure(Figure *fig);
    void slotShortcutDel();
    void slotTimer();
    void slotGenerate();
    void slotExit();
    void create(QList<Figure *> list, QString name);
    void launchCreate();
    void addToGroup();
    void deleteGroup();
};

#endif // GEOMETRY_H
