#ifndef DIALOGHELP_H
#define DIALOGHELP_H

#include <QDialog>
#include <QDirModel>

namespace Ui {
class DialogHelp;
}

class DialogHelp : public QDialog
{
    Q_OBJECT

public:
    explicit DialogHelp(QWidget *parent = 0);
    ~DialogHelp();

private:
    Ui::DialogHelp *ui;

public slots:
void afficher_help();
void AboutUS();
};

#endif // DIALOGHELP_H
