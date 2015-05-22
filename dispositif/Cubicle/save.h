#ifndef SAVE_H
#define SAVE_H

#include <QDialog>
#include "cube.h"

namespace Ui {
class save;
}

class save : public QDialog
{
    Q_OBJECT

public:
    explicit save(QWidget *parent = 0);
    ~save();
    void ouvrir();
    void setName(QString nom);
    QString getName();
    void setEmpl(QString empl);
    QString getEmpl();
public slots:
    void controlSave();

private:
    Ui::save *ui;
    QString nom;
    QString empl;
    Cube c;

};

#endif // SAVE_H
