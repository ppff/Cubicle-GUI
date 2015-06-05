#include "dialoghelp.h"
#include "ui_dialoghelp.h"

DialogHelp::DialogHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHelp)
{
    ui->setupUi(this);
    //this->setWindowIcon();
    this->setWindowTitle("Help ");
    ui->treeWidget->setColumnCount(1);
        ui->treeWidget->setHeaderLabel("Groupes");
        ui->textEdit->setReadOnly(true);

        QAction* group;
        group = new QAction("Groups",this);
         ui->treeWidget->addAction(group);
         connect(ui->treeWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(afficher_help()));
}

DialogHelp::~DialogHelp()
{
    delete ui;
}

void DialogHelp::afficher_help(){

    QList<QTreeWidgetItem *> itemList;
    itemList = ui->treeWidget->selectedItems();
    foreach(QTreeWidgetItem *item, itemList)
    {
       QString str = item->text(0);
       if (str=="Groups")
  { ui->textEdit->setText("Groups represent ....\n  to add a group into the current directory" );}
       else if(str=="Patterns"){
           ui->textEdit->setText("Patterns represent ....\n  ");
       }
       else if(str=="new Patterns"){
           ui->textEdit->setText("to add a pattern go on File->new Pattern or ..\n  ");
       }
       else if (str=="display Patterns"){
             ui->textEdit->setText("to display the new Item selected double click on it ... \n ");
       }

       //str is what you want
    }

}
