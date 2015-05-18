#ifndef MOTIF_H
#define MOTIF_H

#include "global.h"

/* Description :
 * Cette classe représente un motif complet : les coordonnées de ses points, s'il a été translaté, etc.
 */

enum Translations { Haut, Bas, Gauche, Droite, Devant, Derriere };

class Motif
{
    public:

        explicit Motif(QString const& nom, QList<QVector3D> const& points);

        void translater(Translations sens);

        QList<QVector3D> recuperer_points() const;
        QString recuperer_nom() const;


    private:

        QString _nom;
        QList<QVector3D> _points;
        QVector3D _translation;

};

#endif // MOTIF_H
