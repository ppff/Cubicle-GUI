#ifndef QPUSHBUTTONPERS_H
#define QPUSHBUTTONPERS_H
#include <QPushButton>
#include "global.h"

class QPushButtonPers : public QPushButton
{
  //  Q_OBJECT
public:
    QPushButtonPers(QWidget *parent = 0);
    void setUi(Ui::MainWindow *ui);
    ~QPushButtonPers();


signals:
    void onPressRightClic(void);

protected:
    void mousePressEvent(QMouseEvent *event1);

private slots:
    void copierPlan();
    void collerPlan();

private :
    Ui::MainWindow *uiMainWindow;

};


#endif // QPUSHBUTTONPERS_H
