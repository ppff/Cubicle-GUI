#ifndef CONTROLARBORESCENCE_H
#define CONTROLARBORESCENCE_H

#include "cube.h"
#include <QString>
#include "gestionfichier.h"
#include "global.h"
#include <QObject>
#include <QFileSystemModel>

class ControlArborescence
{
public:
    ControlArborescence();
    void ctlSave(Cube cubeMotif, QString emplMotif);
    void monter(Ui::MainWindow *ui,QFileSystemModel *model);
    void descendre(Ui::MainWindow *ui,QFileSystemModel *model);

};

#endif // CONTROLARBORESCENCE_H
