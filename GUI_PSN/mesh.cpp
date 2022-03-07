#include "mesh.h"
#include "ui_mesh.h"
#include "seqelement.h"

Mesh::Mesh(MeshCond* mesh, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mesh)
{
    ui->setupUi(this);
    cond = mesh;
    ui->doubleSpinBox->setValue(mesh->r[0]);
    for(int i = 1; i < mesh->r.count(); ++i){
        SeqElement* tempEl = new SeqElement(tr("r"), (SeqCond){mesh->r[i], mesh->rN[i-1]}, ui->RPartLay);
        connect(tempEl, &SeqElement::deleteSignals, this, &Mesh::incrR);
        ui->RpartLay->addWidget(tempEl);
        ++rCounter;
        ui->AddR->setEnabled(rCounter < 10);
    }
    ui->doubleSpinBox_2->setValue(mesh->z[0]);
    for(int i = 1; i < mesh->z.count(); ++i){
        SeqElement* tempEl = new SeqElement(tr("z"), (SeqCond){mesh->z[i], mesh->zN[i-1]}, ui->ZPartLay);
        connect(tempEl, &SeqElement::deleteSignals, this, &Mesh::incrZ);
        ui->ZpartLay->addWidget(tempEl);
        ++zCounter;
        ui->AddZ->setEnabled(zCounter < 10);
    }

    connect(ui->AddR, &QPushButton::clicked, this, &Mesh::addR);
    connect(ui->AddZ, &QPushButton::clicked, this, &Mesh::addZ);
    connect(ui->OK_butt, &QPushButton::clicked, this, &Mesh::OKslot);
}

Mesh::~Mesh()
{
    delete ui;
}

void Mesh::addR(){
    ui->RpartLay->addWidget(new SeqElement(tr("r"), (SeqCond){0.0, 1}, ui->RPartLay));
    ++rCounter;
    qDebug() << tr("rCounter: %1").arg(rCounter);
    ui->AddR->setEnabled(rCounter < 10);
}

void Mesh::addZ(){
    ui->ZpartLay->addWidget(new SeqElement(tr("z"), (SeqCond){0.0, 1}, ui->ZPartLay));
    ++zCounter;
    qDebug() << tr("zCounter: %1").arg(zCounter);
    ui->AddZ->setEnabled(zCounter < 10);
}

void Mesh::OKslot(){
    QList<SeqElement*> rElements = ui->RPartLay->findChildren<SeqElement*>();
    QList<SeqElement*> zElements = ui->ZPartLay->findChildren<SeqElement*>();
    qDebug() << rElements.count();
    qDebug() << zElements.count();
    cond->r.clear();
    cond->z.clear();
    cond->zN.clear();
    cond->rN.clear();
    cond->r.append(ui->doubleSpinBox->value());
    cond->z.append(ui->doubleSpinBox_2->value());
    if(rElements.count() > 0){
        for(int i = 0; i < rElements.count(); ++i){
            cond->r.append(rElements[i]->giveCond().coord);
            cond->rN.append(rElements[i]->giveCond().seqNumb);
        }
    }
    if(zElements.count() > 0){
        for(int i = 0; i < zElements.count(); ++i){
            cond->z.append(zElements[i]->giveCond().coord);
            cond->zN.append(zElements[i]->giveCond().seqNumb);
        }
    }
}

void Mesh::incrZ(){
    --zCounter;
    ui->AddZ->setEnabled(zCounter < 10);
    qDebug() << tr("zCounter: %1").arg(zCounter);
}

void Mesh::incrR(){
    --rCounter;
    ui->AddR->setEnabled(rCounter < 10);
    qDebug() << tr("rCounter: %1").arg(rCounter);
}
