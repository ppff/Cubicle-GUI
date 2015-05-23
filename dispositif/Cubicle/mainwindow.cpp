#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTreeWidgetItem"
#include"QInputDialog"
#include "nouveaumotif.h"
#include "QMenu"
#include "QPoint"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen_directory,SIGNAL(triggered(bool)),this,SLOT(ouvrir_explorer()));
    insert_Group = new QAction("insert Group",this);
    connect(ui->actionNew_Group,SIGNAL(triggered(bool)),this,SLOT(insertGroup()));
    connect(ui->actionNew_Pattern,SIGNAL(triggered(bool)),this,SLOT(ajouter_motif()));
}

//ouvre le répertoire de travail
void MainWindow::ouvrir_explorer(){
    namedir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                   "/home",
                                                   QFileDialog::ShowDirsOnly
                                                   | QFileDialog::DontResolveSymlinks
                                                    );
  tree();
  contextMenu = new QMenu(ui->treeView);
  ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
  insertMotif = new QAction("Inserer Motif",contextMenu);
  ui->treeView->addAction(insertMotif);
  connect(insertMotif,SIGNAL(triggered(bool)),this, SLOT(ajouter_motif()));
}

//affiche l'arbre de dossiers
void MainWindow::tree(){
            model = new QDirModel(this);
            model->setReadOnly(false);
            model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
    ui->treeView->setModel(model);
    QModelIndex index=model->index(namedir);
     ui->treeView->setRootIndex(index);
    ui->treeView->expand(index);
    ui->treeView->scrollTo(index);
    ui->treeView->setCurrentIndex(index);
    ui->treeView->resizeColumnToContents(0);
}

//creer un nouveau motif
void MainWindow::ajouter_motif(){
    QModelIndex index=ui->treeView->currentIndex();
    if (index.isValid()){
        if (model->fileInfo(index).isDir()) {
            QString dir=model->fileInfo(index).absolutePath();
            QString nameGroup=model->fileInfo(index).baseName();
            qDebug()<<"la direction du dossier est "+dir;
            qDebug()<<"le nom du dossier est "+nameGroup;
            QString nameMotif=QInputDialog::getText(this,"Name","Enter the pattern name");
            NouveauMotif m=NouveauMotif(nameGroup,nameMotif,dir+"/"+nameGroup);
            tree();



        }
    }

}

//creer un nouveau groupe de motif
void MainWindow::insertGroup(){
    QModelIndex index =ui->treeView->currentIndex();
    if (!index.isValid()) return;
    QString name =QInputDialog::getText(this,"Name","Enter a name");
    if(name.isEmpty())return;
    model->mkdir(index, name);

}

MainWindow::~MainWindow()
{
    delete ui;
}


