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
#include <strstream>
#include <string>
#include <sstream>
#include <iostream>
#include "gestionfichier.h"
#include "cube.h"
#include <QPushButton>
#include <QPainter>
#include <QPainterPath>

using namespace std;

//MainWindow *MainWindow::_instance = NULL;

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
    ui->actionCut_pattern->setDisabled(true);
    ui->actionSave_as->setDisabled(true);
    ui->actionRaise->setDisabled(true);
    ui->actionLower->setDisabled(true);
    ui->actionNew_Group->setDisabled(true);

    //désactiver la sélection des plans
    ui->plane1->setDisabled(true);
     ui->plane2->setDisabled(true);
      ui->plane3->setDisabled(true);
       ui->plane4->setDisabled(true);
         ui->plane5->setDisabled(true);
          ui->plane6->setDisabled(true);
           ui->plane7->setDisabled(true);
            ui->plane8->setDisabled(true);
            ui->plane9->setDisabled(true);
    connect(ui->actionNew_project,SIGNAL(triggered(bool)),this,SLOT(new_project()));
    connect(ui->actionOpen_directory,SIGNAL(triggered(bool)),this,SLOT(ouvrir_explorer()));
    connect(ui->actionCopy,SIGNAL(triggered(bool)),this,SLOT(copier()));
    connect(ui->actionPaste_pattern,SIGNAL(triggered(bool)),this,SLOT(coller()));
    connect(ui->actionNew_Pattern,SIGNAL(triggered(bool)),this,SLOT(ajouter_motif()));
    connect(ui->actionQuit_2,SIGNAL(triggered(bool)),this,SLOT(controlQuit()));
    connect(ui->actionDelete_pattern,SIGNAL(triggered(bool)),this,SLOT(controlDelete()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(controlSave()));
    connect(ui->treeView,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(doubleClick()));
    connect(ui->actionCut_pattern,SIGNAL(triggered(bool)),this,SLOT(couper()));
    connect(ui->actionRaise,SIGNAL(triggered(bool)),this,SLOT(Monter()));
    connect(ui->actionLower,SIGNAL(triggered(bool)),this,SLOT(Descendre()));
    connect(ui->actionSave_as,SIGNAL(triggered(bool)),this,SLOT(controlSaveAs()));


    this->setWindowTitle("Cubicle");
    deletePlanLed(0);
    desactivePlan(0);
    connexion();
    dirOpen=false;

}

//ouvre le répertoire de travail
void MainWindow::ouvrir_explorer(){
  QString  tmpdir=QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home");
  if (tmpdir=="") {
      qDebug()<<tmpdir;
      return;
  }
  else {
      QFileInfo f=QFileInfo(tmpdir);
      //QDir dir(tmpdir);
      namedir = f.absolutePath();
      QString nomDossier=f.baseName();
      qDebug()<<" le nom duu dossier est "+nomDossier;
      if (nomDossier!="Cubicle") {
        QMessageBox::information(this,tr("warning"),"cannot open this directory, please choose the file Cubicle");
        ouvrir_explorer();
      }
      qDebug()<<" le chemin estttttt "+namedir;
  }

  QDir dir(namedir+"/Cubicle");
  QStringList nameFilter;
  nameFilter<<"*.txt";
  QFileInfoList list=dir.entryInfoList(nameFilter,QDir::Files);
  QFileInfoList list2=dir.entryInfoList(QDir::Dirs);
  //on ne doit pas charger le dossier d'un groupe de motif mais plutot le repertoire des groupes de motif
  if ((!list.isEmpty()) and (!list2.isEmpty())) {
       QMessageBox::information(this,tr("warning"),"cannot open this directory, please choose the source directory");
       qDebug()<<"impossible";
       return;
  }
  this->setWindowTitle("Cubicle["+namedir+"/Cubicle"+"]");
  // je copie le dossier Cubicle dans le workspace"
  QDir dir2(s+"/workspace/Cubicle");
  if (dir2.exists()){
      //qDebug()<<"avant removeDir :"+namedir+"/Cubicle";
      removeDir(s+"/workspace/Cubicle");
  }
  qDebug()<<"je crée cubicle pour la 1ere fois";
  xCopy2(namedir,s+"/workspace","Cubicle");
  tree();
  dirOpen=true;
  saved=false;
  ui->actionSave_as->setDisabled(false);
  this->c=Cube();
  deletePlanLed(1);
  desactivePlan(1);
  this->liste_vecteur3D.clear();
  this->ui->widget->setListPoints(liste_vecteur3D);
  ui->widget->setListPlan(liste_vecteur3D);
  ui->actionNew_Group->setDisabled(true);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event){
    if(dirOpen){
        contextMenu = new QMenu(ui->treeView);
        QModelIndex index=ui->treeView->currentIndex();
        if (model->fileInfo(index).isDir()) {
             QString s =model->fileInfo(index).absoluteFilePath();
             if(index.isValid()){
                  ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
                  QString dir=model->fileInfo(index).absolutePath();
                  QString nameGroup=model->fileInfo(index).baseName();
                  if((dir+'/'+nameGroup)!=namedir){
                          insertMotif = contextMenu->addAction("new pattern");
                          connect(insertMotif,SIGNAL(triggered(bool)),this, SLOT(ajouter_motif()));

                          QAction * paste;
                          paste = contextMenu->addAction("paste pattern");
                          connect(paste,SIGNAL(triggered(bool)),this, SLOT(coller()));

                          QAction * monter;
                          monter = contextMenu->addAction("Raise a repertory");
                          connect(monter, SIGNAL(triggered(bool)),this, SLOT(Monter()));

                          QAction * descendre;
                          descendre = contextMenu->addAction("Lower a repertory");
                          connect(descendre, SIGNAL(triggered(bool)),this, SLOT(Descendre()));
                  }
             }
    }

        if (model->fileInfo(index).isFile()){
              QString sp =model->fileInfo(index).absoluteFilePath();
              if(index.isValid()){
                   ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);

                   QAction * save;
                   save = contextMenu->addAction("save");
                   connect(save,SIGNAL(triggered(bool)),this, SLOT(controlSave()));

                   QAction * copy;
                   copy = contextMenu->addAction("copy pattern");
                   connect(copy,SIGNAL(triggered(bool)),this, SLOT(copier()));

                   QAction *cut = contextMenu->addAction("cut pattern");
                   connect(cut,SIGNAL(triggered(bool)),this, SLOT(couper()));

                   deletePattern = contextMenu->addAction("delete pattern");
                   connect(deletePattern,SIGNAL(triggered(bool)),this, SLOT(controlDelete()));
                }
        }

    contextMenu->exec(QCursor::pos());
    }
}


