#include "qpushbuttonpers.h"

QPushButtonPers::QPushButtonPers(QWidget *parent) :
    QPushButton(parent){

}


void QPushButtonPers::setUi(Ui::MainWindow *ui){
    this->uiMainWindow=ui;
}

void QPushButtonPers::mousePressEvent(QMouseEvent *event1)
{
    if(event1->button() == Qt::RightButton){
        event1->accept();
        emit onPressRightClic();
    }
    QPushButton::mousePressEvent(event1);

}


void QPushButtonPers::onPressRightClic(){
    qDebug("je rentre dans signal emit");
    QMenu myMenu;

    myMenu.addAction(this->uiMainWindow->actionCopy_Plane);
    myMenu.addAction(this->uiMainWindow->actionPaste_Plane);

  /*  QAction *copierPlan;
    copierPlan = myMenu.addAction("copier");
    connect(copierPlan, SIGNAL(triggered(bool)),this, SLOT(copierPlan()));
    QAction *collerPlan;
    collerPlan = myMenu.addAction("coller");
    connect(collerPlan, SIGNAL(triggered(bool)),this, SLOT(collerPlan()));*/

    myMenu.move(860,500);
    myMenu.exec();
   // myMenu.exec(uiMainWindow->plane1->pos()+QPoint(0,50));
}

void QPushButtonPers::copierPlan(){

}

void QPushButtonPers::collerPlan(){

}

QPushButtonPers::~QPushButtonPers()
{
    this->close();
}
