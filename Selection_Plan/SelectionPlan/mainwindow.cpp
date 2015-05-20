#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::information(this,"Title",ui->comboBox->currentText()+" : "+ui->comboBox_2->currentText());
}

int MainWindow::getOrientationPlan()
{
   return firstValeur;
}

int MainWindow::getNumeroPlan()
{
   return secondValeur;
}

void MainWindow::setOrientationPlan(QString t)
{

   QString string = t;
   firstValeur = string.toInt();
}

void MainWindow::setNumeroPlan(QString t)
{

   QString string_2 = t;
   secondValeur = string_2.toInt();
}

void MainWindow::on_pushButton_released()
{
    setOrientationPlan(ui->comboBox->currentText());
    setNumeroPlan(ui->comboBox_2->currentText());
    close();
}
/*
void MainWindow::returnValue()
{
    qDebug() << "Le numero du plan choisit est :" << getNumeroPlan();
    qDebug() << "L'orientation du plan choisit est :" << getOrientationPlan();
}
*/
