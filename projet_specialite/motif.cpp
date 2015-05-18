#include "motif.h"

Motif::Motif(QString const& nom, QList<QVector3D> const& points) : _nom(nom), _points(points)
{
    _translation = QVector3D(0,0,0);

    if (nom.size() > LONGUEUR_MAX_NOM)
    {
        DEBUG_MSG("Le nom de motif" << nom << "a été tronqué");
        _nom.truncate(LONGUEUR_MAX_NOM);
    }
}

void Motif::translater(Translations sens)
{
    QVector3D vecteur(0,0,0);

    switch (sens) //On prend le repère Cubicle
    {
        case Haut     : vecteur = QVector3D(0,0,1);  break;
        case Bas      : vecteur = QVector3D(0,0,-1); break;
        case Gauche   : vecteur = QVector3D(0,-1,0); break;
        case Droite   : vecteur = QVector3D(0,1,0);  break;
        case Devant   : vecteur = QVector3D(1,0,0);  break;
        case Derriere : vecteur = QVector3D(-1,0,0); break;
        default : ERROR_MSG("Sens inconnu :" << sens); break;
    }

    _translation += vecteur;
}

QList<QVector3D> Motif::recuperer_points() const
{
    QList<QVector3D> points(_points);

    for (QVector3D & v : points)
    {
        v += _translation;
    }

    return points;
}

QString Motif::recuperer_nom() const
{
    return _nom;
}
