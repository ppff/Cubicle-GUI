#include "selection_plan.h"
#include "ui_selection_plan.h"
#include <QMessageBox>
#include <QDebug>

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

void Selection_Plan::on_pushButton_clicked()
{
    QMessageBox::information(this,"Title",ui->comboBox->currentText()+" : "+ui->comboBox_2->currentText());
}

int Selection_Plan::getOrientationPlan()
{
   return firstValeur;
}

int Selection_Plan::getNumeroPlan()
{
   return secondValeur;
}

void Selection_Plan::setOrientationPlan(QString t)
{

   QString string = t;
   firstValeur = string.toInt();
}

void Selection_Plan::setNumeroPlan(QString t)
{

   QString string_2 = t;
   secondValeur = string_2.toInt();
}

void Selection_Plan::on_pushButton_released()
{
    setOrientationPlan(ui->comboBox->currentText());
    setNumeroPlan(ui->comboBox_2->currentText());
    close();
}
