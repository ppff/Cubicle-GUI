#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include <QWidget>

namespace Ui {
class sauvegarde;
}

class sauvegarde : public QWidget
{
    Q_OBJECT

public:
    explicit sauvegarde(QWidget *parent = 0);
    ~sauvegarde();

private:
    Ui::sauvegarde *ui;
};

#endif // SAUVEGARDE_H
