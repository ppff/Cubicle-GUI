#include "creationfichier.h"
#include "ui_creationfichier.h"
#include "savetemporary.h"

CreationFichier::CreationFichier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreationFichier)
{
    ui->setupUi(this);
}

CreationFichier::~CreationFichier()
{
    delete ui;
}

void CreationFichier::on_pushButton_clicked()
{
    SaveTemporary savetempo;
    savetempo.setModal(true);
    savetempo.exec();
}
