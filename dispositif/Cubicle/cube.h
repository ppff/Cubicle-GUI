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

    void updateCube(const Plan p,  const int pos);
private:
    QList<Plan>* listePlan1;
};

#endif // CUBE_H
