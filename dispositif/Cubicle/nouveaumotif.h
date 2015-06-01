#ifndef NOUVEAUMOTIF_H
#define NOUVEAUMOTIF_H
#include "QFile"

class NouveauMotif
{

public:
    NouveauMotif(QString nomMotif, QString Dir);
    QString getNameFile();
private:
    QString nameFile;

};

#endif // NOUVEAUMOTIF_H
