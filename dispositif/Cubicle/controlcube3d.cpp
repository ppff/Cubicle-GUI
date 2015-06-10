#include "controlcube3d.h"

ControlCube3D::ControlCube3D()
{

}
void ControlCube3D::desactivePlan(QPushButtonPers * plans[9],Ui::MainWindow *ui){

    for(int i=0;i<9;i++){
         plans[i]->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
    }

 ui->plane1->hide();
 ui->plane2->hide();
 ui->plane3->hide();
 ui->plane4->hide();
 ui->plane5->hide();
 ui->plane6->hide();
 ui->plane7->hide();
 ui->plane8->hide();
 ui->plane9->hide();

}

int ControlCube3D::affichePlanLed(const QString & valeur,Ui::MainWindow *ui,QPushButtonPers * plans[9],QPushButton* buttons[90],Cube cubeMotif){

    desactivePlan(plans,ui);

    QString stnplan=valeur[1];
    int nplan=stnplan.toInt(0,10);

    //colorer en rouge le plan sélectionné
    plans[8-nplan]->setStyleSheet("QPushButton { background-color: red; }");

    QList<QVector3D> ll;
    for(int i=0;i<9;i++)
        for(int k=0;k<9;k++)
        {QVector3D v;
            v= QVector3D(i,nplan,k);
            ll.append(v);
            ui->widget->setListPlan(ll);
        }

   //allumer les leds sur le plan 2D
   for (int i = 0; i < 9; i++) {
        for (int j=0;j<9; j++){
           QString col=QString::number(i);
           QString lig=QString::number(j);
           QString text=lig+col;

           int num=text.toInt(0,10);
           buttons[num]->setVisible(true);

           Led l;
           l=cubeMotif.getList1()->value(nplan).getLed(j,i);

           if(l.getEtat()==0){
               buttons[num]->setIcon(QIcon(":/icone/nvatomeblanc.png"));
           }
           else {
               buttons[num]->setIcon(QIcon(":/icone/atome.gif"));
           }
       }
    }
   return nplan;
}
