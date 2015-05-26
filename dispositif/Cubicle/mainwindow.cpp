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

    this->setWindowState(Qt::WindowFullScreen);
    ui->actionCopy->setDisabled(true);
    ui->actionDelete_pattern->setDisabled(true);
    ui->actionNew_Group->setDisabled(true);
    ui->actionNew_Pattern->setDisabled(true);
    ui->actionPaste_pattern->setDisabled(true);
    ui->actionSave->setDisabled(true);
    ui->actionCut_pattern->setDisabled(true);
    connect(ui->actionOpen_directory,SIGNAL(triggered(bool)),this,SLOT(ouvrir_explorer()));
    connect(ui->actionCopy,SIGNAL(triggered(bool)),this,SLOT(copier()));
    connect(ui->actionPaste_pattern,SIGNAL(triggered(bool)),this,SLOT(coller()));
    connect(ui->actionNew_Group,SIGNAL(triggered(bool)),this,SLOT(insertGroup()));
    connect(ui->actionNew_Pattern,SIGNAL(triggered(bool)),this,SLOT(ajouter_motif()));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(controlQuit()));
    connect(ui->actionDelete_pattern,SIGNAL(triggered(bool)),this,SLOT(controlDelete()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(controlSave()));
    connect(ui->treeView,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(doubleClick()));
    connect(ui->actionCut_pattern,SIGNAL(triggered(bool)),this,SLOT(couper()));
    l=ui->label;
    l2=ui->label_2;
    l3=ui->label_3;
    l4=ui->label_4;
    this->setWindowTitle("Cubicle");
    deleteCube3D(0);
    deletePlanLed(0);
    desactivePlan(0);
    connexion();
    dirOpen=false;



}

//ouvre le répertoire de travail
void MainWindow::ouvrir_explorer(){
    namedir=QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                   "/home"
                                               );
  if (namedir=="") {qDebug()<<namedir;
      return;}

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
  dirOpen=true;
}
void MainWindow::contextMenuEvent(QContextMenuEvent *event){
    if(dirOpen){
        contextMenu = new QMenu(ui->treeView);
        QModelIndex index=ui->treeView->currentIndex();
        if (model->fileInfo(index).isDir()) {
             QString s =model->fileInfo(index).absoluteFilePath();
             if(index.isValid()){
                  ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
                  QAction * insertGroup;
                  insertGroup = contextMenu->addAction("new group");
                  connect(insertGroup,SIGNAL(triggered(bool)),this, SLOT(insertGroup()));
                  QString dir=model->fileInfo(index).absolutePath();
                  QString nameGroup=model->fileInfo(index).baseName();
                  if((dir+'/'+nameGroup)!=namedir){
                          insertMotif = contextMenu->addAction("new pattern");
                          connect(insertMotif,SIGNAL(triggered(bool)),this, SLOT(ajouter_motif()));
                          QAction * paste;
                          paste = contextMenu->addAction("paste pattern");
                          connect(paste,SIGNAL(triggered(bool)),this, SLOT(coller()));
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
                        tree();
                    }
                    if (!valid){
                       qDebug()<<"coller impossible";
                   }
                    tree();
                }
          }
        }
    }
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
    for(int i=1;i<4;i++){
        ui->treeView->hideColumn(i);
    }
    ui->treeView->resizeColumnToContents(0);
  //  ui->treeView->setSizePolicy(expanding);
    ui->actionNew_Group->setEnabled(true);
    ui->actionNew_Pattern->setEnabled(true);
    ui->actionDelete_pattern->setEnabled(true);
    ui->actionCopy->setDisabled(false);
    ui->actionPaste_pattern->setDisabled(false);
    ui->actionCut_pattern->setDisabled(false);
    ui->actionSave->setDisabled(false);

}

