#include "creefichier.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CreeFichier w;
    w.show();

    return a.exec();
}
