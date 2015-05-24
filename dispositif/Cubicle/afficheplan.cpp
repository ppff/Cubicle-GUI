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
#include <QInputDialog>
#include <QMessageBox>
#include <QPainter>
#include "personbutton.h"

using namespace std;

AffichePlan::AffichePlan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AffichePlan)
{
    ui->setupUi(this);
    this->c=Cube();
    QLabel* l=ui->label;
    this->setWindowIcon(QIcon("cubicle.jpg"));
    this->setWindowTitle("Cubicle");

    QObject::connect(ui->pushButton, SIGNAL(clicked()),
                            this, SLOT(controlSave()));
    QObject::connect(ui->pushButton_2,SIGNAL(clicked()),
                            this, SLOT(controlQuit()));
    QObject::connect(ui->pushButton_3,SIGNAL(clicked()),
                            this, SLOT(controlDelete()));

    this->afficheCube3D(l);
    this->desactivePlan(0);
    this->deletePlanLed(0);
}

/*
AffichePlan* AffichePlan:: getInstance(){
    if(!instance) {
                instance = new AffichePlan();
                cout << "getInstance(): First instance\n";
                return instance;
            }
            else {
                cout << "getInstance(): previous instance\n";
                return instance;
            }

        }
*/
void AffichePlan::affichePlanLed(const QString & valeur){
    QString stori=valeur[0];
    QString stnplan=valeur[1];
    int ori=stori.toInt(false,10);
    int nplan=stnplan.toInt(false,10);
    this->setNumeroPlan(nplan);
    QSignalMapper *signalMapper = new QSignalMapper(this);

   for (int i = 0; i < 9; i++) {
        for (int j=0;j<9; j++){
           QString col=QString::number(i);
           QString lig=QString::number(j);
           QString text=lig+col;

           int num=text.toInt(false,10);
           buttons[num]->setVisible(true);
           buttons[num]->setGeometry(30, 30, 30, 30);
           buttons[num]->move(30*i+50, 30*j+50);
           Led l;
           switch(this->OrienPlan){
                case 0: l=c.getList1()->value(this->NumeroPlan).getLed(j,i); break;
                case 1: l=c.getList2()->value(this->NumeroPlan).getLed(j,i); break;
                case 2: l=c.getList3()->value(this->NumeroPlan).getLed(j,i); break;
           }

           if(l.getEtat()==0){
               buttons[num]->setIcon(QIcon(":/icone/atomeblanc.jpeg"));
           }
           else {
               buttons[num]->setIcon(QIcon(":/icone/atome.gif"));
           }

          connect(buttons[num], SIGNAL(clicked()), signalMapper, SLOT(map()));
          signalMapper->setMapping(buttons[num], text);

       }
    }
    connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(controlLed(const QString &)));
}

void AffichePlan::deletePlanLed(int nfois){

        for (int i = 0; i < 9; i++) {
             for (int j=0;j<9; j++){
                 QString col=QString::number(i);
                 QString lig=QString::number(j);
                 QString text=lig+col;
                 int num=text.toInt(false,10);
                  if(nfois==0){
                         buttons[num]=new QPushButton("",this);
                  }
                 buttons[num]->hide();
             }

    }
}

