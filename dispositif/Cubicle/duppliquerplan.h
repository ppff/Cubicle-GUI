#ifndef DUPPLIQUERPLAN_H
#define DUPPLIQUERPLAN_H

#include "global.h"
#include "gestionfichier.h"
class DuppliquerPlan
{
public:
    DuppliquerPlan();

    QList<QVector3D> dupliquer(Ui::MainWindow *ui,Cube cubeMotif,
                   int NumeroPlanADupliquer,QList<int> l,QList<QVector3D> liste_vecteur3D,QString emplMotif);
    void DeconnecterPlan(Ui::MainWindow *ui);
    void colorePlan(Ui::MainWindow *ui,int nplan);
    void decolorePlan(Ui::MainWindow *ui,int nplan);
    QList<QVector3D> parcoursCube(int NumeroPlanADupliquer,QList<QVector3D> liste_vecteur3D,Cube cubeMotif,int nplan);
    Cube updateCube(Cube nouveauCube,int NumeroPlanADupliquer,int nplan);
};

#endif // DUPPLIQUERPLAN_H
