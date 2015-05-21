#ifndef PLANLED_H
#define PLANLED_H
#include "cube.h"


namespace Ui {
class PlanLed;
}


class PlanLed
{

public slots:
    void AfficheLed();


private:
    Ui::PlanLed *ui;
    Cube c;

};


#endif // PLANLED_H
