#include "mainwindow.h"
#include "selection_plan.h"
#include "creationfichier.h"
#include "boutonaffichecube.h"
#include <QApplication>
#include"led.h"
#include "plan.h"
#include "iostream"
#include "cube.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //Selection_Plan s;
    //s.show();
    //CreationFichier c;
    //c.show();
    BoutonAfficheCube b;
    b.show();
    return a.exec();
}
