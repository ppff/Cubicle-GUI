#ifndef PERSONBUTTON_H
#define PERSONBUTTON_H
#include <QPushButton>
#include<QPainter>

class PersonButton: public QPushButton
{
public:
    PersonButton(QWidget* parent);
protected:
    void paintEvent(QPaintEvent *);
};

#endif // PERSONBUTTON_H
