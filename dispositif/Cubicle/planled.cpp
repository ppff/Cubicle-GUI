#include "planled.h"
#include "ui_planled.h"

Planled::Planled(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Planled)
{
    ui->setupUi(this);
}

Planled::~Planled()
{
    delete ui;
}
