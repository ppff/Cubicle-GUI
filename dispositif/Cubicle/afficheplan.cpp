#include "afficheplan.h"
#include "ui_afficheplan.h"
#include <strstream>
#include <string>
#include <sstream>
#include <iostream>
#include <QPushButton>
#include <QSignalMapper>
#include <QLabel>

using namespace std;

AffichePlan::AffichePlan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AffichePlan)
{
    ui->setupUi(this);
    this->c=Cube();
    QLabel* l=ui->label;
    QLabel* l2=ui->label_2;
    this->afficheCube3D(l2,l);


    QSignalMapper *signalMapper = new QSignalMapper(this);

    for (int i = 0; i < 9; i++) {
        for (int j=0;j<9; j++){
           QString col=QString::number(i);
           QString lig=QString::number(j);
           QString text=lig+col;
           buttons[i] = new QPushButton("", this);
           buttons[i]->setIcon(QIcon(":/icone/ledEteinte.jpeg"));
           buttons[i]->setGeometry(30, 30, 30, 30);
           buttons[i]->move(30*i+50, 30*j+50);

          connect(buttons[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
          signalMapper->setMapping(buttons[i], text);
       }
    }
    connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(controlLed(const QString &)));


}



void AffichePlan::controlLed(const QString & valeur){
    std:: cout << "le bouton"<< '\n' ;
    cout << qPrintable(valeur);
    QString stri=valeur[0];
    QString strj=valeur[1];
    int i=stri.toInt(false,10);
    int j=strj.toInt(false,10);
     std:: cout << i<< '\n' ;
      std:: cout << j<< '\n' ;
   Led l= this->c.getListHor()->first().getLed(i,j);

   std:: cout << "led etat avant changement"<< '\n' ;
   std:: cout << l.getEtat() << '\n' ;
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
    if(etat==0){
       // buttons[i] = new QPushButton("", this);
        buttons[j]->setIcon(QIcon(":/icone/ledEteinte.jpeg"));
        buttons[j]->setGeometry(30, 30, 30, 30);
        buttons[j]->move(30*j+50, 30*i+50);
        std:: cout << "j'ai fait 0"<< '\n' ;

    }
    else {
      //  buttons[i] = new QPushButton("", this);
        buttons[j]->setIcon(QIcon(":/icone/led.jpeg"));
        buttons[j]->setGeometry(30, 30, 30, 30);
        buttons[j]->move(30*j+50, 30*i+50);
        std:: cout << "j'ai fait 1"<< '\n' ;
    }

}

void AffichePlan:: afficheCube3D( QLabel* label2, QLabel* label){
    label2->setPixmap(QPixmap(":/icone/cubicle.jpg"));
    label2->move(800,300);
    label2->adjustSize();
    label2->show();
       label->setPixmap(QPixmap(":/icone/repere.jpeg"));
       label->move(600,500);
       label->adjustSize();
       label->show();

}

AffichePlan::~AffichePlan()
{
    delete ui;
}
