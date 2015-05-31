#ifndef GESTIONFICHIER_H
#define GESTIONFICHIER_H
#include <QString>
#include <QFile>
#include"cube.h"
#include <QDebug>
#include <QString>
#include <QVector3D>




//#ifdef __cplusplus

class GestionFichier
{
public:
    GestionFichier();
    void ouvrir(QString empl,Cube c);
    void modifierFichier(QString newLine, QString empl);
    QString getLinePlan(const int nplan,const int nligne,Cube c);
    QList<QVector3D> parser(QString empl);
    QList<QVector3D> tabToVector3D(int* tab);
};
/*
#else
    typedef
    struct GestionFichier
    GestionFichier;
#endif

#ifdef __cplusplus
extern "C" {
#endif
    #if defined(__STDC__) || defined(__cplusplus)
    extern int* parser_file(const char*); /* ANSI C prototypes */
 /*   extern GestionFichier* cplusplus_callback_function(GestionFichier*);
#else
    extern void c_function(); /* K&R style */
//    extern GestionFichier* cplusplus_callback_function();
/*#endif

#ifdef __cplusplus
}
#endif

*/

#endif // GESTIONFICHIER_H
