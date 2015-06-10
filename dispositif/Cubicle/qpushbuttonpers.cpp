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

// suite à un clic droit sur un bouton on crée un QMenu avec les actions copy et paste plane
void QPushButtonPers::onPressRightClic(QPoint  p){

    QString nomBouton=this->text();
    QString n=(QString)nomBouton[5];
    int numPlan=n.toInt(0,10);

    QMenu myMenu;

    switch(numPlan){
    case 1:     myMenu.addAction(this->uiMainWindow->actionCopy_Plane1);
                myMenu.addAction(this->uiMainWindow->actionPaste_Plane1);break;
    case 2:     myMenu.addAction(this->uiMainWindow->actionCopy_Plane2);
                myMenu.addAction(this->uiMainWindow->actionPaste_Plane2);break;
    case 3:     myMenu.addAction(this->uiMainWindow->actionCopy_Plane3);
                myMenu.addAction(this->uiMainWindow->actionPaste_Plane3);break;
    case 4:     myMenu.addAction(this->uiMainWindow->actionCopy_Plane4);
                myMenu.addAction(this->uiMainWindow->actionPaste_Plane4);break;
    case 5:     myMenu.addAction(this->uiMainWindow->actionCopy_Plane5);
                myMenu.addAction(this->uiMainWindow->actionPaste_Plane5);break;
    case 6:     myMenu.addAction(this->uiMainWindow->actionCopy_Plane6);
                myMenu.addAction(this->uiMainWindow->actionPaste_Plane6);break;
    case 7:     myMenu.addAction(this->uiMainWindow->actionCopy_Plane7);
                myMenu.addAction(this->uiMainWindow->actionPaste_Plane7);break;
    case 8:     myMenu.addAction(this->uiMainWindow->actionCopy_Plane8);
                myMenu.addAction(this->uiMainWindow->actionPaste_Plane8);break;
    case 9:     myMenu.addAction(this->uiMainWindow->actionCopy_Plane9);
                myMenu.addAction(this->uiMainWindow->actionPaste_Plane9);break;

    }

    myMenu.exec(p+QPoint(0,10));
}

QPushButtonPers::~QPushButtonPers()
{
    this->close();
}
