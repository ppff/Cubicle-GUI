#ifndef AFFICHEPLAN_H
#define AFFICHEPLAN_H
#include "cube.h"
#include <QDialog>
#include <string>
#include <sstream>
#include <iostream>
#include <QLabel>
#include <QFile>
#include <QDebug>
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
    void afficheCube3D( QLabel* label);
    void controlSave();


public:
    explicit AffichePlan(QWidget *parent = 0);
    ~AffichePlan();
    void ouvrir();
    void setName(QString nom);
    QString getName();
    void setEmpl(QString empl);
    QString getEmpl();


private:
    Ui::AffichePlan *ui;
    Cube c;
    QString nom;
    QString empl;

    QPushButton* buttons[90];

};

#endif // AFFICHEPLAN_H
