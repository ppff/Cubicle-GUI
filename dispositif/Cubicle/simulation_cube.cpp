#include "simulation_cube.h"

simulation_cube::simulation_cube(QWidget *parent) : QGLWidget(parent),
                                                    sph(gluNewQuadric())
{
    camR = 15;
    camT = -180;
    camP = -90;
    calculer_coord_cam();

    fps = new QTimer(this);
    connect(fps, SIGNAL(timeout()), this, SLOT(updateGL()));
    fps->start(20);
}

void simulation_cube::initializeGL()
{
        fAxisRadius = 0.025f;
        fAxisHeight = 4.0f;
        fArrowRadius = 0.06f;
        fArrowHeight = 1.0f;
    //changer la couleur du fond du cube 3D. l'enlever si on veut un fond noir
   qglClearColor(QColor(143,181,184,255));

    //activate the depth buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
}

void simulation_cube::resizeGL (int width, int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height );

    /* create viewing cone with near and far clipping planes */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum( -1.0, 1.0, -1.0, 1.0, 5.0, 30.0);

    glMatrixMode( GL_MODELVIEW );
}

void simulation_cube::paintGL()
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

        //On affiche les plans et leds selectionnes
        for (int x=0 ; x<9 ; x++)
        {
            for (int y=0 ; y<9 ; y++)
            {
                for (int z=0 ; z<9 ; z++)
                {
                    glPushMatrix();
                    glTranslatef(x-4, y-4, z-4);
                    if ((plan.indexOf(QVector3D(x,y,z)) == -1)&&(points.indexOf(QVector3D(x,y,z)) == -1)) //Si le point n'est pas dans la liste de points à allumer
                    {
                        dessiner_sphere(QColor(255,255,255,TRANSPARENCE_SPHERE_ETEINTE), RAYON_SPHERES, DETAIL_SPHERES);
                    }
                    else if (points.indexOf(QVector3D(x,y,z)) != -1)
                    {

                       dessiner_sphere(QColor(Qt::red), RAYON_SPHERES_plan, DETAIL_SPHERES);

                    }
                    else{
                        dessiner_sphere(QColor(247,239,102,255), RAYON_SPHERES_plan, DETAIL_SPHERES);

                    }
                    glPopMatrix();



                }
            }
        }

    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0f, 1.0*width()/height(), 0.01f, 100.0f);
}

void simulation_cube::mousePressEvent(QMouseEvent *event)
{
    last_pos = event->pos();
}

void simulation_cube::mouseMoveEvent(QMouseEvent *event)
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

void simulation_cube::calculer_coord_cam()
{
    camY = camR*qCos(qDegreesToRadians(camP));
    camZ = camR*qSin(qDegreesToRadians(camP))*qCos(qDegreesToRadians(camT));
    camX = camR*qSin(qDegreesToRadians(camP))*qSin(qDegreesToRadians(camT));

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


void simulation_cube::dessiner_axes()
{
    GLUquadricObj *pObj = gluNewQuadric();
    // Draw the blue Z axis first, with arrowed head
       glColor3f(0.0f, 0.0f, 1.0f);
       glPushMatrix();
       glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
       gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
       glTranslatef(0.0f, 0.0f, fAxisHeight);
       gluCylinder(pObj, fArrowRadius, 0.0f, fArrowHeight, 10, 1);
       glTranslatef(0.0f, 0.0f, fArrowHeight);
       glDisable(GL_DEPTH_TEST);
       renderText(0, 0, 0, "Z");
       glPopMatrix();
       glPopMatrix();
       ///////////////////////////////////////////////////////
       // Draw the Red X axis 2nd, with arrowed head
       glColor3f(1.0f, 0.0f, 0.0f);
       glPushMatrix();
       glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
       gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
       glTranslatef(0.0f, 0.0f, fAxisHeight);
       gluCylinder(pObj, fArrowRadius, 0.0f, fArrowHeight, 10, 1);
       glTranslatef(0.0f, 0.0f, fArrowHeight);
       glDisable(GL_DEPTH_TEST);
       renderText(0, 0, 0, "X");
       glPopMatrix();
       glPopMatrix();

       ///////////////////////////////////////////////////////
       // Draw the Green Y axis 3rd, with arrowed head
       glColor3f(0.0f, 1.0f, 0.0f);
       glPushMatrix();
       glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
       gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
       glTranslatef(0.0f, 0.0f, fAxisHeight);
       gluCylinder(pObj, fArrowRadius, 0.0f, fArrowHeight, 10, 1);
       glTranslatef(0.0f, 0.0f, fArrowHeight);
       glDisable(GL_DEPTH_TEST);
       renderText(0, 0, 0, "Y");
       glPopMatrix();
       glPopMatrix();

    // Delete the quadric
    gluDeleteQuadric(pObj);

}

void simulation_cube::dessiner_sphere(QColor const& c, float const& rayon, float const& details) const
{
    GLUquadric* sph =  gluNewQuadric();

    glColor4f(c.red()/255.0,c.green()/255.0,c.blue()/255.0,c.alpha()/255.0);
    gluQuadricDrawStyle(sph, GLU_FILL); //Merci GLU
    gluSphere(sph, rayon, details, details);
}

QList<QVector3D> simulation_cube::getListPoints(){
    return this->points;
}

void simulation_cube::setListPoints(QList<QVector3D> const& l){
    this->points.clear();

    for(QVector3D v: l){
        this->points.append(QVector3D(v.x(),v.y(),v.z()));

    }
}



QList<QVector3D> simulation_cube::getListPlan(){
    return this->plan;
}

void simulation_cube::setListPlan(QList<QVector3D> const& l){
    this->plan.clear();

    for(QVector3D v: l){
        this->plan.append(QVector3D(v.x(),v.y(),v.z()));

    }
}
