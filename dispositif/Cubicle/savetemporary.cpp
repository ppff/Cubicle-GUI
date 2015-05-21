#include "savetemporary.h"
#include "ui_savetemporary.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QIODevice>
#include <QTextStream>

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
    QString texte_2 = ui -> textEdit_2 -> toPlainText();
    QDir dir(texte_2);
    if (!dir.exists()) {
        dir.mkpath(".");
        qDebug() << "Created directory successed!";
    }
    QString texte= ui -> textEdit -> toPlainText();
    /*
    QFile fileCreate(texte);
    if (fileCreate.open(QIODevice::ReadWrite)){
        QTextStream myStream(&fileCreate);
        myStream<<texte;
        qDebug() << "Created texte successed!";
    }
*/
    QFile file;
    file.setFileName(texte +".txt");//file_name is the QString, which I get as aparameter
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(&file);
    QTextStream(stdout) << texte; //To see the name of the file, which has just been typed
    file.close();
}
