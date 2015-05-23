#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //ui->treeView->setContextMenuPolicy(Qt::ActionsContextMenu);


     connect(ui->actionOpen_directory,SIGNAL(triggered(bool)),this,SLOT(ouvrir_explorer()));
       insert_Group = new QAction("insert Group",this);
       connect(ui->actionNew_Group,SIGNAL(triggered(bool)),this,SLOT(insertGroup()));

}
void MainWindow::ouvrir_explorer(){
    namedir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                   "/home",
                                                   QFileDialog::ShowDirsOnly
                                                   | QFileDialog::DontResolveSymlinks
                                                    );
  tree();
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
    ui->treeView->resizeColumnToContents(0);


}
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

