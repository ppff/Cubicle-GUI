#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"
#include "controlplan2d.h"
#include "controlcube3d.h"
#include "qpushbuttonpers.h"
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
#include <QFile>
#include <QPainter>
#include <QPainterPath>
#include "simulation_cube.h"
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QAbstractItemModel>
#include "QTreeWidgetItem"
#include"QInputDialog"
#include "nouveaumotif.h"
#include "QMenu"
#include "QPoint"
#include "controlarborescence.h"
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
#include <dialoghelp.h>
#include "duppliquerplan.h"


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
    int getNumeroPlan();
    void setNumeroPlan(int i);
    void connexion();
    void connectPlanToAffiche();
    void connectPlanToDuplicate();
    void copy(const QString &sourcePath, const QString &destPath, const QString &name);
    bool removeDir(const QString& dirPath) ;
    void reordonneGroup(QString namegroup);
    void initUi();
    void initControleur();
    void connectAction();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;
    QModelIndex new_index;
    QMenu* contextMenu;
    QString saveDir;
    //QString namedir;
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
    bool saved=true ;
    int dirOpen;  //vaut 0 si y a pas de directory ouvert, 1 si openDirectory et 2 si on ne choisit pas d'emplacement au début (new project)=>  saveAs
    bool copierCouper; // vaut 0 pour copier et 1 pour couper
    QList<QVector3D> liste_vecteur3D;
    QList<int> listePlanADupliquer;
    bool enfonce;
    QDir *aDir;
    int numeroPlanADuppliquer;


    QPushButtonPers* plans[9];


    Cube cubeMotif;
    QString tmpDir;
    ControlPlan2D ctlPlan;
    ControlCube3D ctlCube;
    DuppliquerPlan dupPlan;
    ControlArborescence ctlArbr;





private slots:

    void new_project();
    void ouvrir_explorer() ;
    void ajouter_motif() ;
    void couper();
    void copier();
    void coller();
    void save();
    void reordonneRenommage();
    void descendre();
    void monter();
    void controlQuit();
    void controlDelete();
    void controlSave();
    void controlSaveAs();
    void doubleClick();
    void closeEvent(QCloseEvent *event);
    void helpwindow();
    void About();
    void allume_led(const QString & valeur);
    void affiche_plan_Cube(const QString &valeur);
    void selectPlanToDuplicate();
    void choixPlanADupliquer(const QString &valeur);
    void duplicate();
    void ShowContextMenu(const QPoint& p);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void ajouter_groupe();
    void rename();
    void copyPlane();
    void pastePlane();

};



#endif // MAINWINDOW_H
