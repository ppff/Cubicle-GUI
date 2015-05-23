#include "plan.h"
#include <iostream>
#include <cstdlib>


Plan::Plan(){

    ///allocation dynamique////////
    this->led_list=new Led*[9];
    for (int i=0;i<9;i++){
        led_list[i]=new Led[9];
    }
    ///initialisation de la matrice////
    for(int i=0 ; i<9 ; i++){
        for(int j ; j<9 ; j++){
            Led l=Led();
            this->led_list[i][j]=l;
        }
    }

}

void Plan::setLed(const Led l,const int i, const int j){
    this->led_list[i][j]=l;
}

Led Plan::getLed(const int i,const int j){
    return this->led_list[i][j];
}

Led** Plan::getMatrice(){
    return this->led_list;
}

void Plan::updatePlan(const Led l, const int i, const int j,const int nplan, const int oriinit, const int nvori ){
    switch (oriinit){
        case 0: switch(nvori){
             //       case 1: this->setLed(l,abs(8-nplan),abs(8-i)); break;
               //     case 2: this->setLed(l,abs(8-nplan),j); break;
                    case 0: this->setLed(l,i,j); break;
            }
        break;

        case 1: switch(nvori){
                    case 0: this->setLed(l,abs(8-j),nplan); break;
                    case 2: this->setLed(l,i,nplan); break;
                    case 1: this->setLed(l,i,j); break;
            }
        break;

        case 2:switch(nvori){
                    case 0: this->setLed(l,nplan,j); break;
                    case 1: this->setLed(l,i,abs(8-nplan)); break;
                    case 2: this->setLed(l,i,j); break;
    }
        break;
    }


}


