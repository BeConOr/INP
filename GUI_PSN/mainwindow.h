#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data.h"
#include "Struck.h"
#include "figure.h"
#include <QGraphicsScene>
#include "view.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadFile(const QString &fileName);

private:
    Ui::MainWindow *ui;
    void createActions();
    InitData inData;
    StartData stData;
    CurrTask *task;
    int order[7];
    UnitsCoef coef;
    InitUnits inUnits;
    QPlainTextEdit *textEdit;
    QString curFile;
    QList<Figure *> figureList;
    QGraphicsScene *scene;
    View *graphicsView;
    double mesh_size = 0.001;
    void fieldFileWrite();
    QString fileN = QString("Unnamed");

    void setCurrentFile(const QString &fileName);
    bool maybeSave();
    bool saveFile(const QString &fileName);

    void spaceWr(QDataStream *in, int n);
    void spaceWr(QDataStream *in, float n);
    void chWr(QDataStream *in, char *n, int len);

private slots:
    void launchData();
    void launchUnits();
    void launchGeom();
    void launchBound();
    void launchDevide();
    void launchMesh();
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void getFigureList(QList<Figure *> list);
    void slotExit();
    void slotTakePic();
};
#endif // MAINWINDOW_H