void MainWindow::couper(){
    copier();
    copierCouper=1;
}

void MainWindow::copier(){
    QModelIndex index=ui->treeView->currentIndex();
    if (model->fileInfo(index).isFile()) {
        dirOrFile=false;
        paste_element=model->fileInfo(index).absoluteFilePath();
        nom_copie=model->fileInfo(index).baseName();
        copierCouper=0;
        qDebug()<<nom_copie;
        qDebug()<<"j'ai copié : "+paste_element;
    }
}
void MainWindow::coller(){
     QString nameGroup;
     if (!dirOrFile){

        QModelIndex index=ui->treeView->currentIndex();
        if (index.isValid()){
            if (model->fileInfo(index).isDir()) {
                QString dir=model->fileInfo(index).absolutePath();
                nameGroup=model->fileInfo(index).baseName();
                if((dir+'/'+nameGroup)!=namedir){
                    QFile file(paste_element);
                     qDebug()<<"je vais coller  :"+dir+"/"+nameGroup+"/"+nom_copie+"_copie.txt";
                    bool valid = file.copy(dir+"/"+nameGroup+"/"+nom_copie+"_copie.txt");
                    if (copierCouper==1){
                        QFile file(paste_element);
                        file.remove();

                        new_index=model->index(dir+"/"+nameGroup);
                        tree();
                       index=model->index(dir+"/"+nameGroup+"/"+nom_copie+"_copie.txt");
                        ui->treeView->setCurrentIndex(index);
                        ui->treeView->selectionModel()->select(index,
                        QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
                        ui->treeView->edit(index);


                    }
                    if (!valid){
                       qDebug()<<"coller impossible";
                   }

                    new_index=model->index(dir+"/"+nameGroup);
                    tree();
                   new_index=model->index(dir+"/"+nameGroup+"/"+nom_copie+"_copie.txt");
                    ui->treeView->setCurrentIndex(new_index);
                    ui->treeView->selectionModel()->select(new_index,
                    QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
                    ui->treeView->edit(new_index);

                }
          }
        }
    }
}

void MainWindow::tree(){
            model = new QDirModel(this);
            model->setReadOnly(false);
            model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
    QModelIndex index=model->index(s+"/workspace");
    ui->treeView->setModel(model);
     ui->treeView->setRootIndex(index);
     index= model->index(s+"/workspace/Cubicle");
     ui->treeView->setExpanded(index,true);
     ui->treeView->scrollTo(index);
      connect(model,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(reordonneGroup()));
     if(new_index.isValid()){
     ui->treeView->setExpanded(new_index,true);
     ui->treeView->scrollTo(new_index);
     }
    for(int i=1;i<4;i++){
        ui->treeView->hideColumn(i);
    }
    ui->treeView->resizeColumnToContents(0);
    ui->actionNew_Pattern->setEnabled(true);
    ui->actionDelete_pattern->setEnabled(true);
    ui->actionCopy->setDisabled(false);
    ui->actionPaste_pattern->setDisabled(false);
    ui->actionCut_pattern->setDisabled(false);
    ui->actionSave->setDisabled(false);
    ui->actionRaise->setDisabled(false);
    ui->actionLower->setDisabled(false);
    ui->actionNew_Group->setDisabled(false);


}

//créer un nouveau motif
void MainWindow::ajouter_motif(){
    QModelIndex index=ui->treeView->currentIndex();
    if (index.isValid()){

        if (model->fileInfo(index).isDir()) {

            QString dir=model->fileInfo(index).absolutePath();

            QString nameGroup=model->fileInfo(index).baseName();
             if((dir + "/" + nameGroup) !=s){
            qDebug()<<"le namedir est "+ namedir;
            qDebug()<<"l'emplacement du dossier est "+dir;
            qDebug()<<"le nom du dossier est "+nameGroup;
            if(nameGroup!="Cubicle"){

                    NouveauMotif m=NouveauMotif("New Pattern",dir+"/"+nameGroup);



                    new_index =model->index(s+"/workspace/Cubicle"+"/"+ nameGroup );
                           tree();
                            new_index =model->index(m.getNameFile());

                             qDebug() << "le path du pattern ajoute est "+ m.getNameFile();
                             ui->treeView->setCurrentIndex(new_index);
                             ui->treeView->selectionModel()->select(new_index,
                             QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
                             ui->treeView->edit(new_index);

            }
            else {
               QMessageBox::information(this,tr("warning"),"cannot add a pattern, please choose or add a group");
            }
        }
       }
    }
}
void MainWindow::new_project(){
    if (!saved) {
        int enregistrer=QMessageBox::question(this, "Quit", " Do you want to save the current project ?");
        if (enregistrer==QMessageBox::Yes){
            controlSave();

        }

    }

     model = new QDirModel(this);
     model->setReadOnly(false);
     model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
     QModelIndex index=model->index(s);
     model->mkdir(index,"workspace");
        QDir dir(s+"/workspace/Cubicle");
        if (dir.exists()){
            //qDebug()<<"avant removeDir :"+namedir+"/Cubicle";
            removeDir(s+"/workspace/Cubicle");
        }
       qDebug()<<"je crée cubicle pour la 1ere fois";
       new_index=model->index(s+"/workspace");
       model->mkdir(new_index,"Cubicle");
      namedir="";
      saved=false;
    dirOpen=true;
    this->setWindowTitle("Cubicle") ;
            tree();
            ui->actionSave_as->setDisabled(false);
            saved=false;
            this->c=Cube();
            deletePlanLed(1);
            desactivePlan(1);
            this->liste_vecteur3D.clear();
            this->ui->widget->setListPoints(liste_vecteur3D);
            ui->widget->setListPlan(liste_vecteur3D);
            ui->actionNew_Group->setDisabled(true);

}

void MainWindow::on_actionNew_Group_triggered()
{   int m;
    QString indice;
    //if (namedir==s+"/workspace"){
    QModelIndex index =model->index(s+"/workspace/Cubicle",0);
    QString name ="NewGroup";
    QDir dir(s+"/workspace/Cubicle");
    QFileInfoList entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
    dir.setSorting( QDir::Name);
    m=entries.size();
    if (m<10){
        indice ="0"+QString::number(m)+"_";
    }else {
       indice=QString::number(m)+"_";
    }
    qDebug() << "s contient "+ s;
    name = indice + name;
     qDebug() << "s contient "+ name;
    model->mkdir(index,name);
    qDebug()<<"j'ai crée un dossier ds "+namedir;
       new_index =model->index(s+"/workspace/Cubicle");
    // qDebug()<<"le new index est " + s+"/workspace/Cubicle";
     new_index =model->index(s+"/workspace/Cubicle");
    tree();
  new_index =model->index(s+"/workspace/Cubicle/"+name);
  qDebug() << "le nouveau index pointe sur "+s+"/workspace/Cubicle/"+name;
  ui->treeView->setCurrentIndex(new_index);
  ui->treeView->selectionModel()->select(new_index,
         QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
  ui->treeView->edit(new_index);


}
    /*else {
        QModelIndex index =model->index(namedir,0);
        QString name ="NewGroup";
        QDir dir(namedir);
        QFileInfoList entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
        dir.setSorting( QDir::Name);
        m=entries.size();
        if (m<10){
            s = "0"+QString::number(m)+"_";
        }else {
            s = QString::number(m)+"_";

        }
        name = s + name;
        model->mkdir(index,name);
        qDebug()<<"j'ai crée un dossier ds "+namedir;
           new_index =model->index(namedir);
         qDebug()<<"le new index est " + namedir;
         new_index =model->index(namedir);
      ui->treeView->expand(new_index);
      ui->treeView->scrollTo(new_index);

      new_index =model->index(namedir+"/"+name);
      ui->treeView->setCurrentIndex(new_index);
      ui->treeView->selectionModel()->select(new_index,
             QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
      ui->treeView->edit(new_index);

    }*/



void MainWindow::Monter(){
    QString nameGroup;
    QString newNameGroup;
    QString nameGroupDessus;
    QString nameMotif;
    QString newNameMotif;
    QString nameMotifDessus;
    QModelIndex index=ui->treeView->currentIndex();
    QModelIndex indexMoinsUn=ui->treeView->indexAbove(index);

    if (index.isValid()){
           if (model->fileInfo(index).isDir()) {
               while(model->fileInfo(indexMoinsUn).isFile()){
                   indexMoinsUn=ui->treeView->indexAbove(indexMoinsUn);
               }

                QString dir=model->fileInfo(index).absolutePath();
                nameGroup=model->fileInfo(index).baseName();
                nameGroupDessus=model->fileInfo(indexMoinsUn).baseName();
                qDebug()<<nameGroup;
                qDebug()<<dir;

                QString numero = nameGroup.left(2);
                QString nameRest = nameGroup.mid(3);
                QString numeroDessus = nameGroupDessus.left(2);
                QString nameDessusRest = nameGroupDessus.mid(3);
                int num = numero.toInt();
                int numDessus = numeroDessus.toInt();
                if(num==0){
                    return;
                }
                if (num<11){
                    newNameGroup = "0"+QString::number(num-1)+"_"+nameRest;
                }else {
                    newNameGroup = QString::number(num-1)+"_"+nameRest;
                }
                QString pathTotalOld = dir+"/"+nameGroup;
                QString pathTotalNew = dir+"/"+newNameGroup;

                if (num<10){
                    if (numDessus==num-1){
                        QString nameGroupMoinsUn = "0"+QString::number(num-1)+"_"+nameDessusRest;
                        qDebug()<<nameGroupMoinsUn;
                        QString totalnameGroupMoinsUn = dir+"/"+nameGroupMoinsUn;

                        QString nameGroupMoinsUnChange = nameDessusRest;
                        QString totalnameGroupMoinsUnChange = dir+"/"+nameGroupMoinsUnChange;

                        QDir directory(totalnameGroupMoinsUn);
                        directory.rename(totalnameGroupMoinsUn,totalnameGroupMoinsUnChange);

                        QDir dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameGroupMoinsUnChangeCorrect = "0"+QString::number(num)+"_"+nameDessusRest;
                        qDebug()<<nameGroupMoinsUnChangeCorrect;
                        QString totalnameGroupMoinsUnCorrect = dir+"/"+nameGroupMoinsUnChangeCorrect;
                        QDir dir2(totalnameGroupMoinsUnCorrect);
                        dir2.rename(totalnameGroupMoinsUnChange, totalnameGroupMoinsUnCorrect);
                        dir2.setSorting(QDir::Name);
                    }
                }else if(num==10){
                    if (numDessus==num-1){
                        QString nameGroupMoinsUn = "0"+QString::number(num-1)+"_"+nameDessusRest;
                        QString totalnameGroupMoinsUn = dir+"/"+nameGroupMoinsUn;

                        QString nameGroupMoinsUnChange = nameDessusRest;
                        QString totalnameGroupMoinsUnChange = dir+"/"+nameGroupMoinsUnChange;

                        QDir directory(totalnameGroupMoinsUn);
                        directory.rename(totalnameGroupMoinsUn,totalnameGroupMoinsUnChange);

                        QDir dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameGroupMoinsUnChangeCorrect = QString::number(num)+"_"+nameDessusRest;
                        QString totalnameGroupMoinsUnCorrect = dir+"/"+nameGroupMoinsUnChangeCorrect;
                        QDir dir2(totalnameGroupMoinsUnCorrect);
                        dir2.rename(totalnameGroupMoinsUnChange, totalnameGroupMoinsUnCorrect);
                        dir2.setSorting(QDir::Name);
                    }
                }else if(num>10){
                    if (numDessus==num-1){
                        QString nameGroupMoinsUn = QString::number(num-1)+"_"+nameDessusRest;
                        QString totalnameGroupMoinsUn = dir+"/"+nameGroupMoinsUn;

                        QString nameGroupMoinsUnChange = nameDessusRest;
                        QString totalnameGroupMoinsUnChange = dir+"/"+nameGroupMoinsUnChange;

                        QDir directory(totalnameGroupMoinsUn);
                        directory.rename(totalnameGroupMoinsUn,totalnameGroupMoinsUnChange);

                        QDir dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameGroupMoinsUnChangeCorrect = QString::number(num)+"_"+nameDessusRest;
                        QString totalnameGroupMoinsUnCorrect = dir+"/"+nameGroupMoinsUnChangeCorrect;
                        QDir dir2(totalnameGroupMoinsUnCorrect);
                        dir2.rename(totalnameGroupMoinsUnChange, totalnameGroupMoinsUnCorrect);
                        dir2.setSorting(QDir::Name);
                    }
                }
                this->tree();
         }else{
                QString dir=model->fileInfo(index).absolutePath();
                nameMotif=model->fileInfo(index).baseName();
                nameMotifDessus=model->fileInfo(indexMoinsUn).baseName();
                qDebug()<<nameMotif;
                 qDebug()<<"hahahahhahhahhahhahhah";
                qDebug()<<dir;

                QString numero = nameMotif.left(2);
                QString nameRest = nameMotif.mid(3);
                QString numeroDessus = nameMotifDessus.left(2);
                QString nameDessusRest = nameMotifDessus.mid(3);
                int num = numero.toInt();
                int numDessus = numeroDessus.toInt();
                if(num==0){
                    return;
                }
                if (num<11){
                    newNameMotif = "0"+QString::number(num-1)+"_"+nameRest;
                }else {
                    newNameMotif = QString::number(num-1)+"_"+nameRest;
                }
                QString pathTotalOld = dir+"/"+nameMotif+".txt";
                QString pathTotalNew = dir+"/"+newNameMotif+".txt";

                if (num<10){
                    if (numDessus==num-1){
                        QString nameMotifMoinsUn = "0"+QString::number(num-1)+"_"+nameDessusRest+".txt";
                        qDebug()<<"hahahahhahhahhahhahhah";
                        qDebug()<<nameMotifMoinsUn;
                        QString totalnameMotifMoinsUn = dir+"/"+nameMotifMoinsUn;
                         qDebug()<<"ooooooooooooooooooooooo";
                        qDebug()<<totalnameMotifMoinsUn;

                        QString nameMotifMoinsUnChange = nameDessusRest;
                        QString totalnameMotifMoinsUnChange = dir+"/"+nameMotifMoinsUnChange+".txt";
                         qDebug()<<"avdfgdfgdffdgdfgfdgdfgd";
                        qDebug()<<totalnameMotifMoinsUnChange;

                        QFile directory(totalnameMotifMoinsUn);
                        directory.rename(totalnameMotifMoinsUnChange);

                        QFile dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameMotifMoinsUnChangeCorrect = "0"+QString::number(num)+"_"+nameDessusRest+".txt";
                        qDebug()<<"hahahahhahhahhahhahhah";
                        qDebug()<<nameMotifMoinsUnChangeCorrect;
                        QString totalnameMotifMoinsUnCorrect = dir+"/"+nameMotifMoinsUnChangeCorrect;
                        qDebug()<<"aaaaaaaaaaaaaaaaaaaaaaaaaaa";
                        qDebug()<<totalnameMotifMoinsUnCorrect;
                        QFile dir2(totalnameMotifMoinsUnChange);
                        dir2.rename(totalnameMotifMoinsUnChange, totalnameMotifMoinsUnCorrect);
                    }
                }else if(num==10){
                    if (numDessus==num-1){
                        QString nameMotifMoinsUn = "0"+QString::number(num-1)+"_"+nameDessusRest+".txt";
                        QString totalnameMotifMoinsUn = dir+"/"+nameMotifMoinsUn;

                        QString nameMotifMoinsUnChange = nameDessusRest;
                        QString totalnameMotifMoinsUnChange = dir+"/"+nameMotifMoinsUnChange+".txt";

                        QFile directory(totalnameMotifMoinsUn);
                        directory.rename(totalnameMotifMoinsUn,totalnameMotifMoinsUnChange);

                        QFile dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameMotifMoinsUnChangeCorrect = QString::number(num)+"_"+nameDessusRest+".txt";
                        QString totalnameMotifMoinsUnCorrect = dir+"/"+nameMotifMoinsUnChangeCorrect;
                        QFile dir2(totalnameMotifMoinsUnCorrect);
                        dir2.rename(totalnameMotifMoinsUnChange, totalnameMotifMoinsUnCorrect);
                    }
                }else if(num>10){
                    if (numDessus==num-1){
                        QString nameMotifMoinsUn = QString::number(num-1)+"_"+nameDessusRest+".txt";
                        QString totalnameMotifMoinsUn = dir+"/"+nameMotifMoinsUn;

                        QString nameMotifMoinsUnChange = nameDessusRest;
                        QString totalnameMotifMoinsUnChange = dir+"/"+nameMotifMoinsUnChange+".txt";

                        QFile directory(totalnameMotifMoinsUn);
                        directory.rename(totalnameMotifMoinsUn,totalnameMotifMoinsUnChange);

                        QFile dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameMotifMoinsUnChangeCorrect = QString::number(num)+"_"+nameDessusRest+".txt";
                        QString totalnameMotifMoinsUnCorrect = dir+"/"+nameMotifMoinsUnChangeCorrect;
                        QFile dir2(totalnameMotifMoinsUnCorrect);
                        dir2.rename(totalnameMotifMoinsUnChange, totalnameMotifMoinsUnCorrect);
                    }
                }
                this->tree();

         }
    }
}
////////////////////////////////////////////////////////////////////////////////
void MainWindow::Descendre(){
    QString nameGroup;
    QString newNameGroup;
    QString nameGroupDessous;
    QString nameMotif;
    QString newNameMotif;
    QString nameMotifDessous;
    QModelIndex index=ui->treeView->currentIndex();
    QModelIndex indexPlusUn=ui->treeView->indexBelow(index);

       if (index.isValid()){
           if (model->fileInfo(index).isDir()) {

                QString dir=model->fileInfo(index).absolutePath();
                nameGroup=model->fileInfo(index).baseName();
                QDir temp(dir);
                QFileInfoList entries = temp.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
                int m=entries.size();
                QString numero = nameGroup.left(2);
                int num = numero.toInt();
                if(num==m-1){
                    qDebug()<<"Les numeros sont egaux";
                    return;
                }

                while(model->fileInfo(indexPlusUn).isFile()){
                    indexPlusUn=ui->treeView->indexBelow(indexPlusUn);
                }
                nameGroupDessous=model->fileInfo(indexPlusUn).baseName();
                QString nameRest = nameGroup.mid(3);
                QString numeroDessous = nameGroupDessous.left(2);
                QString nameDessousRest = nameGroupDessous.mid(3);

                int numDessous = numeroDessous.toInt();


                if (num<9){
                    newNameGroup = "0"+QString::number(num+1)+"_"+nameRest;
                }else {
                    newNameGroup = QString::number(num+1)+"_"+nameRest;
                }
                QString pathTotalOld = dir+"/"+nameGroup;
                QString pathTotalNew = dir+"/"+newNameGroup;

                if (num<9){
                    if (numDessous==num+1){
                        QString nameGroupPlusUn = "0"+QString::number(num+1)+"_"+nameDessousRest;
                        qDebug()<<nameGroupPlusUn;
                        QString totalnameGroupPlusUn = dir+"/"+nameGroupPlusUn;

                        QString nameGroupPlusUnChange = nameDessousRest;
                        QString totalnameGroupPlusUnChange = dir+"/"+nameGroupPlusUnChange;

                        QDir directory(totalnameGroupPlusUn);
                        directory.rename(totalnameGroupPlusUn,totalnameGroupPlusUnChange);

                        QDir dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameGroupPlusUnChangeCorrect = "0"+QString::number(num)+"_"+nameDessousRest;
                        qDebug()<<nameGroupPlusUnChangeCorrect;
                        QString totalnameGroupPlusUnCorrect = dir+"/"+nameGroupPlusUnChangeCorrect;
                        QDir dir2(totalnameGroupPlusUnCorrect);
                        dir2.rename(totalnameGroupPlusUnChange, totalnameGroupPlusUnCorrect);
                        dir2.setSorting(QDir::Name);
                    }
                }else if(num==9){
                    if (numDessous==num+1){
                        QString nameGroupPlusUn = QString::number(num+1)+"_"+nameDessousRest;
                        QString totalnameGroupPlusUn = dir+"/"+nameGroupPlusUn;

                        QString nameGroupPlusUnChange = nameDessousRest;
                        QString totalnameGroupPlusUnChange = dir+"/"+nameGroupPlusUnChange;

                        QDir directory(totalnameGroupPlusUn);
                        directory.rename(totalnameGroupPlusUn,totalnameGroupPlusUnChange);

                        QDir dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameGroupPlusUnChangeCorrect = "0"+QString::number(num)+"_"+nameDessousRest;
                        QString totalnameGroupPlusUnCorrect = dir+"/"+nameGroupPlusUnChangeCorrect;
                        QDir dir2(totalnameGroupPlusUnCorrect);
                        dir2.rename(totalnameGroupPlusUnChange, totalnameGroupPlusUnCorrect);
                        dir2.setSorting(QDir::Name);
                    }
                }else if(num>9){
                    if (numDessous==num+1){
                        QString nameGroupPlusUn = QString::number(num+1)+"_"+nameDessousRest;
                        QString totalnameGroupPlusUn = dir+"/"+nameGroupPlusUn;

                        QString nameGroupPlusUnChange = nameDessousRest;
                        QString totalnameGroupPlusUnChange = dir+"/"+nameGroupPlusUnChange;

                        QDir directory(totalnameGroupPlusUn);
                        directory.rename(totalnameGroupPlusUn,totalnameGroupPlusUnChange);

                        QDir dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameGroupPlusUnChangeCorrect = QString::number(num)+"_"+nameDessousRest;
                        QString totalnameGroupPlusUnCorrect = dir+"/"+nameGroupPlusUnChangeCorrect;
                        QDir dir2(totalnameGroupPlusUnCorrect);
                        dir2.rename(totalnameGroupPlusUnChange, totalnameGroupPlusUnCorrect);
                        dir2.setSorting(QDir::Name);
                    }
                }

                this->tree();

         }else{
               QString dir=model->fileInfo(index).absolutePath();
               nameMotif=model->fileInfo(index).baseName();
               QDir temp(dir);
               QFileInfoList entries = temp.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
               int m=entries.size();
               QString numero = nameMotif.left(2);
               int num = numero.toInt();
               if(num==m-1){
                   qDebug()<<"Les numeros sont egaux";
                   return;
               }

               nameMotifDessous=model->fileInfo(indexPlusUn).baseName();
               QString nameRest = nameMotif.mid(3);
               QString numeroDessous = nameMotifDessous.left(2);
               QString nameDessousRest = nameMotifDessous.mid(3);

               int numDessous = numeroDessous.toInt();


               if (num<9){
                   newNameMotif = "0"+QString::number(num+1)+"_"+nameRest;
               }else {
                   newNameMotif = QString::number(num+1)+"_"+nameRest;
               }
               QString pathTotalOld = dir+"/"+nameMotif+".txt";
               QString pathTotalNew = dir+"/"+newNameMotif+".txt";

               if (num<9){
                   if (numDessous==num+1){
                       QString nameMotifPlusUn = "0"+QString::number(num+1)+"_"+nameDessousRest+".txt";
                       qDebug()<<nameMotifPlusUn;
                       QString totalnameMotifPlusUn = dir+"/"+nameMotifPlusUn;

                       QString nameMotifPlusUnChange = nameDessousRest;
                       QString totalnameMotifPlusUnChange = dir+"/"+nameMotifPlusUnChange+".txt";

                       QFile directory(totalnameMotifPlusUn);
                       directory.rename(totalnameMotifPlusUn,totalnameMotifPlusUnChange);

                       QFile dir1(pathTotalOld);
                       dir1.rename(pathTotalOld, pathTotalNew);

                       QString nameMotifPlusUnChangeCorrect = "0"+QString::number(num)+"_"+nameDessousRest+".txt";
                       qDebug()<<nameMotifPlusUnChangeCorrect;
                       QString totalnameMotifPlusUnCorrect = dir+"/"+nameMotifPlusUnChangeCorrect;
                       QFile dir2(totalnameMotifPlusUnCorrect);
                       dir2.rename(totalnameMotifPlusUnChange, totalnameMotifPlusUnCorrect);
                   }
               }else if(num==9){
                   if (numDessous==num+1){
                       QString nameMotifPlusUn = QString::number(num+1)+"_"+nameDessousRest+".txt";
                       QString totalnameMotifPlusUn = dir+"/"+nameMotifPlusUn;

                       QString nameMotifPlusUnChange = nameDessousRest;
                       QString totalnameMotifPlusUnChange = dir+"/"+nameMotifPlusUnChange+".txt";

                       QFile directory(totalnameMotifPlusUn);
                       directory.rename(totalnameMotifPlusUn,totalnameMotifPlusUnChange);

                       QFile dir1(pathTotalOld);
                       dir1.rename(pathTotalOld, pathTotalNew);

                       QString nameMotifPlusUnChangeCorrect = "0"+QString::number(num)+"_"+nameDessousRest+".txt";
                       QString totalnameMotifPlusUnCorrect = dir+"/"+nameMotifPlusUnChangeCorrect;
                       QFile dir2(totalnameMotifPlusUnCorrect);
                       dir2.rename(totalnameMotifPlusUnChange, totalnameMotifPlusUnCorrect);
                   }
               }else if(num>9){
                   if (numDessous==num+1){
                       QString nameMotifPlusUn = QString::number(num+1)+"_"+nameDessousRest+".txt";
                       QString totalnameMotifPlusUn = dir+"/"+nameMotifPlusUn;

                       QString nameMotifPlusUnChange = nameDessousRest;
                       QString totalnameMotifPlusUnChange = dir+"/"+nameMotifPlusUnChange+".txt";

                       QFile directory(totalnameMotifPlusUn);
                       directory.rename(totalnameMotifPlusUn,totalnameMotifPlusUnChange);

                       QFile dir1(pathTotalOld);
                       dir1.rename(pathTotalOld, pathTotalNew);

                       QString nameMotifPlusUnChangeCorrect = QString::number(num)+"_"+nameDessousRest+".txt";
                       QString totalnameMotifPlusUnCorrect = dir+"/"+nameMotifPlusUnChangeCorrect;
                       QFile dir2(totalnameMotifPlusUnCorrect);
                       dir2.rename(totalnameMotifPlusUnChange, totalnameMotifPlusUnCorrect);
                   }
               }

               this->tree();
         }

   }

}

void MainWindow::controlQuit(){
    if (!this->saved) {
        int enregistrer=QMessageBox::question(this, "Quit", " Do you want to save the project before you quit ?");
        if (enregistrer==QMessageBox::Yes){
            controlSave();
            this->close();
        }
        else
        {
            this->close();
        }
    }
        else {
        this->close();
    }
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    controlQuit();
}


void MainWindow::controlDelete(){
    QModelIndex index=ui->treeView->currentIndex();
    if (model->fileInfo(index).isFile()) {
        dirOrFile=false;

         QString name=model->fileInfo(index).absoluteFilePath();
         QString path=model->fileInfo(index).absolutePath();
         qDebug() << "le path du fichier à supprimer est "+path;
         QFile file(name);
         int reponse = QMessageBox::question(this, "Quit", " Are you sure you want to delete this pattern ?");
           if (reponse == QMessageBox::Yes) {
               file.remove();
              new_index=model->index(path);
              tree();
              ui->treeView->setCurrentIndex(new_index);
              ui->treeView->selectionModel()->select(new_index,
                     QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);

               this->deletePlanLed(1);
               this->desactivePlan(1);
           }
    }
    else {
        dirOrFile=true;
    }
}
void MainWindow::controlSave(){
    GestionFichier ges;
    ges.ouvrir(this->emplMotif,this->c);
    if (namedir=="") {
        controlSaveAs();
    }
    else {
        removeDir(namedir+"/Cubicle");
        xCopy2(s+"/workspace",namedir,"Cubicle");
        saved=true;
        QMessageBox msgBox;
        msgBox.setText("Your project Cubicle has been succesfully saved");
        msgBox.exec();
    }

}
void MainWindow::controlSaveAs(){
    qDebug()<<"je suis dans controlSaveAs";
    QString destPath=QFileDialog::getExistingDirectory(this, tr("Open Directory"),

                                                   "/home"
                                               );
    if (destPath=="") {qDebug()<<destPath;
        return;}
    qDebug()<<"l'origine est "+namedir;
    qDebug()<<"la destination est"+destPath;
    QDir dir(destPath+"/Cubicle");
    if (dir.exists()) {

        int remplacer=QMessageBox::question(this, "Exist", "Project Cubicle already exists in this directory, do you want to replace it ?");
        if (remplacer==QMessageBox::No){
            controlSaveAs();
        }
        else {
            namedir=destPath;
            controlSave();
        }

    }
    else {
    namedir= destPath;
    qDebug()<< "le nouveau path est" + namedir;
    controlSave();
    this->setWindowTitle("Cubicle["+destPath+"/Cubicle"+"]") ;

    }
}

/*void MainWindow::controlSave(){

    QMessageBox msgBox;
    msgBox.setText("Your pattern "+currentPattern +" has been succesfully saved");
    msgBox.exec();
}*/

void MainWindow::xCopy2 (const QString &sourcePath, const QString &destPath, const QString &name)
{
    static const QStringList filters = QStringList () << "*";
    static const QDir::Filters flags = QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files | QDir::Hidden;

    QString sourceObjectPath = sourcePath+"/"+name;
    QString destObjectPath = destPath +"/"+name;
    QDir dir(destObjectPath);
    if (dir.exists()) {
        removeDir(destObjectPath) ;
        qDebug()<<"j'ai supprimé le dossier "+destObjectPath;
    }
    QFileInfo fi (sourceObjectPath);

    if (fi.isDir ()) {
        qDebug () << "Créer le répertoire " << destObjectPath;
        QDir destDir(destPath);
        destDir.mkdir(name);

        qDebug () << "Recopier dedans, récursivement, le contenu de" << sourceObjectPath;
        //sourceObjectPath += '/';
        //destObjectPath += '/';
        QDir currentSourceDir (sourceObjectPath);
        const QStringList fileList = currentSourceDir.entryList (filters, flags);
        foreach (const QString &content, fileList) {
            xCopy2 (sourceObjectPath, destObjectPath, content);
        }
    } else {
        qDebug () << "Copier le fichier " << name << "de" << sourcePath << "vers" << destPath;
        QFile::copy (sourceObjectPath, destObjectPath);


    }





}

void MainWindow::removeDir(const QString& PathDir)
{


 //Création de l'itérateur, on précise qu'on veut tous les sous-dossiers
 QDirIterator dirIterator(PathDir, QDirIterator::Subdirectories);

  //On récupère les fichiers et dossiers grâce à l'itérateur
  QFileInfoList fileList;

  while(dirIterator.hasNext())
  {
      dirIterator.next();
      fileList << dirIterator.fileInfo();
  }
  QString t;
  t=QString::number(fileList.size());
  qDebug()<<"la taille de la liste est "+t;
  //On parcours les éléments
  QStringList directories;
  for(int i = fileList.count() - 1; i >=0 ; i--)
  {
    //Si l'élément est un fichier, on le supprime
    if(fileList.at(i).isFile()) {
        QFile::remove(fileList.at(i).absoluteFilePath());
    //On stocke le dossier contenant cet élément dans un liste (si ce n'est pas déjà fait)
    if(!directories.contains(fileList.at(i).absolutePath()))
        directories << fileList.at(i).absolutePath();
    }
    else if( fileList.at(i).isDir() && (!directories.contains(fileList.at(i).completeBaseName()))){


    directories << fileList.at(i).absolutePath()+"/"+fileList.at(i).completeBaseName();

    qDebug()<<"j'ajoute le dossier "+fileList.at(i).completeBaseName();

  }
  }

  QDir dir = QDir::root();

  //Finalement, on supprime tous les dossiers
  QString s;
  s=QString::number(directories.size());
  qDebug()<<"la taille de la liste dir est "+s;
  foreach( const QString StrDir, directories)
  {
     qDebug()<<"je supprime le dossier "+StrDir;
     dir.rmdir(StrDir);
  }
  dir.rmdir(PathDir); // on supprime finalement le dossier Cubicle.
}


void MainWindow::reordonneGroup(){
         QModelIndex index = ui->treeView->currentIndex();
         if (model->fileInfo(index).isDir()){
        int i= index.row();
        qDebug() << "le rang du groupe est"+ QString::number(i);
         QString nameGroup = model->fileName(index);
         qDebug() << "le nom du groupe à modifier est "+ nameGroup;
         QString path = model->fileInfo(index).absolutePath();
         qDebug() << "le path du groupe est "+ path;
         QDir dir(path);
        QString indice;
        if (i<10){
            indice = "0"+QString::number(i)+"_";
            }else {
             indice = QString::number(i)+"_";
                  }

        QString newNameGroup=indice+nameGroup;
         QString pathTotalOld = path+"/"+nameGroup;
         QString pathTotalNew = path+"/"+newNameGroup;
          dir.rename(pathTotalOld,pathTotalNew);
         }



     }


//extern "C" int* parser_file(const char* name);


// supprimer  le plan 2D Lors d'un double clic sur un nouveau motif
void MainWindow::doubleClick(){
     QModelIndex index=ui->treeView->currentIndex();
     if (model->fileInfo(index).isFile()) {
        dirOrFile=false;

        //réactiver la sélection des plans
        ui->plane1->setDisabled(false);
        ui->plane2->setDisabled(false);
        ui->plane3->setDisabled(false);
        ui->plane4->setDisabled(false);
        ui->plane5->setDisabled(false);
        ui->plane6->setDisabled(false);
        ui->plane7->setDisabled(false);
        ui->plane8->setDisabled(false);
        ui->plane9->setDisabled(false);

         QString name=model->fileInfo(index).absoluteFilePath();
         this->currentPattern=model->fileInfo(index).baseName();
         if(name.compare(this->getEmplMotif())!=0){
             GestionFichier ges;
             ges.ouvrir(this->emplMotif,this->c);
             this->setEmpMotif(name);
             qDebug ()<< "nouveau motif "+this->getEmplMotif();
             qDebug ()<< "nom pattern "+currentPattern;
             this->c=Cube();
             deletePlanLed(1);
             desactivePlan(1);

             this->liste_vecteur3D.clear();
             this->ui->widget->setListPoints(liste_vecteur3D);
             ui->widget->setListPlan(liste_vecteur3D);
       //      int* tab;
         //  std::string nameStd = name.toStdString();
         //  const char* nomFichier= nameStd.c_str();
         //  tab=parser_file(nomFichier);
           //        int h=tab[1];
             //      QString lh=QString::number(h);
               //    qDebug()<<"premier elmt ds tab "+lh;
                   //GestionFichier ges;

                 //  QList<QVector3D> l=ges.tabToVector3D(tab);
                   // int x=l.first().x();
                   // QString lll=QString::number(x);
                  //  qDebug()<<"premier elmt "+lll;

                    QList<QVector3D> l;
                    l=ges.parser(name,l);
                     if(!l.empty()){

                         this->ui->widget->setListPoints(l);

                         for (QVector3D u:l){
                           Led l=this->c.getList1()->value(u.y()).getLed(fabs(8-u.z()),fabs(8-u.x()));
                           l.modifierEtat();
                           Plan p=c.getList1()->value(u.y());
                           p.updatePlan(l,fabs(8-u.z()),fabs(8-u.x()),u.y());
                           this->c.updateCube(p,u.y());
                           liste_vecteur3D.append(u);
                           this->ui->widget->setListPoints(liste_vecteur3D);
                         }
                     }
                 }
    else {
        dirOrFile=true;
    }
}
}


void MainWindow::desactivePlan(int niemefois){


            //déselectionner les plans
            ui->plane1->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
             ui->plane2->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
              ui->plane3->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
               ui->plane4->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
                 ui->plane5->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
                  ui->plane6->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
                   ui->plane7->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
                    ui->plane8->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
                    ui->plane9->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");


}


void MainWindow::affichePlanLed(const QString & valeur){

    ui->plane1->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
     ui->plane2->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
      ui->plane3->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
       ui->plane4->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
         ui->plane5->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
          ui->plane6->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
           ui->plane7->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
            ui->plane8->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
            ui->plane9->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");

    QString stnplan=valeur[1];

    int nplan=stnplan.toInt(0,10);

    this->setNumeroPlan(nplan);

    switch(nplan){
    case 0:ui->plane1->setStyleSheet("QPushButton { background-color: red; }"); break;
    case 1:ui->plane2->setStyleSheet("QPushButton { background-color: red; }"); break;
    case 2:ui->plane3->setStyleSheet("QPushButton { background-color: red; }"); break;
    case 3:ui->plane4->setStyleSheet("QPushButton { background-color: red; }"); break;
    case 4:ui->plane5->setStyleSheet("QPushButton { background-color: red; }"); break;
    case 5:ui->plane6->setStyleSheet("QPushButton { background-color: red; }"); break;
    case 6:ui->plane7->setStyleSheet("QPushButton { background-color: red; }"); break;
    case 7:ui->plane8->setStyleSheet("QPushButton { background-color: red; }"); break;
    case 8:ui->plane9->setStyleSheet("QPushButton { background-color: red; }"); break;
    }

    QList<QVector3D> ll;
    for(int i=0;i<9;i++)
        for(int k=0;k<9;k++)
        {QVector3D v;
            v= QVector3D(i,nplan,k);
            ll.append(v);
            this->ui->widget->setListPlan(ll);
        }

   for (int i = 0; i < 9; i++) {
        for (int j=0;j<9; j++){
           QString col=QString::number(i);
           QString lig=QString::number(j);
           QString text=lig+col;

           int num=text.toInt(0,10);
           buttons[num]->setVisible(true);

           Led l;
           l=c.getList1()->value(this->NumeroPlan).getLed(j,i);

           if(l.getEtat()==0){
               buttons[num]->setIcon(QIcon(":/icone/nvatomeblanc.png"));
           }
           else {
               buttons[num]->setIcon(QIcon(":/icone/atome.gif"));
           }
       }
    }
}

void MainWindow::deletePlanLed(int nfois){


        for (int i = 0; i < 9; i++) {
             for (int j=0;j<9; j++){
                 QString col=QString::number(i);
                 QString lig=QString::number(j);
                 QString text=lig+col;
                 int num=text.toInt(0,10);
                  if(nfois==0){
                         buttons[num]=new QPushButton("",this);
                         buttons[num]->setGeometry(30, 30, 30, 30);
                         buttons[num]->move(30*i+320, 30*j+90);
                  }
                 buttons[num]->hide();
             }
    }
}

void MainWindow::controlLed(const QString & valeur){
   QString strlig=valeur[0];
   QString strcol=valeur[1];
   int lig=strlig.toInt(0,10);
   int col=strcol.toInt(0,10);
  Led l;
  l= this->c.getList1()->value(NumeroPlan).getLed(lig,col);
  l.modifierEtat();

  Plan p1=c.getList1()->value(this->NumeroPlan);
  p1.updatePlan(l,lig,col,NumeroPlan);
  c.updateCube(p1,NumeroPlan);

  QVector3D v;
  v=QVector3D(abs(8-col),NumeroPlan,abs(8-lig));


  liste_vecteur3D.append(v);
  this->ui->widget->setListPoints(liste_vecteur3D);

  if(this->c.getList1()->value(NumeroPlan).getLed(lig,col).getEtat()==1){

        liste_vecteur3D.append(v);
        this->ui->widget->setListPoints(liste_vecteur3D);

  }
  else {
      liste_vecteur3D.removeAll(v);
      this->ui->widget->setListPoints(liste_vecteur3D);
  }

  afficheLed(lig,col,l.getEtat());

}


void MainWindow:: afficheLed(const int i, const int j,const  int etat )
{
       QString lig=QString::number(i);
       QString col=QString::number(j);
       QString text=lig+col;
       int num=text.toInt(0,10);

    if(etat==0){
        this->buttons[num]->setIcon(QIcon(":/icone/nvatomeblanc.png"));
      }
    else {
        this->buttons[num]->setIcon(QIcon(":/icone/atome.gif"));
    }

}

void MainWindow::connexion(){

    QSignalMapper *signalMapper = new QSignalMapper(this);

        connect(ui->plane1, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(ui->plane1, "00");
        connect(ui->plane2, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(ui->plane2, "01");
        connect(ui->plane3, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(ui->plane3, "02");
        connect(ui->plane4, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(ui->plane4, "03");
        connect(ui->plane5, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(ui->plane5, "04");
        connect(ui->plane6, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(ui->plane6, "05");
        connect(ui->plane7, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(ui->plane7, "06");
        connect(ui->plane8, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(ui->plane8, "07");
        connect(ui->plane9, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(ui->plane9, "08");

    connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(affichePlanLed(const QString &)));

    QSignalMapper *signalMapper1 = new QSignalMapper(this);
    for (int i = 0; i < 9; i++) {
         for (int j=0;j<9; j++){
            QString col=QString::number(i);
            QString lig=QString::number(j);
            QString text=lig+col;

            int num=text.toInt(0,10);
            connect(buttons[num], SIGNAL(clicked()), signalMapper1, SLOT(map()));
            signalMapper1->setMapping(buttons[num], text);
        }
    }
     connect(signalMapper1, SIGNAL(mapped(const QString &)), this, SLOT(controlLed(const QString &)));


}

int MainWindow::getOrientationPlan()
{
   return OrienPlan;
}

void MainWindow::setOrientationPlan(int i)
{
   OrienPlan=i;
}

int MainWindow::getNumeroPlan()
{
   return NumeroPlan;
}

void MainWindow::setNumeroPlan(int i)
{
   NumeroPlan=i;
}

void MainWindow::setEmpMotif(QString nom){
    this->emplMotif=nom;
}

QString MainWindow::getEmplMotif(){
    return this->emplMotif;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Monter();
}

void MainWindow::on_pushButton_2_clicked()
{
    Descendre();
}

void MainWindow::on_pushButton_3_clicked()
{
    ajouter_motif();
}

void MainWindow::on_pushButton_4_clicked()
{
    on_actionNew_Group_triggered();
}
