#include "duppliquerplan.h"

DuppliquerPlan::DuppliquerPlan()
{
}
void DuppliquerPlan::SelectPlan(Ui::MainWindow *ui,Cube c, int n,QList<QVector3D> l, QPushButton* buttons[90]){
    QList<int> listePlanADupliquer;
    listePlanADupliquer.clear();

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

QList<QVector3D> DuppliquerPlan:: parcoursCube(int NumeroPlan, QList<QVector3D> liste_vecteur3D,Cube cubeMotif,int nplan){

    for(int i=0;i<9;i++){
        for (int j=0;j<9;j++){
             Led led=cubeMotif.getList1()->value(NumeroPlan).getLed(i,j);
             if(led.getEtat()==1){
                 QVector3D v;
                 v=QVector3D(abs(8-j),nplan,abs(8-i));
                 liste_vecteur3D.append(v);
                 int size=liste_vecteur3D.size();
                 QString s=QString::number(size);
                 qDebug()<<"taille de liste vecteur3D "+s;
                 cubeMotif.getList1()->value(nplan).getLed(i,j).modifierEtat();
             }
        }
    }
    return liste_vecteur3D;
}


Cube DuppliquerPlan::updateCube(Cube nouveauCube,int NumeroPlan,int nplan){

    for(int i=0;i<9;i++){
        for (int j=0;j<9;j++){
             Led led=nouveauCube.getList1()->value(NumeroPlan).getLed(i,j);
             if(led.getEtat()==1){
                 Led led1=nouveauCube.getList1()->value(nplan).getLed(i,j);
                 led1.modifierEtat();
                 Plan p1=nouveauCube.getList1()->value(nplan);
                 p1.updatePlan(led1,i,j,nplan);
                 nouveauCube.updateCube(p1,nplan);
             }
        }
    }
    return nouveauCube;
}

void DuppliquerPlan::dupliquer(Ui::MainWindow *ui,
                  Cube cubeMotif,int NumeroPlan, QList<int> l,QList<QVector3D> liste_vecteur3D,QString emplMotif){

    QList<QVector3D> Nouvelleliste;
    Cube nouveauCube=cubeMotif;
    Nouvelleliste=liste_vecteur3D;
    for(int i=0; i<l.size();i++){
        int nplan=l.value(i);
        QString nn=QString::number(nplan);
        qDebug()<<"nplan "+nn;
        Nouvelleliste=parcoursCube(NumeroPlan,Nouvelleliste,cubeMotif,nplan);
        nouveauCube=updateCube(nouveauCube,NumeroPlan,nplan);

        ui->widget->setListPoints(Nouvelleliste);
    }
    GestionFichier gestion;
    gestion.ouvrir(emplMotif,nouveauCube);

    //décolorer les boutons plans sélectionnés pour la duplication
    for(int j=0;j<l.size();j++){
        int n=l.value(j);
        decolorePlan(ui,n);
    }

    DeconnecterPlan(ui);
}
