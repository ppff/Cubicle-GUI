#ifndef LED_H
#define LED_H

class Led
{
public:
    Led();

public:
    void allumer();

public:
    void eteindre();

public:
    void updateFichier();

private:
   int etat;
};

#endif // LED_H
