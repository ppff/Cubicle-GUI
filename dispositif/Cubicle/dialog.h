#ifndef DIALOG_H
#define DIALOG_H
#include "cube.h"
#include <QDialog>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
public slots:
    void controlLed();
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();


private:
    Ui::Dialog *ui;
    Cube c;

};

#endif // DIALOG_H
