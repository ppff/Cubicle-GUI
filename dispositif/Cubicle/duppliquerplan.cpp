#include "duppliquerplan.h"

DuppliquerPlan::DuppliquerPlan()
{
}

//mise à jour de la liste de vecteurs 3D après chaque duplication
QList<QVector3D> DuppliquerPlan:: parcoursCube(int NumeroPlanADupliquer, QList<QVector3D> liste_vecteur3D,Cube cubeMotif,int nplan){

    for(int i=0;i<9;i++){
        for (int j=0;j<9;j++){

            Led led=cubeMotif.getList1()->value(NumeroPlanADupliquer).getLed(i,j);
            QVector3D v;
            v=QVector3D(abs(8-j),nplan,abs(8-i));

            if(led.getEtat()==1){
                if(!liste_vecteur3D.contains(v)){
                    liste_vecteur3D.append(v);
                    int size=liste_vecteur3D.size();
                    QString s=QString::number(size);
                    qDebug()<<"taille de liste vecteur3D "+s;
                    cubeMotif.getList1()->value(nplan).getLed(i,j).modifierEtat();
                }
            }
            else {
                if (liste_vecteur3D.contains(v)) {
                    liste_vecteur3D.removeOne(v);
                }

            }
        }
    }
    return liste_vecteur3D;
}

//mise à jour de l'instance du cube après chaque duplication
Cube DuppliquerPlan::updateCube(Cube nouveauCube,int NumeroPlanADupliquer,int nplan){

    for(int i=0;i<9;i++){
        for (int j=0;j<9;j++){
            Led led=nouveauCube.getList1()->value(NumeroPlanADupliquer).getLed(i,j);

            Led led1=nouveauCube.getList1()->value(nplan).getLed(i,j);
            if(led.getEtat()!=led1.getEtat()){

                led1.modifierEtat();
                Plan p1=nouveauCube.getList1()->value(nplan);
                p1.updatePlan(led1,i,j);
                nouveauCube.updateCube(p1,nplan);
            }
        }
    }
    return nouveauCube;
}


//coller un plan à partir d'un clic droit
QList<QVector3D> DuppliquerPlan::collerPlan(Cube cubeMotif,
                                            int NumeroPlanADupliquer, int NumeroPlanPaste, QList<QVector3D> liste_vecteur3D,QString emplMotif){

    QList<QVector3D> Nouvelleliste;
    Cube nouveauCube=cubeMotif;
    Nouvelleliste=liste_vecteur3D;

    Nouvelleliste=parcoursCube(NumeroPlanADupliquer,Nouvelleliste,cubeMotif,NumeroPlanPaste);
    nouveauCube=updateCube(nouveauCube,NumeroPlanADupliquer,NumeroPlanPaste);

    //mise à jour du fichier
    GestionFichier gestion;
    gestion.ouvrir(emplMotif,nouveauCube);

    return Nouvelleliste;
}
