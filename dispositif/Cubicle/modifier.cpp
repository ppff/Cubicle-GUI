#include "modifier.h"
#include <QTextStream>
#include <QFile>
modifier::modifier()
{

}

void modifier::remplaceligne(QString remp,QString s,int a){
    QString line;
    QString line2;
    QString lineremp=remp;
    QFile f(s);
    f.open(QIODevice::ReadWrite| QIODevice::Text);
    QTextStream in(&f);
    int i=1;
    int j=a;
    while(!in.atEnd()){
                line2= in.readLine()+'\n';
                if(i==j){
                   line+=lineremp+'\n';
                }else{line +=line2;}
                i=i+1;

            }
    QFile fr(s);
    fr.open(QFile::ReadWrite | QFile::Truncate);
    QTextStream e(&fr);
    e << line;
}
