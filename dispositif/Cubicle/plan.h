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
    void updatePlan(const Led l, const int i, const int j);

private:
    Led** led_list;


};

#endif // PLAN_H
