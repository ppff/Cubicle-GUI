#ifndef SAVETEMPORARY_H
#define SAVETEMPORARY_H

#include <QDialog>
#include <QString>
#include <QFile>
#include <QTextStream>

namespace Ui {
class SaveTemporary;
}

class SaveTemporary : public QDialog
{
    Q_OBJECT

public:
    explicit SaveTemporary(QWidget *parent = 0);
    ~SaveTemporary();
    QString getFileName();
    void setFileName(QString t);
    void creationFolder();
    void creationFichier();
    void prechargerTexte(QString str);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SaveTemporary *ui;
    QString Name;
};

#endif // SAVETEMPORARY_H
