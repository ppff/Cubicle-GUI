#include "cartesd.h"

using namespace CarteSD;

QList<Groupe> CarteSD::extraire_groupes()
{
    QList<Groupe> groupes;

    QStringList noms_groupes = parser_ordre();

    for (QString s : noms_groupes)
    {
        groupes.append(parser_groupe(s));
    }

    return groupes;
}

QStringList CarteSD::parser_ordre()
{
    return lire_fichier(CHEMIN_VERS_CARTE_SD+QString("ORDRE"));
}

Groupe CarteSD::parser_groupe(QString const& nom_dossier)
{
    Groupe g(nom_dossier);

    QDir dir(CHEMIN_VERS_CARTE_SD+nom_dossier);
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);

    QStringList motifs = dir.entryList();

    for (QString m : motifs)
    {
        g.ajouter_motif(parser_motif(lire_fichier( CHEMIN_VERS_CARTE_SD+nom_dossier+QString("/")+m )));
    }

    return g;
}

Motif CarteSD::parser_motif(QStringList const& contenu_fichier)
{
    //NB : cette fonction a été écrite en C++ standard (non QT) à l'origine, d'où la conversion en conteneurs standards.

    std::vector<std::string> contenu;

    for (int i=0 ; i<contenu_fichier.size() ; i++)
    {
        contenu.push_back(contenu_fichier.at(i).toStdString());
    }

    QString nom;

    //On récupère le nom
    if (contenu[0][0] != '@')
    {
        ERROR_QUIT("Impossible de trouver '@'");
    }

    nom = QString(contenu[0].c_str());
    nom.remove(0,1); //Pour enlever '@'

    DEBUG_MSG("Traitement du motif" << nom);

    contenu.erase(contenu.begin()); //On enlève la ligne du fichier

    //On récupère le numéro du premier plan
    int index = 0;
    while (contenu[index].find("#") == std::string::npos)
    {
        index++;
    }
    int num_p0 = contenu[index][1] - '0'; //Le numéro du premier plan peut être 0 ou 1, d'où cette subtilité.

    //On retourne les chaines
    for (unsigned int i=0 ; i<contenu.size() ; i++)
    {
        if (contenu[i].find("#") != std::string::npos)
        {
            retourner_chaine(contenu[i+1]);
            retourner_chaine(contenu[i+2]);
            retourner_chaine(contenu[i+3]);
            retourner_chaine(contenu[i+4]);
            retourner_chaine(contenu[i+5]);
            retourner_chaine(contenu[i+6]);
            retourner_chaine(contenu[i+7]);
            retourner_chaine(contenu[i+8]);
            retourner_chaine(contenu[i+9]);
        }
    }

    //On met les lignes dans l'ordre
    for (unsigned int i=0 ; i<contenu.size() ; i++)
    {
        if (contenu[i].find("#") != std::string::npos)
        {
            inverser_chaines(contenu[i+1], contenu[i+9]);
            inverser_chaines(contenu[i+2], contenu[i+8]);
            inverser_chaines(contenu[i+3], contenu[i+7]);
            inverser_chaines(contenu[i+4], contenu[i+6]);
        }
    }

    //On regroupe les séries de lignes en plans
    std::vector<std::string> tmp(contenu);
    contenu.clear();
    for (unsigned int i=0 ; i<tmp.size() ; i++)
    {
        if (tmp[i].find("#") != std::string::npos)
        {
            tmp[i+1] = tmp[i+1]+tmp[i+2]+tmp[i+3]+tmp[i+4]+tmp[i+5]+tmp[i+6]+tmp[i+7]+tmp[i+8]+tmp[i+9];

            contenu.push_back(tmp[i]);
            contenu.push_back(tmp[i+1]);

            i += 9;
        }
        else
        {
            contenu.push_back(tmp[i]);
        }
    }

    //On parse chaque ligne pour en extraire les points
    QList<QVector3D> resultat;
    for (unsigned int i=0 ; i<contenu.size() ; i++)
    {
        DEBUG_MSG("Ligne" << i << QString(contenu[i].c_str()));
        if (contenu[i].find("#") != std::string::npos)
        {
            resultat.append(parser_plan(contenu[i+1], (unsigned)((char)contenu[i][1]-'0')-num_p0));
        }
    }

    for (int i=0 ; i<resultat.size() ; i++)
    {
        DEBUG_MSG(resultat[i].x() << resultat[i].y() << resultat[i].z());
    }

    return Motif(QString(nom), resultat);
}

QList<QVector3D> CarteSD::parser_plan(std::string const& plan, unsigned num_plan)
{
    /* Une ligne de plan (vertical) correspond à 81 (9*9) 1 ou 0 qui désignent les LEDs du bas vers le haut, du fond vers l'avant.
     * Chaque bloc de 9 correpsond à une ligne du fond vers l'avant (axe x).
     * Les blocs montent du bas vers le haut (axe z).
     * Exemple : si on on est sur le plan 0 (le plus à gauche), le premier chiffre correspond à la LED (0,0,0).
     *           La dixième LED correspond au point (0,0,1). Elle juste au dessus de la précédente.
     *           La dernière sera au point (8,0,8).
     */

    QList<QVector3D> res;
    DEBUG_MSG(num_plan << QString(plan.c_str()));

    for (unsigned i=0 ; i<plan.size() ; i++)
    {
        if (plan[i] == '1')
        {
            QVector3D v(i%9, num_plan, i/9);
            res.append(v);
        }
    }

    return res;
}

QStringList CarteSD::lire_fichier(QString const& chemin)
{
    QStringList res;

    QFile fichier(chemin);

    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        ERROR_QUIT("Impossible d'ouvrir le fichier" << chemin);

    QTextStream in(&fichier);
    while (!in.atEnd())
    {
        QString ligne = in.readLine();
        res.append(ligne);
    }

    return res;
}

void CarteSD::inverser_chaines(std::string & s1, std::string & s2)
{
    std::string tmp = s1;
    s1 = s2;
    s2 = tmp;
}

void CarteSD::retourner_chaine(std::string & s)
{
    std::string tmp = std::string(s.rbegin(), s.rend());
    s = tmp;
}
