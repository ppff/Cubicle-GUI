#include "controlarborescence.h"

ControlArborescence::ControlArborescence()
{

}

void ControlArborescence:: ctlSave(Cube cubeMotif, QString emplMotif){
    GestionFichier ges;
    if(emplMotif!=""){
         qDebug()<<"je suis dans save";
         ges.ouvrir(emplMotif,cubeMotif);
    }
}


