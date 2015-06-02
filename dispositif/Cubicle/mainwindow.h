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
#include "cube.h"
#include <QContextMenuEvent>
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
#include "simulation_cube.h"
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QAbstractItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void tree();
    void modifierFichier(QString newLine);
    void ouvrir();
    void setEmpMotif(QString nom);
    QString getEmplMotif();
    void deletePlanLed(int i);
    void setOrientationPlan(int i);
    int getOrientationPlan();
    int getNumeroPlan();
    void setNumeroPlan(int i);
    void desactivePlan(int i);
    void connexion();
    void contextMenuEvent(QContextMenuEvent *event);
    void xCopy2 (const QString &sourcePath, const QString &destPath, const QString &name);
    void removeDir(const QString& dirPath) ;


    ~MainWindow();

    /*static MainWindow* getInstance();
    static void kill();*/
     //static MainWindow* _instance;
     //Ui::MainWindow* getUi();

public:
    Ui::MainWindow *ui;

    QDirModel *model;
    QModelIndex new_index;
    QMenu* contextMenu;
    QString namedir="";
    QAction *insertMotif;
    QAction *insert_Group;
    QAction *deletePattern;
    QString paste_element;
    QString nom_copie;
    bool dirOrFile;//false if file
    QString emplMotif;
    QString currentPattern;
    QPushButton* buttons[90];
    int OrienPlan;
    int NumeroPlan;
    QPushButton* plans[30];
    Cube c;
    bool saved=true ;
    int dirOpen;  //vaut 0 si y a pas de directory ouvert, 1 si openDirectory et 2 si on ne choisit pas d'emplacement au début=>  saveAs
    bool copierCouper; // vaut 0 pour copier et 1 pour couper
    QList<QVector3D> liste_vecteur3D;
    QString s=QCoreApplication::applicationDirPath();



public slots:

void new_project();
void ouvrir_explorer() ;
void ajouter_motif() ;
void couper();
void copier();
void coller();
 void reordonneGroup();
//void reordonneMotif();
    void Monter();
    void Descendre();
    void controlQuit();
    void controlDelete();
    void controlSave();
    void controlSaveAs();
    void doubleClick();
    void affichePlanLed(const QString & valeur);
    void afficheLed(const int i, const int j, const int etat);
    void controlLed(const QString & valeur);
     void closeEvent(QCloseEvent *event);


protected:
    QDir *aDir;

private slots:
void on_actionNew_Group_triggered();

void on_pushButton_clicked();
void on_pushButton_2_clicked();
void on_pushButton_3_clicked();
void on_pushButton_4_clicked();
};



#endif // MAINWINDOW_H
