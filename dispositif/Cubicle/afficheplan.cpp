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
    QObject::connect(ui->pushButton_2,SIGNAL(clicked()),
                          this, SLOT(controlQuit()));

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
/////////celà dépend de quelle orientation on choisit: spécifique vue dessus  ori=0//////
   Led l= this->c.getList1()->first().getLed(i,j);
   l.modifierEtat();
   Plan p1=c.getList1()->first();
   Plan p2=c.getList2()->value(j);
   Plan p3=c.getList3()->value(i);
   p1.updatePlan(l,i,j,0,0,0);//0,0 c'est changement de la vue de dessue à vue de dessus
   p2.updatePlan(l,i,j,0,0,1); //premier 0: 1er plan ,  dessus -> gauche
   p3.updatePlan(l,i,j,0,0,2);// dessus -> face
   c.updateCube(p1,0,0); //ori et pos
   c.updateCube(p2,1,j);
   c.updateCube(p3,2,i);
   //////ori==1//////////////////////////////////////////////////////////////////////////////
/*   int ori;
   int nplan;
   switch (ori){
   case 0:  Led l= this->c.getList1()->value(nplan).getLed(i,j); break;
   case 1:  Led l= this->c.getList2()->value(nplan).getLed(i,j); break;
   case 2:  Led l= this->c.getList3()->value(nplan).getLed(i,j); break;
   }

   l.modifierEtat();
   Plan p1=c.getList1()->value(nplan);
   Plan p2=c.getList2()->value(j);
   Plan p3=c.getList3()->value(i);
   p1.updatePlan(l,i,j,nplan,ori,0);//0,0 c'est changement de la vue de dessue à vue de dessus
   p2.updatePlan(l,i,j,nplan,ori,1); //premier 0: 1er plan ,  dessus -> gauche
   p3.updatePlan(l,i,j,nplan,ori,2);// dessus -> face
   c.updateCube(p1,0,nplan); //ori et pos
   c.updateCube(p2,1,j);
   c.updateCube(p3,2,i);*/
/////////////////////////////////////////////////////////////////////////////////////////
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
    QString readLine;
    QString newLine;
    for (int k=0;k<3;k++){
        readLine= flux.readLine()+'\n';
        newLine+=readLine;
    }
    int nplan=0;// numéro du plan
    int nligne=0; //numéro de la ligne

   for(int cntP=0;cntP<9;cntP++){
       for(int cntL=0;cntL<9;cntL++){
           readLine= flux.readLine()+'\n';
           newLine+=getLinePlan(nplan,nligne)+'\n';
           nligne++; //passer à la ligne suivante
       }
        readLine= flux.readLine()+'\n';
        newLine+=readLine; //recopier la ligne #1 par exemple
        nligne=0;
        nplan++;// passer au plan suivant
   }
   file.close();
   modifierFichier(newLine);
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

QString AffichePlan::getLinePlan(int nplan,int nligne){
    QString str="";
    QString etat;
    for(int i=0;i<9;i++){
       Led l=this->c.getList1()->value(nplan).getLed(nligne,i);
       int e=l.getEtat() ;
       etat=QString::number(e);
       str+=etat;
    }
    return str;
}

void AffichePlan::modifierFichier(QString newLine){
    QFile file(this->empl);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"le fichier n'est pas ouvert";
       return;
    }
    QTextStream out(&file);
    out << newLine;
    file.flush();
    file.close();
}

void AffichePlan::quit(){

}

void AffichePlan::controlQuit(){

}


AffichePlan::~AffichePlan()
{
    delete ui;
}
