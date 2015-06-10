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
        emit onPressRightClic(event1->globalPos());
    }
    QPushButton::mousePressEvent(event1);

}


void QPushButtonPers::onPressRightClic(QPoint  p){
    qDebug("je rentre dans signal emit");
   // QPushButtonPers *button = (QPushButtonPers *)(sender());
    QString n=this->text();
    setNamePlane(n);

    //QPushButton *button = (QPushButton *)sender();
   // QPushButton *button = qobject_cast<QPushButton *>( sender() );
    QMenu myMenu;

    myMenu.addAction(this->uiMainWindow->actionCopy_Plane);
    myMenu.addAction(this->uiMainWindow->actionPaste_Plane);

  /*  QAction *copierPlan;
    copierPlan = myMenu.addAction("copier");
    connect(copierPlan, SIGNAL(triggered(bool)),this, SLOT(copierPlan()));
    QAction *collerPlan;
    collerPlan = myMenu.addAction("coller");
    connect(collerPlan, SIGNAL(triggered(bool)),this, SLOT(collerPlan()));*/
    QString x=QString::number(p.x());
    QString y=QString::number(p.y());
    qDebug()<< "les coord de p "+x+" "+y;
  //  myMenu.move(860,500);
  //  myMenu.exec();
    myMenu.exec(p+QPoint(0,10));
   // myMenu.exec(uiMainWindow->plane1->pos()+QPoint(0,50));
}

void QPushButtonPers::copierPlan(){

}

void QPushButtonPers::collerPlan(){

}

void QPushButtonPers::setNamePlane(QString name){
    this->namePlane=name;
}

QString QPushButtonPers::getNamePlane(){
    return this->namePlane;
}

QPushButtonPers::~QPushButtonPers()
{
    this->close();
}
