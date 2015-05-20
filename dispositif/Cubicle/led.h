#ifndef LED_H
#define LED_H

class Led
{
public:
    Led();

public:
    allumer();

public:
    eteindre();

public:
    updateFichier();

private:
    enum etat { allumee, eteinte };

};

#endif // LED_H
