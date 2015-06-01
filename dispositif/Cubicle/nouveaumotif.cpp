#include "nouveaumotif.h"
#include "QFile"
#include "QTextStream"
#include "QDebug"
#include "QDir"


//cette classe crée un nouveau fichier avec le nom du groupe, du nouveau motif et des 0 dans toutes les leds
NouveauMotif::NouveauMotif(QString nomMotif, QString Dir)
{
    QDir dir(Dir);
    QStringList nameFilter;
    nameFilter<<"*.txt";
    QFileInfoList list=dir.entryInfoList(nameFilter,QDir::Files);
    int num=list.size();
    QString snum;
    snum=QString::number(num) ; // commence le comptage par 0


    if(num<10){
        nameFile=Dir+"/0"+snum+"_"+nomMotif+".txt";
    }
    else if(num<100){
        nameFile=Dir+"/"+snum+"_"+nomMotif+".txt";
          }

     QFile motif(nameFile);

    if (!motif.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"le fichier ne s'ouvre pas";
        return;
    }
 QTextStream flux(&motif);
 flux.setCodec("UTF-8");
 flux<<"1"<<endl ;// on ecrit la version du fichier

     flux<<endl;

 motif.close();


}

QString NouveauMotif::getNameFile(){
 return this->nameFile;
}
