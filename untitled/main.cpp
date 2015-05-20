#include "testui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testUI w;
    w.show();

    return a.exec();
}
