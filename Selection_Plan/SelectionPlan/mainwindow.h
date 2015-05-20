#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int getOrientationPlan();
    int getNumeroPlan();
    void setOrientationPlan(QString t);
    void setNumeroPlan(QString t);
    void returnValue();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_released();

private:
    Ui::MainWindow *ui;
    QString OrientationPlan;
    QString NumeroPlan;
    int firstValeur;
    int secondValeur;
};

#endif // MAINWINDOW_H
