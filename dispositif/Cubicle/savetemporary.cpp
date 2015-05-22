#include "savetemporary.h"
#include "ui_savetemporary.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QtCore/QCoreApplication>

SaveTemporary::SaveTemporary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveTemporary)
{
    ui->setupUi(this);
}

SaveTemporary::~SaveTemporary()
{
    delete ui;
}

void SaveTemporary::on_buttonBox_accepted()
{
    creationFichier();
}

/*
void SaveTemporary::creationFolder(){
    QString folderName = ui -> textEdit_2 -> toPlainText();
    QDir dir(folderName);

    if (!dir.exists()) {
        dir.mkpath(".");
        qDebug() << "Created directory successed!";
    }
}
*/

void SaveTemporary::creationFichier(){
    QString fileName= ui -> textEdit -> toPlainText();
    QFile file;
    file.setFileName(fileName +".txt");
    setFileName(fileName);
    getFileName();

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)){
        qDebug()<< "Open successful";
    }else{
        qDebug()<< "Open not successful";
    }

    QString MyAppDirPath =  QCoreApplication::applicationDirPath();
    qDebug()<< MyAppDirPath;

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream
           <<""<<endl
           <<getFileName()<<endl;
   // prechargerTexte(getFileName());

    file.close();


}
/*
void SaveTemporary::prechargerTexte(){
    QString line;
    QFile f("/home/su/Documents/CUBICLE_GUI/Cubicle-GUI/dispositif/build-Cubicle-Desktop-Debug/precharger.txt");
    f.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&f);
    while (!in.atEnd()){
        line+=in.readLine()+'\n';
    }
    QFile f1("/home/su/Documents/CUBICLE_GUI/Cubicle-GUI/dispositif/build-Cubicle-Desktop-Debug/str.txt");
    f1.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream a(&f1);
    a<<line;
}
*/

/*
QString SaveTemporary::prechargerTexte(){
    QString** tableau;
    tableau = new QString*[10];
    for ()
    for (int i=1; i < 10; i++){
        QString str = QString::number(i);
        tableau[i][0]="#";
        tableau[i][1]= str;
        tableau[i][2]= "\n";
        for (int j=1;j<10; j++){
            tableau[i][j]="000000000";
            tableau[i][j+1]= "\n";
        }
    }
    return tableau[][];
}
*/

void SaveTemporary::setFileName(QString t){
    Name = t+"txt";
}

QString SaveTemporary::getFileName(){
    qDebug()<< Name;
    return Name;
}


