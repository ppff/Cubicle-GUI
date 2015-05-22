#include "sauvegarde.h"
#include "ui_sauvegarde.h"

sauvegarde::sauvegarde(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sauvegarde)
{
    ui->setupUi(this);
}

sauvegarde::~sauvegarde()
{
    delete ui;
}
