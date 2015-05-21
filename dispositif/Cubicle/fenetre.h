#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>

namespace Ui {
class Fenetre;
}

class Fenetre : public QMainWindow
{
    Q_OBJECT

public:
    explicit Fenetre(QWidget *parent = 0);
    ~Fenetre();



private:
    Ui::Fenetre *ui;

public slots:
    void ouvrir_explorer();


};

#endif // FENETRE_H
