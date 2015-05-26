#include "cube.h"
#include <QString>
#include <QList>
#include "plan.h"

Cube::Cube()
{
    this->listePlan1= new QList<Plan>();

    for (int i = 0 ; i < 9 ; i++){
    Plan p=Plan();
             this->listePlan1->insert(i, p);
    }
}


QList<Plan>* Cube:: getList1(){
    return this->listePlan1;
}


void Cube::updateCube(const Plan p,  const int pos){

        this->getList1()->removeAt(pos);
        this->getList1()->insert(pos,p);

}
