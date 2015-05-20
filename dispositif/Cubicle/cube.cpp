#include "cube.h"
#include <QString>
#include <QList>
#include "plan.h"

Cube::Cube()
{
    this->listePlanHor= QList<Plan>();
    this->listePlanVer= QList<Plan>();



    for (int i = 0 ; i < 9 ; i++){
    Plan p;
             this->listePlanHor.insert(i, p);
            // this->listePlanVer.push_back(new Plan());
    }
}
