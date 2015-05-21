#include "afficheplan.h"
#include "ui_afficheplan.h"
#include <strstream>
#include <string>
#include <sstream>
#include <iostream>
#include <QPushButton>
#include <QSignalMapper>

using namespace std;

AffichePlan::AffichePlan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AffichePlan)
{
    ui->setupUi(this);
    this->c=Cube();

    QSignalMapper *signalMapper = new QSignalMapper(this);

    for (int i = 0; i < 9; i++) {
        for (int j=0;j<9; j++){
           buttons[i] = new QPushButton("", this);
           buttons[i]->setIcon(QIcon(":/icone/ledEteinte.jpeg"));
           buttons[i]->setGeometry(30, 30, 30, 30);
           buttons[i]->move(30*i+50, 30*j+50);


            QString lig=QString::number(i);
            QString col=QString::number(i);
             std:: cout << & lig << '\n' ;

      //    QWidget::connect(buttons[i], SIGNAL(clicked()), this, SLOT(controlLed()));
          connect(buttons[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
          signalMapper->setMapping(buttons[i], lig);
          connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(controlLed(const QString &)));
       }

    }

}

void AffichePlan:: afficheLed(const QString & valeur)
{

}

void AffichePlan::controlLed(const QString & valeur){
   // std:: cout << "le bouton"<< '\n' ;
 //  std:: cout << & valeur << '\n' ;
   Led l= this->c.getListHor()->first().getLed(0,0);
   std:: cout << "led etat"<< '\n' ;
   std:: cout << l.getEtat() << '\n' ;
   l.modifierEtat();
   Plan p1=c.getListHor()->first();
   Plan p2=c.getListVer()->first();
   p1.updatePlan(l,0,0);
   p2.updatePlan(l,0,0);
   c.updateCube(p1,0,0);
   c.updateCube(p2,1,0);

}

AffichePlan::~AffichePlan()
{
    delete ui;
}
