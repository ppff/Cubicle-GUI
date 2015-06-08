#include "duppliquerplan.h"

DuppliquerPlan::DuppliquerPlan()
{
}
//déconnecter tous les plans du signal affichePlanLed
void DuppliquerPlan:: DeconnecterPlan(Ui::MainWindow *ui){
    ui->plane1->disconnect(SIGNAL(clicked()));
    ui->plane2->disconnect(SIGNAL(clicked()));
    ui->plane3->disconnect(SIGNAL(clicked()));
    ui->plane4->disconnect(SIGNAL(clicked()));
    ui->plane5->disconnect(SIGNAL(clicked()));
    ui->plane6->disconnect(SIGNAL(clicked()));
    ui->plane7->disconnect(SIGNAL(clicked()));
    ui->plane8->disconnect(SIGNAL(clicked()));
    ui->plane9->disconnect(SIGNAL(clicked()));
}
/*
void DuppliquerPlan::clignotementPlan(Ui::MainWindow *ui,int NumeroPlan){

    ui->plane1->setCheckable(true);
}

bool DuppliquerPlan::clignotement(Ui::MainWindow *ui,bool enfonce){

    if(enfonce)
       {
           ui->plane1->setChecked(false);
           enfonce = false;
       }
       else
       {
           ui->plane1->setChecked(true);
           enfonce = true;
       }

    return enfonce;
}
*/
//colorer les plans choisis à dupliquer en jaune
void DuppliquerPlan::colorePlan(Ui::MainWindow *ui,int nplan){

    switch(nplan){
    case 0:ui->plane1->setStyleSheet("QPushButton { background-color: yellow; }"); break;
    case 1:ui->plane2->setStyleSheet("QPushButton { background-color: yellow; }"); break;
    case 2:ui->plane3->setStyleSheet("QPushButton { background-color: yellow; }"); break;
    case 3:ui->plane4->setStyleSheet("QPushButton { background-color: yellow; }"); break;
    case 4:ui->plane5->setStyleSheet("QPushButton { background-color: yellow; }"); break;
    case 5:ui->plane6->setStyleSheet("QPushButton { background-color: yellow; }"); break;
    case 6:ui->plane7->setStyleSheet("QPushButton { background-color: yellow; }"); break;
    case 7:ui->plane8->setStyleSheet("QPushButton { background-color: yellow; }"); break;
    case 8:ui->plane9->setStyleSheet("QPushButton { background-color: yellow; }"); break;
    }
}

void DuppliquerPlan:: decolorePlan(Ui::MainWindow *ui,int nplan){
    switch(nplan){
    case 0:ui->plane1->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }"); break;
    case 1:ui->plane2->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }"); break;
    case 2:ui->plane3->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }"); break;
    case 3:ui->plane4->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }"); break;
    case 4:ui->plane5->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }"); break;
    case 5:ui->plane6->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }"); break;
    case 6:ui->plane7->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }"); break;
    case 7:ui->plane8->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }"); break;
    case 8:ui->plane9->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }"); break;
    }

}

//mise à jour de la liste de vecteurs 3D après chaque duplication
QList<QVector3D> DuppliquerPlan:: parcoursCube(int NumeroPlanADupliquer, QList<QVector3D> liste_vecteur3D,Cube cubeMotif,int nplan){

    for(int i=0;i<9;i++){
        for (int j=0;j<9;j++){
             Led led=cubeMotif.getList1()->value(NumeroPlanADupliquer).getLed(i,j);
             if(led.getEtat()==1){
                 QVector3D v;
                 v=QVector3D(abs(8-j),nplan,abs(8-i));
                 if(!liste_vecteur3D.contains(v)){
                     liste_vecteur3D.append(v);
                     int size=liste_vecteur3D.size();
                     QString s=QString::number(size);
                     qDebug()<<"taille de liste vecteur3D "+s;
                     cubeMotif.getList1()->value(nplan).getLed(i,j).modifierEtat();
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
             if(led.getEtat()==1){
                 Led led1=nouveauCube.getList1()->value(nplan).getLed(i,j);
                 if(led1.getEtat()==0){
                     led1.modifierEtat();
                     Plan p1=nouveauCube.getList1()->value(nplan);
                     p1.updatePlan(led1,i,j);
                     nouveauCube.updateCube(p1,nplan);
                 }

             }
        }
    }
    return nouveauCube;
}

QList<QVector3D> DuppliquerPlan::dupliquer(Ui::MainWindow *ui,
                  Cube cubeMotif,int NumeroPlanADupliquer, QList<int> l,QList<QVector3D> liste_vecteur3D,QString emplMotif){

    QList<QVector3D> Nouvelleliste;
    Cube nouveauCube=cubeMotif;
    Nouvelleliste=liste_vecteur3D;
    for(int i=0; i<l.size();i++){
        int nplan=l.value(i);
        Nouvelleliste=parcoursCube(NumeroPlanADupliquer,Nouvelleliste,cubeMotif,nplan);
        nouveauCube=updateCube(nouveauCube,NumeroPlanADupliquer,nplan);

    }
    GestionFichier gestion;
    gestion.ouvrir(emplMotif,nouveauCube);

    //décolorer les boutons plans sélectionnés pour la duplication
    for(int j=0;j<l.size();j++){
        int n=l.value(j);
        decolorePlan(ui,n);
    }

    DeconnecterPlan(ui);
    return Nouvelleliste;
}
