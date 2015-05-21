#ifndef AFFICHEPLAN_H
#define AFFICHEPLAN_H
#include "cube.h"
#include <QDialog>

namespace Ui {
class AffichePlan;
}

class AffichePlan : public QDialog
{
    Q_OBJECT
public slots:
    void affiche(const int i);
public slots:
    void controlLed(const int i, const int j);

public:
    explicit AffichePlan(QWidget *parent = 0);
    ~AffichePlan();

private:
    Ui::AffichePlan *ui;
    Cube c;
    QPushButton *buttons[81];
};

#endif // AFFICHEPLAN_H
