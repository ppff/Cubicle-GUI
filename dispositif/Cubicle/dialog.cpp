#include "ui_dialog.h"
#include <iostream>

#include "QIcon"
#include "dialog.h"
#include "cube.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{   this->c=Cube();
    ui->setupUi(this);

    ui->pushButton->setIcon(QIcon(":/icone/led.jpeg"));


    QObject::connect(ui->pushButton, SIGNAL(clicked()),
                          this, SLOT(controlLed()));


}

void Dialog::controlLed(){

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

Dialog::~Dialog()
{
    delete ui;
}

