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
    void monter(Ui::MainWindow *ui,QDirModel *model);
    void descendre(Ui::MainWindow *ui,QDirModel *model);

};

#endif // CONTROLARBORESCENCE_H
