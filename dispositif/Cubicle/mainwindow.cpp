#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTreeWidgetItem"
#include"QInputDialog"
#include "nouveaumotif.h"
#include "QMenu"
#include "QPoint"
#include "QMessageBox"
#include "QDirIterator"
#include "QDebug"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionCopy->setDisabled(true);
    ui->actionDelete_pattern->setDisabled(true);
    ui->actionNew_Group->setDisabled(true);
    ui->actionNew_Pattern->setDisabled(true);
    ui->actionPaste_pattern->setDisabled(true);
    ui->actionSave->setDisabled(true);

     connect(ui->actionOpen_directory,SIGNAL(triggered(bool)),this,SLOT(ouvrir_explorer()));
     connect(ui->actionNew_Group,SIGNAL(triggered(bool)),this,SLOT(insertGroup()));
     connect(ui->actionNew_Pattern,SIGNAL(triggered(bool)),this,SLOT(ajouter_motif()));

}

void MainWindow::ouvrir_explorer(){
    namedir=QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                   "/home"
                                               );
  if (namedir=="") return;
  QDir dir(namedir);
  QFileInfoList list=dir.entryInfoList(QDir::Files);
  QFileInfoList list2=dir.entryInfoList(QDir::Dirs);
  //on ne doit pas charger le dossier d'un groupe de motif mais plutot le repertoire des groupes de motif
  if ((!list.isEmpty()) and (!list2.isEmpty())) {
       QMessageBox::information(this,tr("warning"),"cannot open this directory, please choose the source directory");
       qDebug()<<"impossible";
       return;
  }
  tree();
  contextMenu = new QMenu(ui->treeView);
  ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
  insertMotif = new QAction("Inserer Motif",contextMenu);
  ui->treeView->addAction(insertMotif);
  connect(insertMotif,SIGNAL(triggered(bool)),this, SLOT(ajouter_motif()));

}

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
    ui->treeView->setColumnHidden(1,true);
    ui->treeView->setColumnHidden(2,true);
    ui->treeView->resizeColumnToContents(0);
    ui->actionNew_Group->setEnabled(true);
    ui->actionNew_Pattern->setEnabled(true);

}

void MainWindow::ajouter_motif(){
    QModelIndex index=ui->treeView->currentIndex();
    if (index.isValid()){

        if (model->fileInfo(index).isDir()) {
            QString dir=model->fileInfo(index).absolutePath();

            QString nameGroup=model->fileInfo(index).baseName();
             if((dir + "/" + nameGroup) !=namedir){
            qDebug()<<"le namedir est "+ namedir;
            qDebug()<<"la direction du dossier est "+dir;
            qDebug()<<"le nom du dossier est "+nameGroup;
            QString nameMotif=QInputDialog::getText(this,"Name","Enter the pattern name");
            NouveauMotif m=NouveauMotif(nameGroup,nameMotif,dir+"/"+nameGroup);
            tree();
            }
             else {
               QMessageBox::information(this,tr("warning"),"cannot add a pattern, please choose or add a group");
             }

        }
    }

}
void MainWindow::insertGroup(){

    QModelIndex index =model->index(namedir,0);
    if (!index.isValid()) return;
    QString name =QInputDialog::getText(this,"Name","Enter a name");
    if(name.isEmpty())return;
    model->mkdir(index,name);


}

MainWindow::~MainWindow()
{
    delete ui;
}


