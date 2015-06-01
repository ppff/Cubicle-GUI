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
           z=QString::number(abs(8-cntL));
           for(int cntA=0;cntA<9;cntA++){
               Led l=c.getList1()->value(cntP).getLed(cntL,cntA);
               int e=l.getEtat() ;
               if (e) {

                   x=QString::number(abs(8-cntA));
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

//parser le fichier du moutif et renvoyer une liste de vecteurs 3D de leds allumées

QList<QVector3D> GestionFichier:: parser(QString empl, QList<QVector3D> list){
    QFile file(empl);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"le fichier n'est pas ouvert";

    }
    qDebug()<<"fichier ouvert";
    QTextStream flux(&file);
    QString  Line;
    list.clear();
    //lire la première ligne: version
    Line= flux.readLine()+'\n';

    while(!flux.atEnd()){
        Line=flux.readLine()+'\n';
        if(Line.size()>1){
                QString sx=(QString)Line[0];
                QString sy=(QString)Line[1];
                QString sz=(QString)Line[2];
                int x=sx.toInt(0,10);
                int y=sy.toInt(0,10);
                int z=sz.toInt(0,10);

            QVector3D v=QVector3D(x,y,z);
            list.append(v);
        }
    }

    file.close();
   return list;

}




 QList<QVector3D> GestionFichier::tabToVector3D(int* tab){
     QList<QVector3D> listVect;
    int i=0;
    QVector3D v;
    int x,y,z;
     while(tab[i]!=NULL){
        x=tab[i];
        y=tab[i+1];
        z=tab[i+2];
        v=QVector3D(x,y,z);
        listVect.append(v);
        i=i+3;
    }
     return listVect;
 }
