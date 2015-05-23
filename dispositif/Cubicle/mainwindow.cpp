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


     connect(ui->actionOpen_directory,SIGNAL(triggered(bool)),this,SLOT(ouvrir_explorer()));
     connect(ui->actionOpen_directory,SIGNAL(triggered(bool)),this,SLOT(ouvrir_explorer()));
     connect(ui->actionCopy,SIGNAL(triggered(bool)),this,SLOT(copier()));
     connect(ui->actionPaste_pattern,SIGNAL(triggered(bool)),this,SLOT(coller()));
     insert_Group = new QAction("insert Group",this);
     connect(ui->actionNew_Group,SIGNAL(triggered(bool)),this,SLOT(insertGroup()));
     connect(ui->actionNew_Pattern,SIGNAL(triggered(bool)),this,SLOT(ajouter_motif()));

}

void MainWindow::ouvrir_explorer(){
    namedir=QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                   "/home",
                                                   QFileDialog::ShowDirsOnly
                                                   | QFileDialog::DontResolveSymlinks

                                               );

  QDir dir(namedir);
  QStringList filters(".cpp");
  QFileInfoList list=dir.entryInfoList(QDir::Files);
  QFileInfoList list2=dir.entryInfoList(QDir::Dirs);
  //on ne doit pas charger le dossier d'un groupe de motif mais plutot le repertoire des groupes de motif
  if ((!list.isEmpty())) {
       QMessageBox::information(this,tr("warning"),"can not open this directory, please choose the source directory");
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

void MainWindow::copier(){
    QModelIndex index=ui->treeView->currentIndex();
    if (model->fileInfo(index).isFile()) {
        dirOrFile=false;
        paste_element=model->fileInfo(index).absolutePath();
    }
}
void MainWindow::coller(){
    if (!dirOrFile){
        QModelIndex index=ui->treeView->currentIndex();
        if (index.isValid()){
            if (model->fileInfo(index).isDir()) {
                QString dir=model->fileInfo(index).absolutePath();
                QString nameGroup=model->fileInfo(index).baseName();
                QFile file(paste_element);
                bool valid = file.copy("C:/copieNext.txt");
                if (!valid){
                   qDebug()<<"coller impossible";
               }
    }

}

   }}

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


