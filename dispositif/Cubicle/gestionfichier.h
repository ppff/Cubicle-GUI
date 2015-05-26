#ifndef GESTIONFICHIER_H
#define GESTIONFICHIER_H
#include <QString>
#include <QFile>
#include"cube.h"
#include <QDebug>

class GestionFichier
{
public:
    GestionFichier();
    void ouvrir(QString empl,Cube c);
    void modifierFichier(QString newLine, QString empl);
    QString getLinePlan(const int nplan,const int nligne,Cube c);
};

#endif // GESTIONFICHIER_H