void AffichePlan::controlLed(const QString & valeur){
   QString strlig=valeur[0];
   QString strcol=valeur[1];
   int lig=strlig.toInt(false,10);
   int col=strcol.toInt(false,10);
  Led l;
   switch (this->OrienPlan){
   case 0:   l= this->c.getList1()->value(NumeroPlan).getLed(lig,col); break;
   case 1:   l= this->c.getList2()->value(NumeroPlan).getLed(lig,col); break;
   case 2:   l= this->c.getList3()->value(NumeroPlan).getLed(lig,col); break;
   }

   l.modifierEtat();
   switch(OrienPlan){
        case 0:{
       Plan p1=c.getList1()->value(this->NumeroPlan);
       Plan p2=c.getList2()->value(col);
       Plan p3=c.getList3()->value(lig);
       p1.updatePlan(l,lig,col,NumeroPlan,OrienPlan,0);
       p2.updatePlan(l,lig,col,NumeroPlan,OrienPlan,1);
       p3.updatePlan(l,lig,col,NumeroPlan,OrienPlan,2);
       c.updateCube(p1,0,NumeroPlan);
       c.updateCube(p2,1,col);
       c.updateCube(p3,2,lig);
         }break;
        case 1:{
       Plan p1=c.getList1()->value(abs(8-lig));
       Plan p2=c.getList2()->value(NumeroPlan);
       Plan p3=c.getList3()->value(abs(8-col));
       p1.updatePlan(l,lig,col,NumeroPlan,OrienPlan,0);
       p2.updatePlan(l,lig,col,NumeroPlan,OrienPlan,1);
       p3.updatePlan(l,lig,col,NumeroPlan,OrienPlan,2);
       c.updateCube(p1,0,abs(8-lig));
       c.updateCube(p2,1,NumeroPlan);
       c.updateCube(p3,2,abs(8-col));
   } break;

        case 2:{
       Plan p1=c.getList1()->value(abs(8-lig));
       Plan p2=c.getList2()->value(col);
       Plan p3=c.getList3()->value(NumeroPlan);
       p1.updatePlan(l,lig,col,NumeroPlan,OrienPlan,0);
       p2.updatePlan(l,lig,col,NumeroPlan,OrienPlan,1);
       p3.updatePlan(l,lig,col,NumeroPlan,OrienPlan,2);
       c.updateCube(p1,0,abs(8-lig));
       c.updateCube(p2,1,col);
       c.updateCube(p3,2,NumeroPlan);
   } break;
   }
   afficheLed(lig,col,l.getEtat());

}
void AffichePlan:: afficheLed(const int i, const int j,const  int etat )
{
       QString lig=QString::number(i);
       QString col=QString::number(j);
       QString text=lig+col;
       int num=text.toInt(false,10);

    if(etat==0){
        this->buttons[num]->setIcon(QIcon(":/icone/atomeblanc.jpeg"));
      }
    else {
        this->buttons[num]->setIcon(QIcon(":/icone/atome.gif"));
    }

}

void AffichePlan:: afficheCube3D( QLabel* label){
    label->setPixmap(QPixmap(":/icone/nvcube.jpeg"));
    label->move(860,380);
    label->adjustSize();
    label->show();
    this->fleche_bas=new QPushButton("",this);
    fleche_bas->setIcon(QIcon(":/icone/bas.png"));
    fleche_bas->setGeometry(960,390,40,40);
    QObject::connect(fleche_bas, SIGNAL(clicked()),
                          this, SLOT(afficheListePlan1()));
    QPushButton * fleche_gauche=new QPushButton("",this);
    fleche_gauche->setIcon(QIcon(":/icone/GAUCHE.png"));
    fleche_gauche->setGeometry(1060,480,40,40);
    QObject::connect(fleche_gauche, SIGNAL(clicked()),
                          this, SLOT(afficheListePlan2()));
    QPushButton * fleche_face=new QPushButton("",this);
    fleche_face->setIcon(QIcon(":/icone/AR.png"));
    fleche_face->setGeometry(950,500,40,40);
    QObject::connect(fleche_face, SIGNAL(clicked()),
                          this, SLOT(afficheListePlan3()));

}

