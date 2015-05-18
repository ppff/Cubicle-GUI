#include "memoireinterne.h"

MemoireInterne::MemoireInterne(QList<Groupe> const& groupes, QObject *parent) :  QObject(parent), _groupes(groupes)
{
    _groupeActuel = 0;
}

void MemoireInterne::demarrer()
{
    envoyer_points();
    envoyer_noms();
}

void MemoireInterne::envoyer_points()
{
    emit nouveaux_points(motif_actuel().recuperer_points());
}

void MemoireInterne::envoyer_noms()
{
    emit nom_groupe( generer_nom(_groupeActuel, (int)_groupes.size()), groupe_actuel().recuperer_nom() );
    emit nom_motif ( generer_nom(groupe_actuel().recuperer_numero_motif_actuel(), groupe_actuel().recuperer_nombre_de_motifs()), motif_actuel().recuperer_nom() );
}

QString MemoireInterne::generer_nom(unsigned numero, unsigned max) const
{
    return QString(QString::number(numero+1)+QString("/")+QString::number(max));
}

void MemoireInterne::groupe_suivant()
{
    _groupeActuel = _groupeActuel + 1 < _groupes.size() ? _groupeActuel + 1 : 0;
    envoyer_points();
    envoyer_noms();
}

void MemoireInterne::groupe_precedent()
{
    _groupeActuel = _groupeActuel - 1 >= 0 ? _groupeActuel - 1 : _groupes.size() - 1;
    envoyer_points();
    envoyer_noms();
}

void MemoireInterne::motif_suivant()
{
    _groupes[_groupeActuel].motif_suivant();
    envoyer_points();
    envoyer_noms();
}

void MemoireInterne::motif_precedent()
{
    _groupes[_groupeActuel].motif_suivant();
    envoyer_points();
    envoyer_noms();
}

void MemoireInterne::translater(Translations sens)
{
    _groupes[_groupeActuel].translater(sens);
    envoyer_points();
    envoyer_noms();
}
