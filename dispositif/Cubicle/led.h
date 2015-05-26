#ifndef LED_H
#define LED_H


class Led
{
public:
    Led();
    void modifierEtat();
    int getEtat();

private:
   int etat;


};

#endif // LED_H
