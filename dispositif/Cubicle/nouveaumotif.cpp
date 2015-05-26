#include "nouveaumotif.h"
#include "QFile"
#include "QTextStream"
#include "QDebug"


//cette classe crée un nouveau fichier avec le nomdu groupe, du nouveau motif et des 0 dans tous les leds
NouveauMotif::NouveauMotif(QString nomMotif, QString Dir)
{
 QFile motif(Dir+"/"+nomMotif+".txt");
    if (!motif.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"le fichier ne s'ouvre pas";
        return;
    }
 QTextStream flux(&motif);
 flux.setCodec("UTF-8");
 flux<<"@"+nomMotif<<endl ;
 for(int i=1; i<10;i++){
     QString c=QString::number(i);
     flux<<"#"+c<<endl;
     for(int j=1; j<10;j++){
         flux<<"000000000"<<endl ;
     }
     flux<<endl;
 }
 motif.close() ;


}

