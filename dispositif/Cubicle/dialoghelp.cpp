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
    this->setWindowTitle("Help ");
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("Tutorial of functions");
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setText("<body background=:/Images/cube.jpg >");
    QAction* group;
    group = new QAction("Groups",this);
    ui->treeWidget->addAction(group);
    connect(ui->treeWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(afficher_help()));
}

DialogHelp::~DialogHelp()
{
    delete ui;
}

void DialogHelp::AboutUS(){
    QMessageBox::information(this,"About CUBICLE","CUBICLE 1.0 \n Built on Mai 2015 \n Copyright 2015 CUBICLE. All rights reserved \n ");
}

void DialogHelp::afficher_help(){

    QList<QTreeWidgetItem *> itemList;
    itemList = ui->treeWidget->selectedItems();
    foreach(QTreeWidgetItem *item, itemList)
    {
       QString str = item->text(0);  
       if (str=="New project"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("A new project can be created by : \n");
           ui->textEdit->append("Method 1: a shortcut “Ctrl+N” \n");
           ui->textEdit->append("Method 2: Click on button: <img src=':/Images/new_project.png' width='20' height='20'>\n");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3: Select “New Project” from the menu “File” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>Make sure that current project has been saved before creating a new one.</FONT>");
           ui->textEdit->append(s);
           ui->textEdit->append("The location of button is: <img src=':/Images/1.png' width='200' height='100'>\n");
       }else if (str=="Open directory"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("Open an existing  project by : \n");
           ui->textEdit->append("Method 1: a shortcut “Ctrl+O” \n");
           ui->textEdit->append("Method 2: Click on button: <img src=':/Images/open_directory.png' width='20' height='20'>\n");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3: Select “Open Directory” from the menu “File” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>You have to choose a directory named “Cubicle”.</FONT>");
           ui->textEdit->append(s);
           ui->textEdit->append("The location of button is: <img src=':/Images/2.png' width='200' height='100'>\n");
       }else if (str=="New group"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("A new crystal group can be created by : \n");
           ui->textEdit->append("Method 1: a shortcut “Ctrl+G” \n");
           ui->textEdit->append("Method 2: Click on button: <img src=':/Images/new_group.png' width='20' height='20'>");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3: Select “New Group” from the menu “File” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>A new group can't be created before opening or creating a new project.</FONT>");
           ui->textEdit->append(s);
           ui->textEdit->append("The location of button is: <img src=':/Images/4.png' width='200' height='100'>\n");
       }else if(str=="New pattern"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("A new crystal pattern can be created by : \n");
           ui->textEdit->append("Method 1: a shortcut “Ctrl+P” \n");
           ui->textEdit->append("Method 2: Click on button: <img src=':/Images/new_pattern.gif' width='20' height='20'>");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3: Select “New Pattern” from the menu “File” \n");
           ui->textEdit->append("Method 4: Right click on a folder and select “New Pattern” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>Select a group before creating a new pattern.</FONT>");
           ui->textEdit->append(s);
           ui->textEdit->append("The location of button is: <img src=':/Images/5.png' width='200' height='100'>\n");
       }else if(str=="Save"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("Save the current project by: \n");
           ui->textEdit->append("Method 1: a shortcut “Ctrl+S” \n");
           ui->textEdit->append("Method 2: Click on button: <img src=':/Images/save.png' width='20' height='20'>");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3: Select “Save” from the menu “File” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>If the project hasn't been saved, you have to choose a place where to save it.</FONT>");
           ui->textEdit->append(s);
           ui->textEdit->append("The location of button is: <img src=':/Images/3.png' width='200' height='100'>\n");
       }else if(str=="Save as"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("Save the current project by: \n");
           ui->textEdit->append("Method 1: a shortcut “Ctrl+R” \n");
           ui->textEdit->append("Method 2: Select “Save As” from the menu “File” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>You are invited to choose a directory where to save your project.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Quit"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("Quit the current project by: \n");
           ui->textEdit->append("Method 1: a shortcut “Ctrl+Q” \n");
           ui->textEdit->append("Method 2: Select “Quit” from the menu “File” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>Make sure that the current project has been saved before quitting.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Copy pattern"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("Copy a crystal pattern by: \n");
           ui->textEdit->append("Method 1: a shortcut “Ctrl+C” \n");
           ui->textEdit->append("Method 2: Right click on a pattern and select “Copy pattern”\n");
           ui->textEdit->append("Method 3: Select “Copy pattern” from the menu “Edit” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>You have to choose a pattern to copy it.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Paste pattern"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("Paste a crystal pattern by: \n");
           ui->textEdit->append("Method 1: a shortcut “Ctrl+V” \n");
           ui->textEdit->append("Method 2: Right click on a group and select “Paste pattern”\n");
           ui->textEdit->append("Method 3: Select “Paste pattern” from the menu “Edit” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>You have to choose a group where you want to paste your pattern .</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Delete pattern"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("Delete a crystal pattern by: \n");
           ui->textEdit->append("Method 1: a shortcut “Ctrl+F” \n");
           ui->textEdit->append("Method 2: Right click on a pattern and select “Delete pattern”\n");
           ui->textEdit->append("Method 3: Select “Delete pattern” from the menu “Edit” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>You have to choose a pattern to delete it.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Cut pattern"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("Cut a crystal pattern by: \n");
           ui->textEdit->append("Method 1: a shortcut “Ctrl+X” \n");
           ui->textEdit->append("Method 2: Right click on a pattern and select “Cut pattern”\n");
           ui->textEdit->append("Method 3: Select “Cut pattern” from the menu “Edit” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>You have to choose a pattern to cut it.</FONT>");
           ui->textEdit->append(s);
       }else if(str=="Copy Plane"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("Select a plane to duplicate by: \n");
           ui->textEdit->append("Method 1: a right click on the plane and select “Copy Plane”\n");
       }else if(str=="Paste Plane"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("Select a plane to paste by: \n");
           ui->textEdit->append("Method 1: a right click on the plane and select “Paste Plane” \n");
           ui->textEdit->append("The location of botton is: <img src=':/Images/9.png' width='200' height='100'>\n");
       }else if(str=="Raise"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("Raise a group/pattern in the directory by: \n");
           ui->textEdit->append("Method 1: a shortcut “Ctrl+U” \n");
           ui->textEdit->append("Method 2: Click on button: <img src=':/Images/up.png' width='20' height='20'>");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3: Select “Raise” from the menu “Tools” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>A folder or a pattern need to be selected before raising, it can't be raised if it’s the first folder/file in the directory.</FONT>");
           ui->textEdit->append(s);
           ui->textEdit->append("The location of button is: <img src=':/Images/6.png' width='200' height='100'>\n");
       }else if(str=="Lower"){
           ui->textEdit->setText("<body background=:/Images/cube.jpg >");
           ui->textEdit->append("Lower a group/pattern in the directory by: \n");
           ui->textEdit->append("Method 1: a shortcut “Ctrl+D” \n");
           ui->textEdit->append("Method 2: Click on button: <img src=':/Images/down.png' width='20' height='20'>");
           ui->textEdit->append("");
           ui->textEdit->append("Method 3: Select “Lower” from the menu “Tools” \n");
           QString s("<FONT COLOR=red>Warning : </FONT> <FONT COLOR=blue>A folder or a pattern need to be selected before decreasing, it can't be decreased if it’s the last folder/file in the directory.</FONT>");
           ui->textEdit->append(s);
           ui->textEdit->append("The location of button is: <img src=':/Images/7.png' width='200' height='100'>\n");
       }
    }
}

