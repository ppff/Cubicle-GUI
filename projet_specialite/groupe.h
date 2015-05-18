#ifndef GROUPE_H
#define GROUPE_H

#include "global.h"
#include "motif.h"

/* Description :
 * Cette classe représente un ensemble de motifs.
 */

class Groupe
{
    public:

        explicit Groupe(QString const& nom = "PasDeNom");

        void ajouter_motif(Motif const& motif);
        void ajouter_motifs(QList<Motif> const& motifs);

        Motif motif_suivant();
        Motif motif_precedent();
        Motif motif_actuel();
        Motif motif_premier();
        Motif motif_dernier();

        void translater(Translations sens);

        unsigned recuperer_numero_motif_actuel() const;
        unsigned recuperer_nombre_de_motifs() const;
        QString recuperer_nom() const;


    private:

        QString _nom;
        QList<Motif> _motifs;
        int _indexCourant;

};

#endif // GROUPE_H
