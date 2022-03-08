#ifndef MESH_H
#define MESH_H

#include <QDialog>
#include "Struck.h"
#include "seqelement.h"

namespace Ui {
class Mesh;
}

class Mesh : public QDialog
{
    Q_OBJECT

public:
    explicit Mesh(MeshCond* mesh, QWidget *parent = nullptr);
    ~Mesh();

private:
    Ui::Mesh *ui;
    MeshCond* cond;
    int zCounter = 0;
    int rCounter = 0;
    SeqElement* lastElR = NULL;
    SeqElement* lastElZ = NULL;
    SeqElement* tempEl = NULL;

private slots:
    void addR();
    void addZ();
    void OKslot();

public slots:
    void incrZ();
    void incrR();
};

#endif // MESH_H
