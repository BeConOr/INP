#ifndef MESH_H
#define MESH_H

#include <QDialog>

namespace Ui {
class Mesh;
}

class Mesh : public QDialog
{
    Q_OBJECT

public:
    explicit Mesh(double mesh_size, QWidget *parent = nullptr);
    ~Mesh();
    double sizeVal();

private:
    Ui::Mesh *ui;
};

#endif // MESH_H
