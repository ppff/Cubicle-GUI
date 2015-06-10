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
    QString getNamePlane();
    void setNamePlane(QString name);
    ~QPushButtonPers();


signals:
    void onPressRightClic(QPoint  p);

protected:
    void mousePressEvent(QMouseEvent *event1);

private slots:
    void copierPlan();
    void collerPlan();

private :
    Ui::MainWindow *uiMainWindow;
    QString namePlane;

};


#endif // QPUSHBUTTONPERS_H
