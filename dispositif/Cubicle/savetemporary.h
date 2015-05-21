#ifndef SAVETEMPORARY_H
#define SAVETEMPORARY_H

#include <QDialog>

namespace Ui {
class SaveTemporary;
}

class SaveTemporary : public QDialog
{
    Q_OBJECT

public:
    explicit SaveTemporary(QWidget *parent = 0);
    ~SaveTemporary();

private:
    Ui::SaveTemporary *ui;
};

#endif // SAVETEMPORARY_H
