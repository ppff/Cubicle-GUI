#include "controlplan2d.h"

ControlPlan2D::ControlPlan2D()
{

}

//permet d'allumer une led sur le plan 2D selon la valeur passée en paramètre
void ControlPlan2D:: afficheLed(  QPushButton* buttons[90],const int i, const int j,const  int etat )
{
       QString lig=QString::number(i);
       QString col=QString::number(j);
       QString text=lig+col;
       int num=text.toInt(0,10);
       if(etat==0){
           buttons[num]->setIcon(QIcon(":/icone/nvatomeblanc.png"));
       }
       else {
           buttons[num]->setIcon(QIcon(":/icone/atome.gif"));
       }
}


QList<QVector3D> ControlPlan2D::controlLed(const QString & valeur,Cube cubeMotif,int NumeroPlan,QList<QVector3D>  liste_vecteur3D,Ui::MainWindow *ui,QPushButton* buttons[90]){
        QString strlig=valeur[0];
        QString strcol=valeur[1];
        int lig=strlig.toInt(0,10);
        int col=strcol.toInt(0,10);
        Led l;
        l=cubeMotif.getList1()->value(NumeroPlan).getLed(lig,col);
        l.modifierEtat();
        Plan p1=cubeMotif.getList1()->value(NumeroPlan);
        p1.updatePlan(l,lig,col);
        cubeMotif.updateCube(p1,NumeroPlan);
        QVector3D v;
        v=QVector3D(abs(8-col),NumeroPlan,abs(8-lig));
        liste_vecteur3D.append(v);
        QString s ;
        s=QString::number(liste_vecteur3D.size());
        qDebug()<<"la taille de la liste est "+s;
        ui->widget->setListPoints(liste_vecteur3D);
        if(cubeMotif.getList1()->value(NumeroPlan).getLed(lig,col).getEtat()==1){
            liste_vecteur3D.append(v);
           ui->widget->setListPoints(liste_vecteur3D);
        }
        else {
            liste_vecteur3D.removeAll(v);
            ui->widget->setListPoints(liste_vecteur3D);
        }
        afficheLed(buttons,lig,col,l.getEtat());
        return liste_vecteur3D;
}

//désactiver la sélection des plans 2D
void ControlPlan2D::desactiveSelectPlan(QPushButtonPers* plans[9],bool b){

    for(int i=0;i<9;i++){
        plans[i]->setDisabled(b);
    }
}

