#include "cube.h"
#include <QString>
#include <QList>
#include "plan.h"

Cube::Cube()
{
    this->listePlan1= new QList<Plan>();
    this->listePlan2= new  QList<Plan>();
    this->listePlan3= new  QList<Plan>();



    for (int i = 0 ; i < 9 ; i++){
    Plan p=Plan();
             this->listePlan1->insert(i, p);
             this->listePlan2->insert(i,p);
             this->listePlan3->insert(i,p);
    }
}


QList<Plan>* Cube:: getList1(){
    return this->listePlan1;
}

QList<Plan>* Cube:: getList2(){
    return this->listePlan2;
}

QList<Plan>* Cube:: getList3(){
    return this->listePlan3;
}

void Cube::updateCube(const Plan p, const int ori, const int pos){
    if(ori==0){
        this->getList1()->removeAt(pos);
        this->getList1()->insert(pos,p);
    }
    else  if(ori==1){
        this->getList2()->removeAt(pos);
        this->getList2()->insert(pos,p);
          }
         else {
        this->getList3()->removeAt(pos);
        this->getList3()->insert(pos,p);
    }
}
