#include "testui.h"
#include "ui_testui.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

testUI::testUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::testUI)
{
    ui->setupUi(this);
}

testUI::~testUI()
{
    delete ui;
}

void testUI::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"testui-Save As", "/home/workspaceQt","Text Files (*.txt)::All Files(*.*)");
    if (!fileName.isEmpty()){
        saveFile();
    }else{
        return;
    }
}
