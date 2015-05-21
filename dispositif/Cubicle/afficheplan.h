#ifndef AFFICHEPLAN_H
#define AFFICHEPLAN_H
#include "cube.h"
#include <QDialog>
#include <string>
#include <sstream>
#include <iostream>
#include <QLabel>
 using namespace std;

namespace Ui {
class AffichePlan;
}

class AffichePlan : public QDialog
{
    Q_OBJECT
public slots:
    void afficheLed(const int i, const int j, const int etat);
    void controlLed(const QString & valeur);
    void afficheCube3D( QLabel* label, QLabel* label2);


public:
    explicit AffichePlan(QWidget *parent = 0);
    ~AffichePlan();

private:
    Ui::AffichePlan *ui;
    Cube c;
    QPushButton* buttons[9];


};

#endif // AFFICHEPLAN_H
