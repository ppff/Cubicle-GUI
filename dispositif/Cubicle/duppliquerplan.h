#ifndef DUPPLIQUERPLAN_H
#define DUPPLIQUERPLAN_H

#include "global.h"
#include "gestionfichier.h"
class DuppliquerPlan
{
public:
    DuppliquerPlan();
    void SelectPlan(Ui::MainWindow *ui,Cube c, int n,QList<QVector3D> l, QPushButton* buttons[90]);
    void dupliquer(Ui::MainWindow *ui,Cube cubeMotif,
                   int NumeroPlan,QList<int> l,QList<QVector3D> liste_vecteur3D,QString emplMotif);
    void DeconnecterPlan(Ui::MainWindow *ui);
    void colorePlan(Ui::MainWindow *ui,int nplan);
    void decolorePlan(Ui::MainWindow *ui,int nplan);
    QList<QVector3D> parcoursCube(int NumeroPlan,QList<QVector3D> liste_vecteur3D,Cube cubeMotif,int nplan);
    Cube updateCube(Cube nouveauCube,int NumeroPlan,int nplan);
};

#endif // DUPPLIQUERPLAN_H
