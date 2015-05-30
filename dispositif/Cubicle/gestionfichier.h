#ifndef GESTIONFICHIER_H
#define GESTIONFICHIER_H
#include <QString>
#include <QFile>
#include"cube.h"
#include <QDebug>
#include <QString>
#include <QVector3D>

class GestionFichier
{
public:
    GestionFichier();
    void ouvrir(QString empl,Cube c);
    void modifierFichier(QString newLine, QString empl);
    QString getLinePlan(const int nplan,const int nligne,Cube c);
    QList<QVector3D> parser(QString empl);
};

#endif // GESTIONFICHIER_H
