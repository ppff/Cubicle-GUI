#include "mainwindow.h"
#include <QApplication>
#include"led.h"
#include "plan.h"
#include "iostream"
#include "cube.h"
#include <QPalette>
#include "testAxeEtSphere.h"
#include "simulation_cube.h"

//extern "C" int* parser_file(const char* name);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPalette pal=a.palette();
    pal.setColor(QPalette::Window,QColor(234,237,229,255));
    a.setPalette(pal);

    MainWindow w;
    w.show();
    int* tab;
    const char* t="parser.txt";
   // tab=parser_file(t);

    return a.exec();
}
