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
    pal.setColor(QPalette::Window,QColor(143,181,184,255));
    a.setPalette(pal);

    MainWindow w;
    w.show();

    return a.exec();
}
