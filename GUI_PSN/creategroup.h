#ifndef CREATEGROUP_H
#define CREATEGROUP_H

#include <QDialog>
#include "figure.h"
#include <QTreeWidget>

namespace Ui {
class CreateGroup;
}

class CreateGroup : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGroup(QList<Figure *> figures, QList<QString> names, QList<int> del, QWidget *parent = nullptr);
    ~CreateGroup();

private:
    Ui::CreateGroup *ui;
    QList<Figure *> figureList;
    QList<int> delFig;
    QList<QString> group;
    QList<QString> addGroup;
    QList<int> All;
    QList<int> Add;

    void createTree(QList<int> curList, QTreeWidget *treeWidget, QList<QString> nameGroup);

private slots:
    void addButton();
    void removeButton();
    void okSlot();

signals:
    void addGroupSignal(QList<Figure *> list, QString name);
};


#endif // CREATEGROUP_H
