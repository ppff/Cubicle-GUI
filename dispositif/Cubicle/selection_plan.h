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

private:
    Ui::Selection_Plan *ui;
};

#endif // SELECTION_PLAN_H
