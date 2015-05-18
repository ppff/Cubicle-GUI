#ifndef Simulation_cube_H
#define Simulation_cube_H

#include "global.h"

/* Description :
 * Simulation des 9*9*9 LEDs du cube.
 */

#define TRANSPARENCE_SPHERE_ETEINTE 10
#define TRANSPARENCE_SPHERE_ALLUMEE 200

#define DETAIL_SPHERES 4
#define RAYON_SPHERES 0.15

class Simulation_cube : public QGLWidget
{
    Q_OBJECT

    public:

        explicit Simulation_cube(QWidget *parent = NULL);

        void initializeGL();
        void paintGL();
        void resizeGL (int width, int height);

        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);

        void calculer_coord_cam();


    private :

        QVector3D coordonnees_cubicle_vers_opengl(QVector3D const& v) const;
        void dessiner_axes() const;
        void dessiner_sphere(const QColor &c, float const& rayon, float const& details) const;

        float camX, camY, camZ, camR, camT, camP; //rho, theta, phi pour les coordonnées sphériques.
        float camUpX, camUpY, camUpZ;
        QTimer* fps;
        QPoint last_pos;
        QList<QVector3D> points;


    public slots :

        void recevoir_nouveaux_points(QList<QVector3D> const& p);

};

#endif // Simulation_cube_H
