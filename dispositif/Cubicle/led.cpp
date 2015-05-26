#include "led.h"

Led::Led()
{
    etat =0; // 0 equivaut à led eteinte

}

void Led::modifierEtat()
{
    if(this->etat==0)
    {
         this->etat=1;
    }
    else{
         this->etat=0;
    }

}

int Led::getEtat(){
    return this->etat;
}
