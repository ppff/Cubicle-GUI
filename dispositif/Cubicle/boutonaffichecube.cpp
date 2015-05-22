#include "boutonaffichecube.h"
#include "ui_boutonaffichecube.h"
#include <QLabel>
#include <QPixmap>

BoutonAfficheCube::BoutonAfficheCube(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BoutonAfficheCube)
{
    ui->setupUi(this);
    QPixmap pix("/home/su/Documents/CUBICLE_GUI/Cubicle-GUI/dispositif/Cubicle/cube.gif");
    ui -> Cube -> setPixmap(pix);

}

BoutonAfficheCube::~BoutonAfficheCube()
{
    delete ui;
}

