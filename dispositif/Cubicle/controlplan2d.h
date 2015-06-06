#ifndef CONTROLPLAN2D_H
#define CONTROLPLAN2D_H

#include "global.h"


class ControlPlan2D
{
public:
    ControlPlan2D();
    void afficheLed(QPushButton* buttons[90],const int i, const int j,const  int etat );
    QList<QVector3D> controlLed(const QString & valeur,Cube cubeMotif,int NumeroPlan,
                    QList<QVector3D> liste_vecteur3D,Ui::MainWindow *ui,QPushButton* buttons[90]);

};

#endif // CONTROLPLAN2D_H
