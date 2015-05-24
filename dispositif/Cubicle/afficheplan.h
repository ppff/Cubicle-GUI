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

/*private:
     static AffichePlan* instance;
protected:
    AffichePlan(QDialog* = NULL);
public:
    static AffichePlan* getInstance();
*/

public slots:

    void afficheLed(const int i, const int j, const int etat);
    void controlLed(const QString & valeur);
    void afficheCube3D( QLabel* label);
    void controlSave();
    void controlQuit();
    void controlDelete();
    void afficheListePlan1();
    void afficheListePlan2();
    void afficheListePlan3();
    void affichePlanLed(const QString & valeur);


public:
    explicit AffichePlan(QWidget *parent = 0);
    ~AffichePlan();
    void ouvrir();
    void setName(QString nom);
    QString getName();
    void setEmpl(QString empl);
    QString getEmpl();
    void modifierFichier(QString newLine);
    QString getLinePlan(const int nplan,const int nligne);
    void deleteCube3D();
    void deletePlanLed(int i);
    void setOrientationPlan(int i);
    int getOrientationPlan();
    int getNumeroPlan();
    void setNumeroPlan(int i);
    void desactivePlan(int i);


private:
    Ui::AffichePlan *ui;
    Cube c;
    QString nom;
    QString empl;

    QPushButton* buttons[90];
    int OrienPlan;
    int NumeroPlan;
    QPushButton* plans[30];
    QPushButton*  fleche_bas;

};

#endif // AFFICHEPLAN_H
