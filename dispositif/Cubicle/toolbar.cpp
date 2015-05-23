#include "toolbar.h"
#include "ui_toolbar.h"
#include <QToolBar>
#include <QPixmap>
#include <QToolButton>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>

ToolBar::ToolBar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);
    QPixmap pix(":/icone/cube.gif");
    ui -> Cube -> setPixmap(pix);
    ui -> Plan1-> setVisible(false);
    ui -> Plan2-> setVisible(false);
    ui -> Plan3-> setVisible(false);
    ui -> Plan4-> setVisible(false);
    ui -> Plan5-> setVisible(false);
    ui -> Plan6-> setVisible(false);
    ui -> Plan7-> setVisible(false);
    ui -> Plan8-> setVisible(false);
    ui -> Plan9-> setVisible(false);
    ui -> Plan1_2-> setVisible(false);
    ui -> Plan2_2-> setVisible(false);
    ui -> Plan3_2-> setVisible(false);
    ui -> Plan4_2-> setVisible(false);
    ui -> Plan5_2-> setVisible(false);
    ui -> Plan6_2-> setVisible(false);
    ui -> Plan7_2-> setVisible(false);
    ui -> Plan8_2-> setVisible(false);
    ui -> Plan9_2-> setVisible(false);
    ui -> Plan1_3-> setVisible(false);
    ui -> Plan2_3-> setVisible(false);
    ui -> Plan3_3-> setVisible(false);
    ui -> Plan4_3-> setVisible(false);
    ui -> Plan5_3-> setVisible(false);
    ui -> Plan6_3-> setVisible(false);
    ui -> Plan7_3-> setVisible(false);
    ui -> Plan8_3-> setVisible(false);
    ui -> Plan9_3-> setVisible(false);
}

ToolBar::~ToolBar()
{
    delete ui;
}

int ToolBar::getOrientationPlan()
{
   return OrienPlan;
}

void ToolBar::setOrientationPlan(int i)
{
   OrienPlan=i;
}

int ToolBar::getNumeroPlan()
{
   return NumeroPlan;
}

void ToolBar::setNumeroPlan(int i)
{
   NumeroPlan=i;
}

void ToolBar::on_VerticalDA_clicked()
{
    setOrientationPlan(1);
    ui -> Plan1->setVisible(true);
    ui -> Plan2->setVisible(true);
    ui -> Plan3->setVisible(true);
    ui -> Plan4->setVisible(true);
    ui -> Plan5->setVisible(true);
    ui -> Plan6->setVisible(true);
    ui -> Plan7->setVisible(true);
    ui -> Plan8->setVisible(true);
    ui -> Plan9->setVisible(true);
    ui -> Plan1_2-> setVisible(false);
    ui -> Plan2_2-> setVisible(false);
    ui -> Plan3_2-> setVisible(false);
    ui -> Plan4_2-> setVisible(false);
    ui -> Plan5_2-> setVisible(false);
    ui -> Plan6_2-> setVisible(false);
    ui -> Plan7_2-> setVisible(false);
    ui -> Plan8_2-> setVisible(false);
    ui -> Plan9_2-> setVisible(false);
    ui -> Plan1_3-> setVisible(false);
    ui -> Plan2_3-> setVisible(false);
    ui -> Plan3_3-> setVisible(false);
    ui -> Plan4_3-> setVisible(false);
    ui -> Plan5_3-> setVisible(false);
    ui -> Plan6_3-> setVisible(false);
    ui -> Plan7_3-> setVisible(false);
    ui -> Plan8_3-> setVisible(false);
    ui -> Plan9_3-> setVisible(false);
}

void ToolBar::on_VerticalGD_clicked()
{
    setOrientationPlan(2);
    ui -> Plan1->setVisible(false);
    ui -> Plan2->setVisible(false);
    ui -> Plan3->setVisible(false);
    ui -> Plan4->setVisible(false);
    ui -> Plan5->setVisible(false);
    ui -> Plan6->setVisible(false);
    ui -> Plan7->setVisible(false);
    ui -> Plan8->setVisible(false);
    ui -> Plan9->setVisible(false);
    ui -> Plan1_2-> setVisible(true);
    ui -> Plan2_2-> setVisible(true);
    ui -> Plan3_2-> setVisible(true);
    ui -> Plan4_2-> setVisible(true);
    ui -> Plan5_2-> setVisible(true);
    ui -> Plan6_2-> setVisible(true);
    ui -> Plan7_2-> setVisible(true);
    ui -> Plan8_2-> setVisible(true);
    ui -> Plan9_2-> setVisible(true);
    ui -> Plan1_3-> setVisible(false);
    ui -> Plan2_3-> setVisible(false);
    ui -> Plan3_3-> setVisible(false);
    ui -> Plan4_3-> setVisible(false);
    ui -> Plan5_3-> setVisible(false);
    ui -> Plan6_3-> setVisible(false);
    ui -> Plan7_3-> setVisible(false);
    ui -> Plan8_3-> setVisible(false);
    ui -> Plan9_3-> setVisible(false);
}

void ToolBar::on_Horizontal_clicked()
{
    setOrientationPlan(3);
    ui -> Plan1->setVisible(false);
    ui -> Plan2->setVisible(false);
    ui -> Plan3->setVisible(false);
    ui -> Plan4->setVisible(false);
    ui -> Plan5->setVisible(false);
    ui -> Plan6->setVisible(false);
    ui -> Plan7->setVisible(false);
    ui -> Plan8->setVisible(false);
    ui -> Plan9->setVisible(false);
    ui -> Plan1_2-> setVisible(false);
    ui -> Plan2_2-> setVisible(false);
    ui -> Plan3_2-> setVisible(false);
    ui -> Plan4_2-> setVisible(false);
    ui -> Plan5_2-> setVisible(false);
    ui -> Plan6_2-> setVisible(false);
    ui -> Plan7_2-> setVisible(false);
    ui -> Plan8_2-> setVisible(false);
    ui -> Plan9_2-> setVisible(false);
    ui -> Plan1_3-> setVisible(true);
    ui -> Plan2_3-> setVisible(true);
    ui -> Plan3_3-> setVisible(true);
    ui -> Plan4_3-> setVisible(true);
    ui -> Plan5_3-> setVisible(true);
    ui -> Plan6_3-> setVisible(true);
    ui -> Plan7_3-> setVisible(true);
    ui -> Plan8_3-> setVisible(true);
    ui -> Plan9_3-> setVisible(true);
}
