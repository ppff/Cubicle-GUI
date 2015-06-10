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
    void onPressRightClic(QPoint  p);

protected:
    void mousePressEvent(QMouseEvent *event1);


private :
    Ui::MainWindow *uiMainWindow;

};


#endif // QPUSHBUTTONPERS_H
