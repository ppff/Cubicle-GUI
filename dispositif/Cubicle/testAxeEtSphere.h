#ifndef testAxeEtSphere_H
#define testAxeEtSphere_H
#include <QtOpenGL>
#include <QGLWidget>
#include <QtGui>
#include <qgl.h>
#include <QKeyEvent>
#include <QApplication>
#include <QObject>
#include <QMainWindow>
#include <QVector3D>
#include <QDebug>
#include <QList>
#include <QFile>
#include <QTextStream>

class testAxeEtSphere : public QGLWidget
{
    Q_OBJECT
public:
    explicit testAxeEtSphere(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void calculer_coord_cam();

protected:
    GLUquadricObj *pObj;
    float fAxisRadius, fAxisHeight, fArrowRadius, fArrowHeight;
    float camX, camY, camZ, camR, camT, camP; //rho, theta, phi pour les coordonnées sphériques.
    float camUpX, camUpY, camUpZ;
    QTimer* fps;
    QPoint last_pos;
    QList<QVector3D> points;
    GLUquadric* sph;

public slots :

};

#endif // testAxeEtSphere_H
