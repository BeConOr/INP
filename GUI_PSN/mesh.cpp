#include "mesh.h"
#include "ui_mesh.h"

Mesh::Mesh(double mesh_size, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mesh)
{
    ui->setupUi(this);
    ui->mesh_size->setValue(mesh_size);
}

Mesh::~Mesh()
{
    delete ui;
}

double Mesh::sizeVal(){
    return ui->mesh_size->value();
}
