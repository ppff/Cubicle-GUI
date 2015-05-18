#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_haut,    SIGNAL(clicked()), this, SLOT(translater_haut()));
    connect(ui->btn_bas,     SIGNAL(clicked()), this, SLOT(translater_bas()));
    connect(ui->btn_gauche,  SIGNAL(clicked()), this, SLOT(translater_gauche()));
    connect(ui->btn_droite,  SIGNAL(clicked()), this, SLOT(translater_droite()));
    connect(ui->btn_avant,   SIGNAL(clicked()), this, SLOT(translater_devant()));
    connect(ui->btn_arriere, SIGNAL(clicked()), this, SLOT(translater_derriere()));

    connect(ui->btn_groupe_prec, SIGNAL(clicked()), this, SIGNAL(groupe_precedent()));
    connect(ui->btn_groupe_suiv, SIGNAL(clicked()), this, SIGNAL(groupe_suivant()));
    connect(ui->btn_motif_prec,  SIGNAL(clicked()), this, SIGNAL(motif_precedent()));
    connect(ui->btn_motif_suiv,  SIGNAL(clicked()), this, SIGNAL(motif_suivant()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::translater_haut()
{
    emit translation(Haut);
}

void MainWindow::translater_bas()
{
    emit translation(Bas);
}

void MainWindow::translater_gauche()
{
    emit translation(Gauche);
}

void MainWindow::translater_droite()
{
    emit translation(Droite);
}

void MainWindow::translater_devant()
{
    emit translation(Devant);
}

void MainWindow::translater_derriere()
{
    emit translation(Derriere);
}

void MainWindow::modifier_groupe(QString const& numero, QString const& nom)
{
    //Dans l'idéal il faudrait tronquer ici et pas dans les constructeurs Groupe/Motif mais bon.
    ui->numero_groupe->setText(numero);
    ui->nom_groupe->setText(nom);
}

void MainWindow::modifier_motif(QString const& numero, QString const& nom)
{
    ui->numero_motif->setText(numero);
    ui->nom_motif->setText(nom);
}
