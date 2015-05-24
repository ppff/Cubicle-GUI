#include "save.h"
#include "ui_save.h"
#include <QFile>
#include <QDebug>

save::save(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::save)
{
    ui->setupUi(this);
    this->c=Cube();
    QObject::connect(ui->pushButton, SIGNAL(clicked()),
                          this, SLOT(controlSave()));


}

save::~save()
{
    delete ui;
}

void save::ouvrir(){

    QFile file(this->empl);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        qDebug()<<"le fichier n'est pas ouvert";
       return;
    }

 file.close();
}

void save::setName(QString nom){
    this->nom=nom;
}

QString save::getName(){
    return this->nom;
}

void save::setEmpl(QString e){
    this->empl=e;
}

QString save::getEmpl(){
    return this->empl;
}

void save::controlSave(){
    this->ouvrir();

}
