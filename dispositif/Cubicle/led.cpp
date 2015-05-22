#include "led.h"

Led::Led()
{
    etat =0; // 0 equivaut à led eteinte

}

void Led::allumer()
{
    this->etat=1;
    this->updateFichier();
}


void Led::eteindre()
{
    this->etat= 0;
    this->updateFichier();
}

void Led::modifierEtat()
{
    if(this->etat==0)
    {
        allumer();
    }
    else{
        eteindre();
    }

}

void Led::updateFichier()
{

}

int Led::getEtat(){
    return this->etat;
}