void AffichePlan::deleteCube3D(){
    ui->label->setPixmap(QPixmap());
   ui->label->repaint();
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


void AffichePlan::controlQuit(){
    int reponse = QMessageBox::question(this, "Quit", " Are you sure you want to quit ?");

        if (reponse == QMessageBox::Yes)
        {
            this->close();
        }
}

void AffichePlan::controlDelete(){
    int reponse = QMessageBox::question(this, "Quit", " Are you sure you want to delete this pattern ?");

        if (reponse == QMessageBox::Yes)
        {
            QFile file(empl);
            file.remove();
            this->deleteCube3D();
            this->deletePlanLed(1);

        }
}

int AffichePlan::getOrientationPlan()
{
   return OrienPlan;
}

void AffichePlan::setOrientationPlan(int i)
{
   OrienPlan=i;
}

int AffichePlan::getNumeroPlan()
{
   return NumeroPlan;
}

void AffichePlan::setNumeroPlan(int i)
{
   NumeroPlan=i;
}


void AffichePlan::afficheListePlan1(){
    desactivePlan(1);
    deletePlanLed(1);
    QSignalMapper *signalMapper = new QSignalMapper(this);
         for (int j=0;j<9; j++){ //les plans vue de dessus
           setOrientationPlan(0);
           QString ori=QString::number(0);
           QString nplan=QString::number(j);
           QString text=ori+nplan;
           int num=text.toInt(false,10);
           plans[num]->setVisible(true);
           plans[num]->setGeometry(100, 50, 250, 100);
           plans[num]->move(500-20*j, 50*j+50);

          connect(plans[num], SIGNAL(clicked()), signalMapper, SLOT(map()));
          signalMapper->setMapping(plans[num], text);
        }
    connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(affichePlanLed(const QString &)));

}


void AffichePlan::afficheListePlan2(){
    desactivePlan(1);
     deletePlanLed(1);
 QSignalMapper *signalMapper = new QSignalMapper(this);
 for (int j=0;j<9; j++){ //les plans vue de gauche
    setOrientationPlan(1);
    QString ori=QString::number(1);
    QString nplan=QString::number(j);
    QString text=ori+nplan;

    int num=text.toInt(false,10);
    plans[num]->setVisible(true);
    plans[num]->setIcon(QIcon(":/icone/ledEteinte.jpeg"));
    plans[num]->setGeometry(100, 50, 250, 100);
    plans[num]->move(500-j*50, 30*j+50);

   connect(plans[num], SIGNAL(clicked()), signalMapper, SLOT(map()));
   signalMapper->setMapping(plans[num], text);

    }
   connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(affichePlanLed(const QString &)));

}

void AffichePlan::afficheListePlan3(){
    desactivePlan(1);
     deletePlanLed(1);
    QSignalMapper *signalMapper = new QSignalMapper(this);
    for (int j=0;j<9; j++){ //les plans vue de face
       setOrientationPlan(2);
       QString ori=QString::number(2);
       QString nplan=QString::number(j);
       QString text=ori+nplan;

       int num=text.toInt(false,10);
       plans[num]->setVisible(true);
       plans[num]->setGeometry(100, 50, 250, 100);
       plans[num]->move(500-20*j, 50*j+50);

       connect(plans[num], SIGNAL(clicked()), signalMapper, SLOT(map()));
      signalMapper->setMapping(plans[num], text);
   }
      connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(affichePlanLed(const QString &)));

}

void AffichePlan::desactivePlan(int niemefois){

        for (int j=0;j<9; j++){
           QString ori=QString::number(0);
           QString nplan=QString::number(j);
           QString text=ori+nplan;
           int num=text.toInt(false,10);
           if(niemefois==0){  //il crée le bouton que la première fois
            plans[num]=new QPushButton(nplan,this);
           }
           plans[num]->hide();
        }

        for (int j=0;j<9; j++){
           QString ori=QString::number(1);
           QString nplan=QString::number(j);
           QString text=ori+nplan;
           int num=text.toInt(false,10);
           if(niemefois==0){
             plans[num]=new QPushButton(nplan,this);
           }
           plans[num]->hide();
        }
        for (int j=0;j<9; j++){
           QString ori=QString::number(2);
           QString nplan=QString::number(j);
           QString text=ori+nplan;
           int num=text.toInt(false,10);
           if(niemefois==0){
              plans[num]=new QPushButton(nplan,this);
           }
           plans[num]->hide();
          }



}


AffichePlan::~AffichePlan()
{
    delete ui;
}
