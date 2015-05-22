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
#include <QTextStream>

using namespace std;

AffichePlan::AffichePlan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AffichePlan)
{
    ui->setupUi(this);
    this->c=Cube();
    QLabel* l=ui->label;
    this->afficheCube3D(l);
    QObject::connect(ui->pushButton, SIGNAL(clicked()),
                          this, SLOT(controlSave()));

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

   Led l= this->c.getList1()->first().getLed(i,j);
   l.modifierEtat();
   Plan p1=c.getList1()->first();
   Plan p2=c.getList2()->first();
   Plan p3=c.getList3()->first();
   p1.updatePlan(l,i,j);
   p2.updatePlan(l,i,j);
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
}

void AffichePlan::ouvrir(){

    QFile file(this->empl);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        qDebug()<<"le fichier n'est pas ouvert";
       return;
    }

    QTextStream flux(&file);
  //  for()


 file.close();
}

void AffichePlan::setName(QString nom){
    this->nom=nom;
}

QString AffichePlan::getName(){
    return this->nom;
}

void AffichePlan::setEmpl(QString e){
    this->empl=e;
}

QString AffichePlan::getEmpl(){
    return this->empl;
}

void AffichePlan::controlSave(){
    this->ouvrir();

}


AffichePlan::~AffichePlan()
{
    delete ui;
}
