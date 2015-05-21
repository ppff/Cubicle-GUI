#ifndef CREEFICHIER_H
#define CREEFICHIER_H

#include <QMainWindow>

namespace Ui {
class CreeFichier;
}

class CreeFichier : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreeFichier(QWidget *parent = 0);
    ~CreeFichier();

private:
    Ui::CreeFichier *ui;
};

#endif // CREEFICHIER_H
