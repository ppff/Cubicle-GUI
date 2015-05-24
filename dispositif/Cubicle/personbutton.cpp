#include "personbutton.h"
#include<QPolygonF>
#include <QPainterPath>

PersonButton::PersonButton(QWidget* parent): QPushButton(parent)
{
}

    void PersonButton::paintEvent(QPaintEvent * event) {
        QPainter p(this);

        QPointF position(500,100);
        QPainterPath pPath(position);

        QRectF rect(QPointF(200, 200), QPointF(500, 800));

        pPath.lineTo(700,100);
        pPath.lineTo(650,150 );
        pPath.lineTo(450, 150);
        pPath.closeSubpath();

        QLinearGradient upLinearGrad(position+QPointF(-66, 60), position+QPointF(30, 112));
        QLinearGradient downLinearGrad(position+QPointF(-66, 60), position+QPointF(30, 112));

        QColor topColor(154, 0, 0, 255);
        QColor bottomColor(231, 39, 0, 255);
        downLinearGrad.setColorAt(0, topColor);
        downLinearGrad.setColorAt(1, bottomColor);
        upLinearGrad.setColorAt(1, topColor);
        upLinearGrad.setColorAt(0, bottomColor);

        p.setRenderHint(QPainter::Antialiasing, true);
        p.setPen(QPen(QBrush(Qt::black), (isDown()) ? 2 : 1));
        p.setBrush(QBrush((isDown()) ? downLinearGrad : upLinearGrad));
        p.drawPath(pPath);
        p.end();

    }




