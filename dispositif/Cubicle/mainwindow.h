#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QDirModel>
#include <QFileDialog>
#include <QString>
#include <iostream>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void tree();
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    QDirModel *model;
     QString namedir;

public slots:
void ouvrir_explorer() ;


};

#endif // MAINWINDOW_H
