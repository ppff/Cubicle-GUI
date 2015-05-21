#ifndef CREATIONFICHIER_H
#define CREATIONFICHIER_H

#include <QDialog>

namespace Ui {
class CreationFichier;
}

class CreationFichier : public QDialog
{
    Q_OBJECT

public:
    explicit CreationFichier(QWidget *parent = 0);
    ~CreationFichier();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CreationFichier *ui;
};

#endif // CREATIONFICHIER_H
