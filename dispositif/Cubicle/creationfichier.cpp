#include "creationfichier.h"
#include "ui_creationfichier.h"

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
