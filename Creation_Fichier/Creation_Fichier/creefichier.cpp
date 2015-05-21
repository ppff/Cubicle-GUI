#include "creefichier.h"
#include "ui_creefichier.h"

CreeFichier::CreeFichier(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreeFichier)
{
    ui->setupUi(this);
}

CreeFichier::~CreeFichier()
{
    delete ui;
}
