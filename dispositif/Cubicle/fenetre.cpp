#include "fenetre.h"
#include "ui_fenetre.h"
#include <QFileDialog>
#include<QMessageBox>
Fenetre::Fenetre(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Fenetre)
{
    ui->setupUi(this);
    QWidget::connect(ui->actionSave_as,SIGNAL(triggered(bool)),this,SLOT(ouvrir_explorer()));

}

Fenetre::~Fenetre()
{
    delete ui;
}

void Fenetre::ouvrir_explorer(){
    QString filename=QFileDialog::getSaveFileName(
                this,
                tr("save file"),
                "C://",
                "All files (*.*)"
                );
    //QMessageBox::information(this,tr("File Name"),filename);

}
