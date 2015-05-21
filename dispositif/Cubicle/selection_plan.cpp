#include "selection_plan.h"
#include "ui_selection_plan.h"

Selection_Plan::Selection_Plan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Selection_Plan)
{
    ui->setupUi(this);
}

Selection_Plan::~Selection_Plan()
{
    delete ui;
}
