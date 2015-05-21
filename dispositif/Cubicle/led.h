#ifndef LED_H
#define LED_H


class Led
{
public:
    Led();
    void allumer();
    void eteindre();
    void modifierEtat();
    void updateFichier();
    int getEtat();

private:
   int etat;


};

#endif // LED_H
