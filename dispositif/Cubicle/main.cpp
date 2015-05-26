#include "mainwindow.h"
#include <QApplication>
#include"led.h"
#include "plan.h"
#include "iostream"
#include "cube.h"
#include "personbutton.h"
#include <QPalette>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPalette pal=a.palette();
    pal.setColor(QPalette::Window, Qt ::white);
    a.setPalette(pal);


    MainWindow w;
    w.show();


    return a.exec();
}
