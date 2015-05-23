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
#include "QMenu"
#include "QPoint"
#include <QInputDialog>


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
    QMenu* contextMenu;
    QString namedir;
    QAction *insertMotif;
    QAction *insert_Group;
    QString paste_element;
    bool dirOrFile;//false if file

public slots:
void ouvrir_explorer() ;
void ajouter_motif() ;
void copier();
void coller();
public slots:
void insertGroup();



};

#endif // MAINWINDOW_H
