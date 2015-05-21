#include "cube.h"
#include <QString>
#include <QList>
#include "plan.h"

Cube::Cube()
{
    this->listePlanHor= new QList<Plan>();
    this->listePlanVer= new  QList<Plan>();



    for (int i = 0 ; i < 9 ; i++){
    Plan p=Plan();
             this->listePlanHor->insert(i, p);
             this->listePlanVer->insert(i,p);
    }
}


QList<Plan>* Cube:: getListHor(){
    return this->listePlanHor;
}
QList<Plan>* Cube:: getListVer(){
    return this->listePlanVer;
}

void Cube::updateCube(const Plan p, const int ori, const int pos){
    if(ori==0){
        this->getListHor()->removeAt(pos);
        this->getListHor()->insert(pos,p);
    }
    else {
        this->getListVer()->removeAt(pos);
        this->getListVer()->insert(pos,p);
    }
}
