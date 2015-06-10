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
        //passer en paramètre la position de event pour pouvoir afficher le menu au bon endroit
        emit onPressRightClic(event1->globalPos());
    }
    QPushButton::mousePressEvent(event1);

}


void QPushButtonPers::onPressRightClic(QPoint  p){

    QString nomBouton=this->text();
    setNamePlane(nomBouton);

    QMenu myMenu;

    myMenu.addAction(this->uiMainWindow->actionCopy_Plane);
    myMenu.addAction(this->uiMainWindow->actionPaste_Plane);

    myMenu.exec(p+QPoint(0,10));
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
