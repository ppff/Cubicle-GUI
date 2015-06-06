#ifndef CONTROLCUBE3D_H
#define CONTROLCUBE3D_H

#include "global.h"
class ControlCube3D
{
public:
    ControlCube3D();
    void desactivePlan(Ui::MainWindow *ui);
    int affichePlanLed(const QString & valeur,Ui::MainWindow *ui,
                       QPushButton* buttons[90],Cube cubeMotif,int numeroPlan);
};

#endif // CONTROLCUBE3D_H
