#include "mainwindow.h"
#include <QApplication>
#include "dialog.h"
#include"led.h"
#include "plan.h"
#include "iostream"
#include "cube.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Dialog d;
    d.show();
    w.show();

    ///////////////////////test des classes led, cube et plan/////////////
/*
   Plan p=Plan() ;
   std:: cout << "le plan"<< '\n' ;
   std:: cout << p.getLed(0,1).getEtat() << '\n' ;
   Cube c=Cube();
   std:: cout << c.getListHor()->first().getLed(0,0).getEtat() << '\n' ;
   */
   /////////////////////////////////////////////////////////////////////

    return a.exec();
}
