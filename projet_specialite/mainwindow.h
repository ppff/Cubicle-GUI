#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"

#include "motif.h" //Pour avoir l'enum.

/* Description :
 * La simulation du panneau de controle du cube.
 */

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();


    private:

        Ui::MainWindow *ui;


    public slots:

        void translater_haut();
        void translater_bas();
        void translater_gauche();
        void translater_droite();
        void translater_devant();
        void translater_derriere();

        void modifier_groupe(QString const& numero, QString const& nom);
        void modifier_motif(QString const& numero, QString const& nom);


    signals:

        void translation(Translations sens);
        void groupe_suivant();
        void groupe_precedent();
        void motif_suivant();
        void motif_precedent();

};

#endif // MAINWINDOW_H
