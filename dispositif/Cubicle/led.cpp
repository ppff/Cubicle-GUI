#include "led.h"

Led::Led()
{
    this->etat = eteinte;
}

Led::allumer()
{
    this->etat= allumee;
    this->updateFichier();
}


Led::eteindre()
{
    this->etat= eteinte;
    this->updateFichier();
}
