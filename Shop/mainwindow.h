#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DataBase *db;
    QString dbname;


private slots:
    void openColor();
    void openKnife();
    void createOrder();
    void setKnifeList();
    void setColorList();
    void feeChk();
    void delivChk();
    void dolChk();
    void openDB();
};
#endif // MAINWINDOW_H
