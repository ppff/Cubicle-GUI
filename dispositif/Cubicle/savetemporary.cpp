#include "savetemporary.h"
#include "ui_savetemporary.h"

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
