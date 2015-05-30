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
    pal.setColor(QPalette::Window,QColor(234,237,229,255));
    a.setPalette(pal);


    MainWindow w;
    w.show();



   // GestionFichier g;
   // QList<QVector3D> l=g.parser(":/texte/parser.txt");
    return a.exec();
}
