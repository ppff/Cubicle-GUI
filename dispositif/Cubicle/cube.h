#ifndef CUBE_H
#define CUBE_H
#include <QString>
#include <QList>
#include "plan.h"



class Cube
{
public:
    Cube();
    QList<Plan>* getList1();
    QList<Plan>* getList2();
    QList<Plan>* getList3();
    void updateCube(const Plan p, const int ori, const int pos);
private:
    QList<Plan>* listePlan1;
    QList<Plan>* listePlan2;
    QList<Plan>* listePlan3;
};

#endif // CUBE_H
