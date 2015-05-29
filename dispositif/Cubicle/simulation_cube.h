#ifndef Simulation_cube_H
#define Simulation_cube_H

#include <QWidget>
#include <QtOpenGL>
#include <QGLWidget>
#include "adapt.h"
#include<QTimer>
#include <QApplication>
#include <QObject>
#include <QMainWindow>
#include <QVector3D>
#include <QDebug>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <GL/glut.h>
#include <QtGui>
#include <qgl.h>
#include <QKeyEvent>

/* Description :
 * Simulation des 9*9*9 LEDs du cube.
 */
//10 eteinte et 200 allumée
#define TRANSPARENCE_SPHERE_ETEINTE 150
#define TRANSPARENCE_SPHERE_ALLUMEE 250


#define DETAIL_SPHERES 4
#define RAYON_SPHERES 0.15

class simulation_cube : public QGLWidget
{
    Q_OBJECT

    public:

        explicit simulation_cube(QWidget *parent = NULL);

        void initializeGL();
        void paintGL();
        void resizeGL (int width, int height);

        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);

        void calculer_coord_cam();
        QList<QVector3D> getListPoints();
        void setListPoints(QList<QVector3D> const& l);


    protected :

        QVector3D coordonnees_cubicle_vers_opengl(QVector3D const& v) const;


        void dessiner_axes();

        float fAxisRadius, fAxisHeight, fArrowRadius, fArrowHeight;


        void dessiner_sphere(const QColor &c, float const& rayon, float const& details, int i) const;
        float camX, camY, camZ, camR, camT, camP; //rho, theta, phi pour les coordonnées sphériques.
        float camUpX, camUpY, camUpZ;
        QTimer* fps;
        QPoint last_pos;
        QList<QVector3D> points;
        GLUquadric* sph;

    public slots :

        void recevoir_nouveaux_points(QList<QVector3D> const& p);

};

#endif // Simulation_cube_H
