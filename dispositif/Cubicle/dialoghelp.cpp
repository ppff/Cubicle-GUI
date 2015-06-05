#include "dialoghelp.h"
#include "ui_dialoghelp.h"
#include <QLineEdit>
#include <QMessageBox>
#include "QDebug"

DialogHelp::DialogHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHelp)
{
    ui->setupUi(this);
    //this->setWindowIcon();
    this->setWindowTitle("Help ");
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("Tutorial of functions");
    ui->textEdit->setReadOnly(true);

    QAction* group;
    group = new QAction("Groups",this);
    ui->treeWidget->addAction(group);
    connect(ui->treeWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(afficher_help()));

    QAction* About;
    About = new QAction("About CUBICLE",this);
    ui->treeWidget->addAction(About);
    connect(ui->treeWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(AboutUS()));
}

DialogHelp::~DialogHelp()
{
    delete ui;
}

void DialogHelp::AboutUS(){
    QMessageBox::information(this,"About CUBICLE","CUBICLE 1.0.0 \n");
}

void DialogHelp::afficher_help(){

    QList<QTreeWidgetItem *> itemList;
    itemList = ui->treeWidget->selectedItems();
    foreach(QTreeWidgetItem *item, itemList)
    {
       QString str = item->text(0);
       if (str=="New project"){
           ui->textEdit->setText("A new project can be created by : \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+N” \n");
           ui->textEdit->append("Method 2 : Click on botton: <img src=':/Images/new_project.png' width='20' height='20'>\n");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3 : Select “New Project” in the menu “File” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>Make sure that current project have been saved before creating a new one.</FONT>");
           ui->textEdit->append(s);
       }else if (str=="Open directory"){
           ui->textEdit->setText("Open a project by : \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+O” \n");
           ui->textEdit->append("Method 2 : Click on botton: <img src=':/Images/open_directory.png' width='20' height='20'>\n");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3 : Select “Open Directory” in the menu “File” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>The name of the directory must be “Cubicle”.</FONT>");
           ui->textEdit->append(s);
       }else if (str=="New group"){
           ui->textEdit->setText("A new crystal group can be created by : \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+G” \n");
           ui->textEdit->append("Method 2 : Click on botton: <img src=':/Images/new_group.png' width='20' height='20'>");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3 : Select “New Group” in the menu “File” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>A new group can't be created before open or create a directory.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="New pattern"){
           ui->textEdit->setText("A new crystal pattern can be created by : \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+P” \n");
           ui->textEdit->append("Method 2 : Click on botton: <img src=':/Images/new_pattern.gif' width='20' height='20'>");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3 : Select “New Pattern” in the menu “File” \n");
           ui->textEdit->append("Method 4 : Right click on a folder and select “New Pattern” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>Select a folder before creating pattern, otherwise it can't be created.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Save"){
           ui->textEdit->setText("Save the current project by: \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+S” \n");
           ui->textEdit->append("Method 2 : Click on botton: <img src=':/Images/save.png' width='20' height='20'>");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3 : Select “Save” in the menu “File” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>If project hasn't be saved, a folder need to be selected to save it. Otherwise, it can be saved directly.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Save as"){
           ui->textEdit->setText("Save the current project by: \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+R” \n");
           ui->textEdit->append("Method 2 : Select “Save As” in the menu “File” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>If project has been saved, another folder can be chosen to save it. If not, it is needed to be saved for the first time.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Quit"){
           ui->textEdit->setText("Quit the current project by: \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+Q” \n");
           ui->textEdit->append("Method 2 : Select “Quit” in the menu “File” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>Make sure that current project has been saved before quitting the program.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Copy pattern"){
           ui->textEdit->setText("Copy a crystal pattern by: \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+C” \n");
           ui->textEdit->append("Method 2 : Right click on a pattern and select “Copy pattern”\n");
           ui->textEdit->append("Method 3 : Select “copy pattern” in the menu “Edit” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>Select a pattern before using this funtion.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Paste pattern"){
           ui->textEdit->setText("Paste a crystal pattern by: \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+V” \n");
           ui->textEdit->append("Method 2 : Right click on a group and select “Paste pattern”\n");
           ui->textEdit->append("Method 3 : Select “paste pattern” in the menu “Edit” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>Select a folder before using this funtion.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Delete pattern"){
           ui->textEdit->setText("Delete a crystal pattern by: \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+F” \n");
           ui->textEdit->append("Method 2 : Right click on a pattern and select “Delete pattern”\n");
           ui->textEdit->append("Method 3 : Select “Delete pattern” in the menu “Edit” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>Select a pattern before using this function.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Cut pattern"){
           ui->textEdit->setText("Cut a crystal pattern by: \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+X” \n");
           ui->textEdit->append("Method 2 : Right click on a pattern and select “Cut pattern”\n");
           ui->textEdit->append("Method 3 : Select “Cut pattern” in the menu “Edit” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>Select a pattern before using this function.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Select"){
           ui->textEdit->setText("Select a part of plan to duplicate by: \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+A” \n");
           ui->textEdit->append("Method 2 : Click on botton: <img src=':/icone/Select.png' width='20' height='20'>");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3 : Select “Select” in the menu “Tools” \n");
           //ui->textEdit->append("");
       }else if(str=="Duplicate"){
           ui->textEdit->setText("Duplicate a part of plan by: \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+T” \n");
           ui->textEdit->append("Method 2 : Click on botton: <img src=':/icone/Dupliquer.gif' width='20' height='20'>");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3 : Select “Duplicate” in the menu “Tools” \n");
           //ui->textEdit->append("");
       }else if(str=="Raise"){
           ui->textEdit->setText("Raise a group/pattern in the directory by: \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+U” \n");
           ui->textEdit->append("Method 2 : Click on botton: <img src=':/Images/up.png' width='20' height='20'>");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3 : Select “Raise” in the menu “Tools” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>A folder or a pattern need to be selected before raising, it can't be raised if it’s the first folder/file in the directory.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Lower"){
           ui->textEdit->setText("Lower a group/pattern in the directory by: \n");
           ui->textEdit->append("Method 1 : By shortcut “Ctrl+D” \n");
           ui->textEdit->append("Method 2 : Click on botton: <img src=':/Images/down.png' width='20' height='20'>");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3 : Select “Lower” in the menu “Tools” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>A folder or a pattern need to be selected before decreasing, it can't be decreased if it’s the last folder/file in the directory.</FONT>");
           ui->textEdit->append(s);
       }
    }
}

