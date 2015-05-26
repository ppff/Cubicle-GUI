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
    void modifierFichier(QString newLine);
    void ouvrir();
    void setEmpMotif(QString nom);
    QString getEmplMotif();
    void afficheCube3D(QLabel* l,QLabel*l2);
    void deleteCube3D(int i);
    void deletePlanLed(int i);
    void setOrientationPlan(int i);
    int getOrientationPlan();
    int getNumeroPlan();
    void setNumeroPlan(int i);
    void desactivePlan(int i);
    void connexion();
    void contextMenuEvent(QContextMenuEvent *event);

    ~MainWindow();

    /*static MainWindow* getInstance();
    static void kill();*/
     //static MainWindow* _instance;
     //Ui::MainWindow* getUi();

public:
    Ui::MainWindow *ui;

    QDirModel *model;
    QMenu* contextMenu;
    QString namedir;
    QAction *insertMotif;
    QAction *insert_Group;
    QAction *deletePattern;
    QString paste_element;
    QString nom_copie;
    bool dirOrFile;//false if file
    QString emplMotif;
    QLabel* l;
    QLabel * l2;
    QLabel* l3;
    QLabel* l4;
    QPushButton* buttons[90];
    int OrienPlan;
    int NumeroPlan;
    QPushButton* plans[30];
    QPushButton*  fleche_bas;
    QPushButton*  fleche_gauche;
    QPushButton*  fleche_face;
    Cube c;
    bool dirOpen;
    bool copierCouper; // vaut 0 pour copier et 1 pour couper


public slots:
void ouvrir_explorer() ;
void ajouter_motif() ;
void couper();
void copier();
void coller();
public slots:
void insertGroup();
void controlQuit();
void controlDelete();
void controlSave();
void doubleClick();
void afficheListePlan1();
void afficheListePlan2();
void afficheListePlan3();
void affichePlanLed(const QString & valeur);
void afficheLed(const int i, const int j, const int etat);
void controlLed(const QString & valeur);



};

//MainWindow* MainWindow::_instance=NULL;

#endif // MAINWINDOW_H
