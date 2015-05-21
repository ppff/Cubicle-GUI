#ifndef AFFICHEPLAN_H
#define AFFICHEPLAN_H
#include "cube.h"
#include <QDialog>
#include <string>
#include <sstream>
#include <iostream>
 using namespace std;

namespace Ui {
class AffichePlan;
}

class AffichePlan : public QDialog
{
    Q_OBJECT
public slots:
    void afficheLed(const QString & valeur);
    void controlLed(const QString & valeur);


public:
    explicit AffichePlan(QWidget *parent = 0);
    ~AffichePlan();

private:
    Ui::AffichePlan *ui;
    Cube c;
    QPushButton* buttons[81];

};

#endif // AFFICHEPLAN_H
