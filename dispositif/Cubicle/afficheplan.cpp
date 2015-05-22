#include "afficheplan.h"
#include "ui_afficheplan.h"
#include <strstream>
#include <string>
#include <sstream>
#include <iostream>
#include <QPushButton>
#include <QSignalMapper>
#include <QLabel>
#include <QGridLayout>


using namespace std;

AffichePlan::AffichePlan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AffichePlan)
{
    ui->setupUi(this);
    this->c=Cube();
    QLabel* l=ui->label;
    this->afficheCube3D(l);

    QSignalMapper *signalMapper = new QSignalMapper(this);

   for (int i = 0; i < 9; i++) {
        for (int j=0;j<9; j++){
           QString col=QString::number(i);
           QString lig=QString::number(j);
           QString text=lig+col;

           int num=text.toInt(false,10);
           buttons[num] = new QPushButton("", this);
           buttons[num]->setIcon(QIcon(":/icone/ledEteinte.jpeg"));
           buttons[num]->setGeometry(30, 30, 30, 30);
           buttons[num]->move(30*i+50, 30*j+50);

          connect(buttons[num], SIGNAL(clicked()), signalMapper, SLOT(map()));
          signalMapper->setMapping(buttons[num], text);

       }
}
    connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(controlLed(const QString &)));

}


void AffichePlan::controlLed(const QString & valeur){

   QString stri=valeur[0];
   QString strj=valeur[1];
   int i=stri.toInt(false,10);
   int j=strj.toInt(false,10);

   Led l= this->c.getListHor()->first().getLed(i,j);
   l.modifierEtat();
   Plan p1=c.getListHor()->first();
   Plan p2=c.getListVer()->first();
   p1.updatePlan(l,i,j);
   p2.updatePlan(l,i,j);
   c.updateCube(p1,0,0);
   c.updateCube(p2,1,0);

   afficheLed(i,j,l.getEtat());

}
void AffichePlan:: afficheLed(const int i, const int j,const  int etat )
{
       QString lig=QString::number(i);
       QString col=QString::number(j);
       QString text=lig+col;
       int num=text.toInt(false,10);

    if(etat==0){
        this->buttons[num]->setIcon(QIcon(":/icone/ledEteinte.jpeg"));
        this->buttons[num]->setGeometry(30, 30, 30, 30);
        this->buttons[num]->move(30*j+50, 30*i+50);
      }
    else {
        this->buttons[num]->setIcon(QIcon(":/icone/led.jpeg"));
        this->buttons[num]->setGeometry(30, 30, 30, 30);
        this->buttons[num]->move(30*j+50, 30*i+50);
    }

}

void AffichePlan:: afficheCube3D( QLabel* label){
    label->setPixmap(QPixmap(":/icone/cubicle.jpg"));
    label->move(800,300);
    label->adjustSize();
    label->show();


    for (int i = 0; i < 9; i++) {
        for (int j=0;j<9; j++){

           QString text = QString::number(i);
           buttons[i] = new QPushButton("", this);
           buttons[i]->setIcon(QIcon(":/icone/ledEteinte.jpeg"));
           buttons[i]->setGeometry(30, 30, 30, 30);
           buttons[i]->move(30*i+50, 30*j+50);

           connect(buttons[i], SIGNAL(clicked()), this, SLOT(affiche(i)));

       }

    }

}

void AffichePlan:: affiche(const int i)
{

}

void AffichePlan::controlLed(const int i,const int j){
    std:: cout << "le bouton"<< '\n' ;
    std:: cout << i+" "+j << '\n' ;
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