//creer un nouveau motif
void MainWindow::ajouter_motif(){
    QModelIndex index=ui->treeView->currentIndex();
    if (index.isValid()){

        if (model->fileInfo(index).isDir()) {
            QString dir=model->fileInfo(index).absolutePath();

            QString nameGroup=model->fileInfo(index).baseName();
             if((dir + "/" + nameGroup) !=namedir){
            qDebug()<<"le namedir est "+ namedir;
            qDebug()<<"l'emplacement du dossier est "+dir;
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

//creer un nouveau groupe de motif
void MainWindow::insertGroup(){

    QModelIndex index =model->index(namedir,0);
    if (!index.isValid()) return;
    QString name =QInputDialog::getText(this,"Name","Enter a name");
    if(name.isEmpty())return;
    model->mkdir(index,name);


}

void MainWindow::controlQuit(){
    int reponse = QMessageBox::question(this, "Quit", " Are you sure you want to quit ?");

        if (reponse == QMessageBox::Yes)
        {
            this->close();
        }
}

void MainWindow::controlDelete(){
    QModelIndex index=ui->treeView->currentIndex();
    if (model->fileInfo(index).isFile()) {
        dirOrFile=false;

         QString name=model->fileInfo(index).absoluteFilePath();
         QFile file(name);
         qDebug()<< "are you sure delete pattern";
         int reponse = QMessageBox::question(this, "Quit", " Are you sure you want to delete this pattern ?");
           if (reponse == QMessageBox::Yes) {
               file.remove();
               tree();
               this->deleteCube3D(1);
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
}

void MainWindow::setEmpMotif(QString nom){
    this->emplMotif=nom;
}

QString MainWindow::getEmplMotif(){
    return this->emplMotif;
}

void MainWindow::doubleClick(){
    QModelIndex index=ui->treeView->currentIndex();
    if (model->fileInfo(index).isFile()) {
        dirOrFile=false;

         QString name=model->fileInfo(index).absoluteFilePath();
         if(name.compare(this->getEmplMotif())!=0){
             qDebug() <<"ancien motif "+ this->getEmplMotif();
             this->setEmpMotif(name);
             qDebug ()<< "nv motif "+this->getEmplMotif();
             this->c=Cube();
             deletePlanLed(1);
             desactivePlan(1);
             deleteCube3D(1);
             afficheCube3D(l,l2);
         }
    }
    else {
        dirOrFile=true;
    }
}

void MainWindow:: afficheCube3D( QLabel* label,QLabel* l){
    label->setPixmap(QPixmap(":/icone/nvcube.jpeg"));
    label->move(860,350);
    label->adjustSize();
    label->show();
    l->setPixmap(QPixmap(":/icone/reperenv.jpeg"));
    l->move(820,500);
    l->adjustSize();
    l->show();
    this->fleche_bas->setVisible(true);
    fleche_bas->setIcon(QIcon(":/icone/bas.png"));
    fleche_bas->setGeometry(1025,415,40,40);
  //  fleche_gauche->setVisible(true);
    fleche_gauche->setIcon(QIcon(":/icone/GAUCHE.png"));
    fleche_gauche->setGeometry(1085,550,40,40);
 //   fleche_face->setVisible(true);
    fleche_face->setIcon(QIcon(":/icone/AR.png"));
    fleche_face->setGeometry(1000,550,40,40);
}

void MainWindow::deleteCube3D(int i){
    if(i==0){
        this->fleche_bas=new QPushButton("",this);
        this->fleche_gauche=new QPushButton("",this);
        this->fleche_face=new QPushButton("",this);
    }
    else{
        ui->label->setPixmap(QPixmap());
        ui->label->repaint();
        ui->label_2->setPixmap(QPixmap());
        ui->label_2->repaint();
        ui->label_3->setPixmap(QPixmap());
        ui->label_3->repaint();
        ui->label_4->setPixmap(QPixmap());
        ui->label_4->repaint();
    }
    this->fleche_bas->hide();
    this->fleche_gauche->hide();
    this->fleche_face->hide();

}

void MainWindow::afficheListePlan1(){
    desactivePlan(1);
    deletePlanLed(1);
 //   QSignalMapper *signalMapper = new QSignalMapper(this);
         for (int j=0;j<9; j++){ //les plans vue de dessus
           setOrientationPlan(0);
           QString ori=QString::number(0);
           QString nplan=QString::number(j);
           QString text=ori+nplan;
           int num=text.toInt(false,10);
           plans[num]->setVisible(true);
       //   connect(plans[num], SIGNAL(clicked()), signalMapper, SLOT(map()));
         // signalMapper->setMapping(plans[num], text);
        }
  //  connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(affichePlanLed(const QString &)));

}


void MainWindow::afficheListePlan2(){
     desactivePlan(1);
     deletePlanLed(1);
 QSignalMapper *signalMapper = new QSignalMapper(this);
 for (int j=0;j<9; j++){ //les plans vue de gauche
    setOrientationPlan(1);
    QString ori=QString::number(1);
    QString nplan=QString::number(j);
    QString text=ori+nplan;

    int num=text.toInt(false,10);
    plans[num]->setVisible(true);

   connect(plans[num], SIGNAL(clicked()), signalMapper, SLOT(map()));
   signalMapper->setMapping(plans[num], text);

    }
   connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(affichePlanLed(const QString &)));

}

void MainWindow::afficheListePlan3(){
     desactivePlan(1);
     deletePlanLed(1);
    QSignalMapper *signalMapper = new QSignalMapper(this);
    for (int j=0;j<9; j++){ //les plans vue de face
       setOrientationPlan(2);
       QString ori=QString::number(2);
       QString nplan=QString::number(j);
       QString text=ori+nplan;

       int num=text.toInt(false,10);
       plans[num]->setVisible(true);

       connect(plans[num], SIGNAL(clicked()), signalMapper, SLOT(map()));
      signalMapper->setMapping(plans[num], text);
   }
      connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(affichePlanLed(const QString &)));

}

void MainWindow::desactivePlan(int niemefois){

        for (int j=0;j<9; j++){
           QString ori=QString::number(0);
           QString nplan=QString::number(j);
           QString text=ori+nplan;
           int num=text.toInt(false,10);
           if(niemefois==0){  //il crée le bouton une seule fois fois
            plans[num]=new QPushButton("",this);
            plans[num]->setGeometry(100, 50, 250, 100);
            plans[num]->move(700-20*j, 50*j+90);
            plans[num]->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
           }
           plans[num]->hide();
        }

        for (int j=0;j<9; j++){
           QString ori=QString::number(1);
           QString nplan=QString::number(j);
           QString text=ori+nplan;
           int num=text.toInt(false,10);
           if(niemefois==0){
             plans[num]=new QPushButton("",this);
             plans[num]->setGeometry(100, 50, 250, 100);
             plans[num]->move(700-20*j, 50*j+90);
             plans[num]->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
           }
           plans[num]->hide();
        }
        for (int j=0;j<9; j++){
           QString ori=QString::number(2);
           QString nplan=QString::number(j);
           QString text=ori+nplan;
           int num=text.toInt(false,10);
           if(niemefois==0){
              plans[num]=new QPushButton("",this);
              plans[num]->setGeometry(100, 50, 250, 100);
              plans[num]->move(700-20*j, 50*j+90);
              plans[num]->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
           }
           plans[num]->hide();
          }
}


void MainWindow::affichePlanLed(const QString & valeur){
    for (int num=0;num<9;num++){
         plans[num]->setStyleSheet("QPushButton { background-color: rgba(240,240,240,255); }");
    }
    l3->setPixmap(QPixmap(":/icone/y.png"));
    l3->move(290,-1);
    l3->adjustSize();
    l3->show();
    l4->setPixmap(QPixmap(":/icone/x.png"));
    l4->move(280,5);
    l4->adjustSize();
    l4->show();
    QString stori=valeur[0];
    QString stnplan=valeur[1];
    int ori=stori.toInt(false,10);
    int nplan=stnplan.toInt(false,10);
    this->setNumeroPlan(nplan);
    plans[nplan]->setStyleSheet("QPushButton { background-color: red; }");
 //   QSignalMapper *signalMapper = new QSignalMapper(this);

   for (int i = 0; i < 9; i++) {
        for (int j=0;j<9; j++){
           QString col=QString::number(i);
           QString lig=QString::number(j);
           QString text=lig+col;

           int num=text.toInt(false,10);
           buttons[num]->setVisible(true);

           Led l;
           switch(this->OrienPlan){
                case 0: l=c.getList1()->value(this->NumeroPlan).getLed(j,i); break;
                case 1: l=c.getList2()->value(this->NumeroPlan).getLed(j,i); break;
                case 2: l=c.getList3()->value(this->NumeroPlan).getLed(j,i); break;
           }

           if(l.getEtat()==0){
               buttons[num]->setIcon(QIcon(":/icone/nvatomeblanc.png"));
           }
           else {
               buttons[num]->setIcon(QIcon(":/icone/atome.gif"));
           }

         // connect(buttons[num], SIGNAL(clicked()), signalMapper, SLOT(map()));
         // signalMapper->setMapping(buttons[num], text);

       }
    }
 //   connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(controlLed(const QString &)));
}

void MainWindow::deletePlanLed(int nfois){

        for (int i = 0; i < 9; i++) {
             for (int j=0;j<9; j++){
                 QString col=QString::number(i);
                 QString lig=QString::number(j);
                 QString text=lig+col;
                 int num=text.toInt(false,10);
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
   int lig=strlig.toInt(false,10);
   int col=strcol.toInt(false,10);
  Led l;
   switch (this->OrienPlan){
   case 0:   l= this->c.getList1()->value(NumeroPlan).getLed(lig,col); break;
   case 1:   l= this->c.getList2()->value(NumeroPlan).getLed(lig,col); break;
   case 2:   l= this->c.getList3()->value(NumeroPlan).getLed(lig,col); break;
   }

   l.modifierEtat();
   switch(OrienPlan){
        case 0:{
       Plan p1=c.getList1()->value(this->NumeroPlan);
       Plan p2=c.getList2()->value(col);
       Plan p3=c.getList3()->value(lig);
       p1.updatePlan(l,lig,col,NumeroPlan,OrienPlan,0);
       p2.updatePlan(l,lig,col,NumeroPlan,OrienPlan,1);
       p3.updatePlan(l,lig,col,NumeroPlan,OrienPlan,2);
       c.updateCube(p1,0,NumeroPlan);
       c.updateCube(p2,1,col);
       c.updateCube(p3,2,lig);
         }break;
        case 1:{
       Plan p1=c.getList1()->value(abs(8-lig));
       Plan p2=c.getList2()->value(NumeroPlan);
       Plan p3=c.getList3()->value(abs(8-col));
       p1.updatePlan(l,lig,col,NumeroPlan,OrienPlan,0);
       p2.updatePlan(l,lig,col,NumeroPlan,OrienPlan,1);
       p3.updatePlan(l,lig,col,NumeroPlan,OrienPlan,2);
       c.updateCube(p1,0,abs(8-lig));
       c.updateCube(p2,1,NumeroPlan);
       c.updateCube(p3,2,abs(8-col));
   } break;

        case 2:{
       Plan p1=c.getList1()->value(abs(8-lig));
       Plan p2=c.getList2()->value(col);
       Plan p3=c.getList3()->value(NumeroPlan);
       p1.updatePlan(l,lig,col,NumeroPlan,OrienPlan,0);
       p2.updatePlan(l,lig,col,NumeroPlan,OrienPlan,1);
       p3.updatePlan(l,lig,col,NumeroPlan,OrienPlan,2);
       c.updateCube(p1,0,abs(8-lig));
       c.updateCube(p2,1,col);
       c.updateCube(p3,2,NumeroPlan);
   } break;
   }
   afficheLed(lig,col,l.getEtat());

}
void MainWindow:: afficheLed(const int i, const int j,const  int etat )
{
       QString lig=QString::number(i);
       QString col=QString::number(j);
       QString text=lig+col;
       int num=text.toInt(false,10);

    if(etat==0){
        this->buttons[num]->setIcon(QIcon(":/icone/nvatomeblanc.png"));
      }
    else {
        this->buttons[num]->setIcon(QIcon(":/icone/atome.gif"));
    }

}

void MainWindow::connexion(){
    QObject::connect(fleche_bas, SIGNAL(clicked()), this, SLOT(afficheListePlan1()));
    QObject::connect(fleche_gauche, SIGNAL(clicked()),this, SLOT(afficheListePlan2()));
    QObject::connect(fleche_face, SIGNAL(clicked()),this, SLOT(afficheListePlan3()));

    QSignalMapper *signalMapper = new QSignalMapper(this);
    QString ori=QString::number(0);
    for (int i=0;i<9;i++){
        QString nplan=QString::number(i);
        QString text=ori+nplan;
        int num=text.toInt(false,10);
        connect(plans[num], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(plans[num], text);
    }
    connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(affichePlanLed(const QString &)));

    QSignalMapper *signalMapper1 = new QSignalMapper(this);
    for (int i = 0; i < 9; i++) {
         for (int j=0;j<9; j++){
            QString col=QString::number(i);
            QString lig=QString::number(j);
            QString text=lig+col;

            int num=text.toInt(false,10);
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



MainWindow::~MainWindow()
{
    delete ui;
}

/*MainWindow* MainWindow::getInstance()
{
    if(_instance == 0)
        _instance = new MainWindow();

    return _instance;
}

void MainWindow::kill()
{
    if(_instance != 0)
        delete _instance;
}*/

