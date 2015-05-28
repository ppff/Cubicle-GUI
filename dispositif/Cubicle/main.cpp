#include "mainwindow.h"
#include <QApplication>
#include"led.h"
#include "plan.h"
#include "iostream"
#include "cube.h"
#include <QPalette>
#include "testAxeEtSphere.h"
#include "simulation_cube.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPalette pal=a.palette();
    pal.setColor(QPalette::Window, Qt ::white);
    a.setPalette(pal);


    MainWindow w;


   //MainWindow *mainwindow = MainWindow::getInstance();
  // mainwindow->show();
    w.show();

    //testAxeEtSphere t;
    //t.show();

    //simulation_cube s;
  //  s.show();

    return a.exec();
}
