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
    /*
    QString folderName = ui -> textEdit_2 -> toPlainText();
    QDir dir(folderName);

    if (!dir.exists()) {
        dir.mkpath(".");
        qDebug() << "Created directory successed!";
    }
    */

    QString fileName= ui -> textEdit -> toPlainText();
    QFile file;
    file.setFileName(fileName +".txt");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    //QTextStream stream(&file);
    SaveTemporary::setFileName(fileName);
    file.close();
    getFileName();
}

void SaveTemporary::setFileName(QString t){
    Name = t;
}

QString SaveTemporary::getFileName(){
    qDebug() << Name;
    return Name;
}
