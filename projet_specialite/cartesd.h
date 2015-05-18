#ifndef CARTESD
#define CARTESD

#include "global.h"

#include "groupe.h"
#include "motif.h"

/* Description :
 * Ce couple .h/.cpp contient les fonctions qui sont exécutées sur le dossier 'CarteSD' à l'ouverture du programme.
 * Il faut donc modifier ces fichiers suivant le format des fichiers choisi.
 */

namespace CarteSD
{
    QList<Groupe> extraire_groupes();

    QStringList parser_ordre();
    Groupe parser_groupe(QString const& nom_dossier);
    Motif parser_motif(QStringList const& contenu_fichier);
    QList<QVector3D> parser_plan(std::string const& plan, unsigned num_plan);

    //Trucs pratiques
    QStringList lire_fichier(QString const& chemin);
    void inverser_chaines(std::string & s1, std::string & s2);
    void retourner_chaine(std::string & s);

} //namespace CarteSD

#endif // CARTESD

