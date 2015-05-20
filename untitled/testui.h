#ifndef TESTUI_H
#define TESTUI_H

#include <QMainWindow>

namespace Ui {
class testUI;
}

class testUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit testUI(QWidget *parent = 0);
    ~testUI();

private slots:
    void on_actionSave_As_triggered();

private:
    Ui::testUI *ui;
    void saveFile();
};

#endif // TESTUI_H
