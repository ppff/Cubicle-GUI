#include "global.h"

#include "mainwindow.h"
#include "simulation_cube.h"

#include "memoireinterne.h"
#include "cartesd.h"

int main(int argc, char *argv[])
{
    //Instances
    QApplication a(argc, argv);

    MemoireInterne mem(CarteSD::extraire_groupes());
    MainWindow controle;
    Simulation_cube leds;

    //Connexions
    QObject::connect(&controle, SIGNAL(translation(Translations)), &mem, SLOT(translater(Translations)));
    QObject::connect(&controle, SIGNAL(groupe_precedent()), &mem, SLOT(groupe_precedent()));
    QObject::connect(&controle, SIGNAL(groupe_suivant()), &mem, SLOT(groupe_suivant()));
    QObject::connect(&controle, SIGNAL(motif_precedent()), &mem, SLOT(motif_precedent()));
    QObject::connect(&controle, SIGNAL(motif_suivant()), &mem, SLOT(motif_suivant()));

    QObject::connect(&mem, SIGNAL(nouveaux_points(QList<QVector3D>)), &leds, SLOT(recevoir_nouveaux_points(QList<QVector3D>)));

    QObject::connect(&mem, SIGNAL(nom_groupe(QString, QString)), &controle, SLOT(modifier_groupe(QString,QString)));
    QObject::connect(&mem, SIGNAL(nom_motif(QString, QString)), &controle, SLOT(modifier_motif(QString,QString)));

    //Ouverture
    leds.resize(600, 600);
    leds.show();

    controle.show();

    //Lancement
    mem.demarrer();

    return a.exec();
}
