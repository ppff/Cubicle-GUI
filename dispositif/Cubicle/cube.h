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
    QList<Plan>* listePlan1; //liste des plans vue de dessus ori=0
    QList<Plan>* listePlan2; //liste des plans vue de gauche ori=1
    QList<Plan>* listePlan3; //liste des plans vue de face  ori=2
};

#endif // CUBE_H
