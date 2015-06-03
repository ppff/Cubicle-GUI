#ifndef NOUVEAUMOTIF_H
#define NOUVEAUMOTIF_H
#include "QFile"
#include "QTextStream"
#include "QDebug"
#include "QDir"

class NouveauMotif
{

public:
    NouveauMotif(QString nomMotif, QString Dir);
    QString getNameFile();
private:
    QString nameFile;

};

#endif // NOUVEAUMOTIF_H
