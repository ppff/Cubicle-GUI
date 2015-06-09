#ifndef CONTROLCUBE3D_H
#define CONTROLCUBE3D_H

#include "global.h"
#include "qpushbuttonpers.h"
class ControlCube3D
{
public:
    ControlCube3D();
    void desactivePlan(QPushButtonPers * plans[9]);
    int affichePlanLed(const QString & valeur,Ui::MainWindow *ui,QPushButtonPers * plans[9],
                       QPushButton* buttons[90],Cube cubeMotif);


};

#endif // CONTROLCUBE3D_H
