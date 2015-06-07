#ifndef CONTROLARBORESCENCE_H
#define CONTROLARBORESCENCE_H

#include "cube.h"
#include <QString>
#include "gestionfichier.h"
#include "global.h"
#include <QObject>

class ControlArborescence
{
public:
    ControlArborescence();
    void ctlSave(Cube cubeMotif, QString emplMotif);

};

#endif // CONTROLARBORESCENCE_H
