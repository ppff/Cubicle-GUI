#include "nouveaumotif.h"
#include "QFile"
#include "QTextStream"
#include "QDebug"
#include "QDir"


//cette classe crée un nouveau fichier avec le nomdu groupe, du nouveau motif et des 0 dans tous les leds
NouveauMotif::NouveauMotif(QString nomMotif, QString Dir)
{

    QDir dir(Dir);
    QStringList nameFilter;
    nameFilter<<"*.txt";
    QFileInfoList list=dir.entryInfoList(nameFilter,QDir::Files);
    int num=list.size();
    QString snum;
    snum=QString::number(num) ; // commence le comptage par 0
   // if (num<10) {
    QFile motif(Dir+"/0"+snum+"_"+nomMotif+".txt");
   // else if (num<100){
   // QFile motif(Dir+"/"+snum+"_"+nomMotif+".txt");
    //}
   /*else{
        qDebug()<<"nombre maximum de motif atteint";
    }*/
    if (!motif.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"le fichier ne s'ouvre pas";
        return;
    }
 QTextStream flux(&motif);
 flux.setCodec("UTF-8");
 flux<<"version 0.0"<<endl ;

     flux<<endl;

 motif.close();


}

