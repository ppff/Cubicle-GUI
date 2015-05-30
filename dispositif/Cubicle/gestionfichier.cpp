#include "gestionfichier.h"
using namespace std;

GestionFichier::GestionFichier()
{
}

void GestionFichier::ouvrir(QString empl,Cube c){

    QFile file(empl);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        qDebug()<<"le fichier n'est pas ouvert";
       return;
    }

    QTextStream flux(&file);
    QString x,y,z;
    QString version=flux.readLine(); // on lit la ligne de la version
    file.resize(0);
    flux<<version<<endl;
   for(int cntP=0;cntP<9;cntP++){
       y=QString::number(cntP);
       for(int cntL=0;cntL<9;cntL++){
           z=QString::number(cntL);
           for(int cntA=0;cntA<9;cntA++){
               Led l=c.getList1()->value(cntP).getLed(cntL,cntA);
               int e=l.getEtat() ;
               if (e) {

                   x=QString::number(cntA);
                   qDebug()<<"led ("+x+y+z+") allumé ";
                   flux<<x+y+z<<endl;
           }

       }
   }



}
   file.close();
}

QString GestionFichier::getLinePlan(int nplan,int nligne,Cube c){
    QString str="";
    QString x,y,z;
    y=QString::number(nplan);
    z=QString::number(nligne);
    for(int i=0;i<9;i++){
       Led l=c.getList1()->value(nplan).getLed(nligne,i);
       int e=l.getEtat() ;
       if (e=1) {
           x=QString::number(i);
           str+=x+y+z+'\n';
       }
    }
    return str;
}



