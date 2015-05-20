#include "led.h"

Led::Led()
{
    this->etat =0; // 0 equivaut à led eteinte
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

void Led::updateFichier()
{

}
