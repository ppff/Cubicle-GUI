#ifndef PLAN_H
#define PLAN_H
#include "led.h"
#include <QObject>
#include<QVector>


class Plan
{
public:
    Plan();
    void setLed(const Led l, const int i, const int j);
    Led** getMatrice();
    Led getLed(const int i, const int j);
    void updatePlan(const Led l, const int i, const int j,const int nplan, const int oriinit, const int nvori);

private:
    Led** led_list;


};

#endif // PLAN_H
