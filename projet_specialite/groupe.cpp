#include "groupe.h"

Groupe::Groupe(QString const& nom) : _nom(nom)
{
    _motifs.clear();
    _indexCourant = 0;

    if (nom.size() > LONGUEUR_MAX_NOM)
    {
        DEBUG_MSG("Le nom de groupe" << nom << "a été tronqué");
        _nom.truncate(LONGUEUR_MAX_NOM);
    }
}

void Groupe::ajouter_motif(Motif const& motif)
{
    _motifs.append(motif);
}

void Groupe::ajouter_motifs(QList<Motif> const& motifs)
{
    _motifs += motifs;
}

Motif Groupe::motif_suivant()
{
    _indexCourant = _indexCourant + 1 < _motifs.size() ? _indexCourant + 1 : 0;
    return motif_actuel();
}

Motif Groupe::motif_precedent()
{
    _indexCourant = _indexCourant - 1 >= 0 ? _indexCourant - 1 : _motifs.size() - 1;
    return motif_actuel();
}

Motif Groupe::motif_actuel()
{
    return _motifs.at((int)_indexCourant);
}

Motif Groupe::motif_premier()
{
    _indexCourant = 0;
    return motif_actuel();
}

Motif Groupe::motif_dernier()
{
    _indexCourant = _motifs.size() - 1;
    return motif_actuel();
}

void Groupe::translater(Translations sens)
{
    _motifs[_indexCourant].translater(sens);
}

unsigned Groupe::recuperer_numero_motif_actuel() const
{
    return _indexCourant;
}

unsigned Groupe::recuperer_nombre_de_motifs() const
{
    return (unsigned)_motifs.size();
}

QString Groupe::recuperer_nom() const
{
    return _nom;
}
