#ifndef SELECTION_PLAN_H
#define SELECTION_PLAN_H

#include <QDialog>

namespace Ui {
class Selection_Plan;
}

class Selection_Plan : public QDialog
{
    Q_OBJECT

public:
    explicit Selection_Plan(QWidget *parent = 0);
    ~Selection_Plan();
    int getOrientationPlan();
    int getNumeroPlan();
    void setOrientationPlan(QString t);
    void setNumeroPlan(QString t);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_released();

private:
    Ui::Selection_Plan *ui;
    QString OrientationPlan;
    QString NumeroPlan;
    int firstValeur;
    int secondValeur;
};

#endif // SELECTION_PLAN_H
