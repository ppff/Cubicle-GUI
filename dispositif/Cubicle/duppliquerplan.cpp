#include "duppliquerplan.h"

DuppliquerPlan::DuppliquerPlan()
{
}

//déconnecter tous les plans du signal affichePlanLed
void DuppliquerPlan:: DeconnecterPlan(QPushButtonPers* plans[9]){

    for(int i=0;i<9;i++){
        plans[i]->disconnect(SIGNAL(clicked()));
     }

}

//colorer le plan à dupliquer en jaune
void DuppliquerPlan::colorePlan(QPushButtonPers* plans[9],int nplan){

    plans[8-nplan]->setStyleSheet("QPushButton { background-color: yellow; }");

}

//décolorer le plan déjà dupliqué
void DuppliquerPlan:: decolorePlan(QPushButtonPers* plans[9],int nplan){

    plans[8-nplan]->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");

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



QList<QVector3D> DuppliquerPlan::dupliquer(QPushButtonPers* plans[9],
                  Cube cubeMotif,int NumeroPlanADupliquer, QList<int> l,QList<QVector3D> liste_vecteur3D,QString emplMotif){

    QList<QVector3D> Nouvelleliste;
    Cube nouveauCube=cubeMotif;
    Nouvelleliste=liste_vecteur3D;

    for(int i=0; i<l.size();i++){
        int nplan=l.value(i);
        Nouvelleliste=parcoursCube(NumeroPlanADupliquer,Nouvelleliste,cubeMotif,nplan);
        nouveauCube=updateCube(nouveauCube,NumeroPlanADupliquer,nplan);

    }

    //mise à jour du fichier.txt
    GestionFichier gestion;
    gestion.ouvrir(emplMotif,nouveauCube);

    //décolorer les boutons plans sélectionnés pour la duplication
    for(int j=0;j<l.size();j++){
        int n=l.value(j);
        decolorePlan(plans,n);
    }

    DeconnecterPlan(plans);
    return Nouvelleliste;
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

int DuppliquerPlan::recupereNomPlan(QPushButtonPers* plans[9]){
    int i=0;
    int numeroPlanADuppliquer;
    while(plans[i]->getNamePlane().compare("")==0){
        i++;
    }
    QString nomPlan=(QString)plans[i]->getNamePlane();
    if(nomPlan.compare("plane9")==0){
        qDebug()<<"plan 9";
        numeroPlanADuppliquer=8;

    }
    if(nomPlan.compare("plane8")==0){
        qDebug()<<"plan 8";
        numeroPlanADuppliquer=7;

    }
    if(nomPlan.compare("plane7")==0){
        qDebug()<<"plan 7";
        numeroPlanADuppliquer=6;

    }
    if(nomPlan.compare("plane6")==0){
        qDebug()<<"plan 6";
        numeroPlanADuppliquer=5;

    }
    if(nomPlan.compare("plane5")==0){
        qDebug()<<"plan 5";
        numeroPlanADuppliquer=4;

    }
    if(nomPlan.compare("plane4")==0){
        qDebug()<<"plan 4";
        numeroPlanADuppliquer=3;

    }
    if(nomPlan.compare("plane3")==0){
        qDebug()<<"plan 3";
        numeroPlanADuppliquer=2;

    }
    if(nomPlan.compare("plane2")==0){
        qDebug()<<"plan 2";
        numeroPlanADuppliquer=1;

    }
    if(nomPlan.compare("plane1")==0){
        qDebug()<<"plan 1";
        numeroPlanADuppliquer=0;

    }
    return numeroPlanADuppliquer;
}
