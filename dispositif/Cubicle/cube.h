#ifndef CUBE_H
#define CUBE_H
#include <QString>
#include <QList>
#include "plan.h"



class Cube
{
public:
    Cube();
    QList<Plan>* getListVer();
    QList<Plan>* getListHor();
    void updateCube(const Plan p, const int ori, const int pos);
private:
    QList<Plan>* listePlanHor;
    QList<Plan>* listePlanVer;
};

#endif // CUBE_H
