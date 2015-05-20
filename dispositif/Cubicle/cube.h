#ifndef CUBE_H
#define CUBE_H
#include <QString>
#include <QList>
#include "plan.h"



class Cube
{
public:
    Cube();

private:
    QList<Plan> listePlanHor;

private:
    QList<Plan> listePlanVer;
};

#endif // CUBE_H
