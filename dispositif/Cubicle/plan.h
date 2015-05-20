#ifndef PLAN_H
#define PLAN_H

#include <QObject>
#include<QVector>
class Plan
{
public:
    Plan();

private:


   QVector<QVector<Led>> led_list(9);

};

#endif // PLAN_H
