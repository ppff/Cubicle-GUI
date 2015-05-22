#ifndef BOUTONAFFICHECUBE_H
#define BOUTONAFFICHECUBE_H

#include <QDialog>

namespace Ui {
class BoutonAfficheCube;
}

class BoutonAfficheCube : public QDialog
{
    Q_OBJECT

public:
    explicit BoutonAfficheCube(QWidget *parent = 0);
    ~BoutonAfficheCube();

private slots:
    void on_pushButton_clicked();

    void on_toolButton_clicked();

private:
    Ui::BoutonAfficheCube *ui;
};

#endif // BOUTONAFFICHECUBE_H
