#ifndef MEMOIREINTERNE_H
#define MEMOIREINTERNE_H

#include "global.h"
#include "groupe.h"
#include "motif.h"

/* Description :
 * Cette classe permet de manipuler les groupes et motifs stockés dans le cube.
 */

class MemoireInterne : public QObject
{
    Q_OBJECT

    public:

        explicit MemoireInterne(QList<Groupe> const& groupes, QObject *parent = 0);

        inline Groupe groupe_actuel() const
        {
            return _groupes.at(_groupeActuel);
        }

        inline Motif motif_actuel() const
        {
            return groupe_actuel().motif_actuel();
        }

        void demarrer();


    private:

        void envoyer_points();
        void envoyer_noms();
        QString generer_nom(unsigned numero, unsigned max) const;

        QList<Groupe> _groupes;
        int _groupeActuel;


    signals:

        void nouveaux_points(QList<QVector3D> const& points);
        void nom_groupe(QString const& numero, QString const& nom);
        void nom_motif(QString const& numero, QString const& nom);


    public slots:

        void groupe_suivant();
        void groupe_precedent();
        void motif_suivant();
        void motif_precedent();
        void translater(Translations sens);

};

#endif // MEMOIREINTERNE_H
