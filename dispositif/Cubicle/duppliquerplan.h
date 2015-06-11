#ifndef DUPPLIQUERPLAN_H
#define DUPPLIQUERPLAN_H

#include "global.h"
#include "gestionfichier.h"
#include "qpushbuttonpers.h"
class DuppliquerPlan
{
public:
    DuppliquerPlan();

    QList<QVector3D> parcoursCube(int NumeroPlanADupliquer,QList<QVector3D> liste_vecteur3D,Cube cubeMotif,int nplan);
    Cube updateCube(Cube nouveauCube,int NumeroPlanADupliquer,int nplan);
    QList<QVector3D> collerPlan(Cube cubeMotif,
                    int NumeroPlanADupliquer,int NumeroPlanPaste,QList<QVector3D> liste_vecteur3D,QString emplMotif);

};

#endif // DUPPLIQUERPLAN_H
