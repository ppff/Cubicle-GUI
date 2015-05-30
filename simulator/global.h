#ifndef GENERAL_HPP
#define GENERAL_HPP

//Includes
#include <QtOpenGL>
#include <QGLWidget>
#include "adapt.h"

#include <QApplication>
#include <QObject>
#include <QMainWindow>
#include <QVector3D>
#include <QDebug>
#include <QList>
#include <QFile>
#include <QTextStream>

//Constantes
#define LONGUEUR_MAX_NOM 15 //Le nom d'un groupe ou d'un motif ne peut faire qu'un certain nombre de caractères.
#define CHEMIN_VERS_CARTE_SD QString("../CarteSD/")
//Messages (NB : qDebug ajoute des espaces entre les chaines).
extern "C"
{
    #define DEBUG_MSG(...)     \
    { 	   \
        do      \
        {	   \
            qDebug()      \
            << "[DEBUG]"		\
            << "(" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ")"	\
            << __VA_ARGS__		\
            << "."		\
            ;		\
        } while( 0 );     \
    }

    #define ERROR_MSG(...)     \
    { 	   \
        do      \
        {	   \
            qDebug()      \
            << "[ERROR]"		\
            << "(" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ")"	\
            << __VA_ARGS__		\
            << "."	\
            ;		\
        } while( 0 );     \
    }

    #define ERROR_QUIT(...)     \
    { 	   \
        do      \
        {	   \
            ERROR_MSG(__VA_ARGS__) \
            exit(EXIT_FAILURE);		\
        } while( 0 ); \
    }
} //extern C

#endif
