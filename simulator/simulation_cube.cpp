#include "simulation_cube.h"

Simulation_cube::Simulation_cube(QWidget *parent) : QGLWidget(parent)
{
    camR = 15;
    camT = -180;
    camP = -90;
    calculer_coord_cam();

    fps = new QTimer(this);
    connect(fps, SIGNAL(timeout()), this, SLOT(updateGL()));
    fps->start(20);
}

void Simulation_cube::initializeGL()
{
    //activate the depth buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
}

void Simulation_cube::resizeGL (int width, int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height );

    /* create viewing cone with near and far clipping planes */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum( -1.0, 1.0, -1.0, 1.0, 5.0, 30.0);

    glMatrixMode( GL_MODELVIEW );
}

void Simulation_cube::paintGL()
{
    //delete color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(camX, camY, camZ,
                  0.0, 0.0, 0.0,
                  camUpX, camUpY, camUpZ);

        dessiner_axes();

        //On affiche les LEDS
        for (int x=0 ; x<9 ; x++)
        {
            for (int y=0 ; y<9 ; y++)
            {
                for (int z=0 ; z<9 ; z++)
                {
                    glPushMatrix();
                    glTranslatef(x-4, y-4, z-4);
                    if (points.indexOf(QVector3D(x,y,z)) == -1) //Si le point n'est pas dans la liste de points à allumer
                    {
                        dessiner_sphere(QColor(255,255,255,TRANSPARENCE_SPHERE_ETEINTE), RAYON_SPHERES, DETAIL_SPHERES);
                    }
                    else
                    {
                        dessiner_sphere(QColor(255,255,255,TRANSPARENCE_SPHERE_ALLUMEE), RAYON_SPHERES, DETAIL_SPHERES);
                    }
                    glPopMatrix();
                }
            }
        }

    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0f, 1.0*width()/height(), 0.01f, 100.0f);
}

void Simulation_cube::mousePressEvent(QMouseEvent *event)
{
    last_pos = event->pos();
}

void Simulation_cube::mouseMoveEvent(QMouseEvent *event)
{
    const int dx = event->x() - last_pos.x();
    const int dy = event->y() - last_pos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        camT -= dx;
        camP += dy;
        calculer_coord_cam();
    }

    last_pos = event->pos();
}

void Simulation_cube::calculer_coord_cam()
{
    camY = camR*qCos(qDegreesToRadians(camP));
    camZ = camR*qSin(qDegreesToRadians(camP))*qCos(qDegreesToRadians(camT));
    camX = camR*qSin(qDegreesToRadians(camP))*qSin(qDegreesToRadians(camT));

    //qDebug() << camR << camT << camP << "|" << camX << camY << camZ;

    if (camX == 0 && camY >= 0 && camZ == 0)
    {
        camUpX = 1;
        camUpY = 0;
        camUpZ = 0;
    }
    else
    {
        camUpX = 0;
        camUpY = 1;
        camUpZ = 0;
    }
}

void Simulation_cube::recevoir_nouveaux_points(QList<QVector3D> const& p)
{
    points.clear();

    for (QVector3D v : p)
    {
        points.append(coordonnees_cubicle_vers_opengl(v));
    }
}

QVector3D Simulation_cube::coordonnees_cubicle_vers_opengl(QVector3D const& v) const
{
    /* Sur le cube :
     * x vers l'avant
     * y vers la droite
     * z vers le haut
     * (l'origine au fond en bas à gauche)
     * Avec OpenGl :
     * z vers l'avant
     * x vers la droite
     * y vers le haut
     *
     * Pour résumer, correspondances Cubicle <-> OpenGL :
     *  - x <-> z
     *  - y <-> x
     *  - z <-> y
     */

    return QVector3D(v.y(), v.z(), v.x());
}

void Simulation_cube::dessiner_axes() const
{
    //On prend le repère Cubicle
    glBegin(GL_LINES);
    //X en rouge
    glColor4f(0.0, 0.0, 1.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(3.0, 0.0, 0.0);
    //Y en vert
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 3.0, 0.0);
    //Z en bleu
    glColor4f(0.0, 1.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 3.0);
    glEnd();
}

void Simulation_cube::dessiner_sphere(QColor const& c, float const& rayon, float const& details) const
{
    GLUquadric* sph;
    glColor4f(c.red()/255.0,c.green()/255.0,c.blue()/255.0,c.alpha()/255.0);
    gluQuadricDrawStyle(sph, GLU_FILL); //Merci GLU
    gluSphere(sph, rayon, details, details);
}
