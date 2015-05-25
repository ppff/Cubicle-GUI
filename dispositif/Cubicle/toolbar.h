#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QMainWindow>

namespace Ui {
class ToolBar;
}

class ToolBar : public QMainWindow
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = 0);
    ~ToolBar();
    void setOrientationPlan(int i);
    int getOrientationPlan();
    int getNumeroPlan();
    void setNumeroPlan(int i);

private slots:
    void on_VerticalDA_clicked();
    void on_VerticalGD_clicked();
    void on_Horizontal_clicked();

private:
    Ui::ToolBar *ui;
    int OrienPlan;
    int NumeroPlan;
};

#endif // TOOLBAR_H
