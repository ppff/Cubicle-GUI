#include "mainwindow.h"
#include "selection_plan.h"
#include "creationfichier.h"
#include <QApplication>
#include"led.h"
#include "plan.h"
#include "iostream"
#include "cube.h"
#include "afficheplan.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /////////////Démo allumer une led/////////////////////////////////////
  /* Dialog d;
    d.show();*/
    //////////////////////////////////////////////////////////////////////




    ///////////Démo Affichage d'un plan de led///////////////////////////
    AffichePlan aff;
    aff.show();


    /////////////////////////////////////////////////////////////////////





    ///////////////////////test des classes led, cube et plan/////////////
/*
   Plan p=Plan() ;
   std:: cout << "le plan"<< '\n' ;
   std:: cout << p.getLed(0,1).getEtat() << '\n' ;
   Cube c=Cube();
   std:: cout << c.getListHor()->first().getLed(0,0).getEtat() << '\n' ;
   */
   /////////////////////////////////////////////////////////////////////
    //MainWindow w;
    //w.show();


    //Selection_Plan s;
    //s.show();
    CreationFichier c;
    c.show();
    return a.exec();
}
