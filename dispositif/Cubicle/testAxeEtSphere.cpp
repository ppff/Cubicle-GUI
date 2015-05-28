#include "testAxeEtSphere.h"

testAxeEtSphere::testAxeEtSphere(QWidget *parent) :
    QGLWidget(parent)
{
    camR = 15;
    camT = -180;
    camP = -90;
    calculer_coord_cam();

    fps = new QTimer(this);
    connect(fps, SIGNAL(timeout()), this, SLOT(updateGL()));
    fps->start(20);
}

void testAxeEtSphere::initializeGL(){
    // Measurements
    fAxisRadius = 0.025f;
    fAxisHeight = 1.0f;
    fArrowRadius = 0.06f;
    fArrowHeight = 0.1f;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
}

void testAxeEtSphere::paintGL(){
        // 清除屏幕和深度缓存
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(camX, camY, camZ,0.0, 0.0, 0.0, camUpX, camUpY, camUpZ);

        pObj = gluNewQuadric();
        gluQuadricDrawStyle(pObj, GLU_FILL);

        /*
        glPushMatrix();
        glTranslatef(0, 0, -7);
        glColor3f(1.0f, 0.0f, 0.0f);
        glRotatef(45.0f, 1.0f, 1.0f, 0.0f);
        gluSphere(pObj, 4, 50, 50);
        glPopMatrix();
        */

        gluQuadricDrawStyle(pObj, GLU_FILL);
        gluQuadricNormals(pObj, GLU_SMOOTH);
        gluQuadricOrientation(pObj, GLU_OUTSIDE);
        gluQuadricTexture(pObj, GLU_FALSE);

        ///////////////////////////////////////////////////////
        // Draw the blue X axis first, with arrowed head
        glColor3f(0.0f, 0.0f, 1.0f);
        glPushMatrix();
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
        glPushMatrix();
        glTranslatef(0.0f,0.0f,1.0f);
        gluCylinder(pObj, fArrowRadius, 0.0f, fArrowHeight, 10, 1);
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        gluDisk(pObj, fAxisRadius, fArrowRadius, 10, 1);
        glDisable(GL_DEPTH_TEST);
        glPushMatrix();
        renderText(0, 0, -1, "X");
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
        ///////////////////////////////////////////////////////
        // Draw the Red Z axis 2nd, with arrowed head
        glColor3f(1.0f, 0.0f, 0.0f);
        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 1.0f);
        gluCylinder(pObj, fArrowRadius, 0.0f, fArrowHeight, 10, 1);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        gluDisk(pObj, fAxisRadius, fArrowRadius, 10, 1);
        glDisable(GL_DEPTH_TEST);
        glPushMatrix();
        renderText(1, 0, 0, "Z");
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();

        ///////////////////////////////////////////////////////
        // Draw the Green Y axis 3rd, with arrowed head
        glColor3f(0.0f, 1.0f, 0.0f);
        glPushMatrix();
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 1.0f);
        gluCylinder(pObj, fArrowRadius, 0.0f, fArrowHeight, 10, 1);
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        gluDisk(pObj, fAxisRadius, fArrowRadius, 10, 1);
        glDisable(GL_DEPTH_TEST);
        glPushMatrix();
        renderText(0, 1, 0, "Y");
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();

        /////////////////////////////////////////////////////////
        // Delete the quadric
        gluDeleteQuadric(pObj);


/*
        glBegin( GL_QUADS );
        glColor3f(1.0f,1.0f,0.0f);
        glVertex3f( -1.0,  1.0,  0.0 );
        glColor3f(1.0f,0.0f,1.0f);
        glVertex3f(  1.0,  1.0,  0.0 );
        glColor3f(1.0f,1.0f,1.0f);
        glVertex3f(  1.0, -1.0,  0.0 );
        glColor3f(0.6f,0.5f,0.5f);
        glVertex3f( -1.0, -1.0,  0.0 );
        glEnd();

        glLoadIdentity();
        glTranslatef(0.0f,0.0f,-5.0f);
        glRotatef( 180,  1.0,  0.0,  0.0 );
        glBegin(GL_TRIANGLES);							// 绘制三角形
        glColor3f (1.0, 0.0, 0.0);
        glVertex3f( 0.0f, 1.0f, 0.0f);					// 上顶点
        glColor3f (0.0, 1.0, 0.0);
        glVertex3f(-1.0f,-1.0f, 0.0f);					// 左下
        glColor3f (0.0, 0.0, 1.0);
        glVertex3f( 1.0f,-1.0f, 0.0f);					// 右下
        glEnd();

         //绘制圆形
        glLoadIdentity();
        glTranslatef(2.0f,0.0f,-5.0f);
        glRotatef( 45,  0.0,  1.0,  0.0 );
        GLint iCirclePoints = 500;
        glBegin (GL_TRIANGLE_FAN );

        for (int i = 0; i < 500; ++i ){
           double dAngle = 2 * 3.14f * i / iCirclePoints ;
           glColor3f (0.0/i, 1.0/i, 1.0/i);
           glVertex3f (cos (dAngle ), sin (dAngle ), 0.0);
        }
        glEnd ();

        glLoadIdentity();
        //移到屏幕的左半部分，并且将视图推入屏幕背后足够的距离以便我们可以看见全部的场景
        glTranslatef(-1.0f,0.0f,-6.0f);
        glRotatef(30,1.0,0,0);
        glBegin( GL_TRIANGLE_STRIP );
        glColor3f( 1.0, 0.0, 0.0 );
        glVertex3f(  0.0,  1.0,  0.0 );
        glColor3f( 0.0, 1.0, 0.0 );
        glVertex3f(-1.0, -1.0,  1.0 );
        glColor3f( 0.0, 0.0, 1.0 );
        glVertex3f(  1.0, -1.0,  1.0 );
        glColor3f( 0.0, 1.0, 0.0 );
        glVertex3f(  1.0, -1.0, -1.0 );
        glColor3f( 1.0, 0.0, 0.0 );
        glVertex3f(  0.0,  1.0,  0.0 );
        glColor3f( 0.0, 1.0, 0.0 );
        glVertex3f(-1.0, -1.0,  1.0 );
        glEnd();

        glLoadIdentity();

*/
}

void testAxeEtSphere::resizeGL(int w, int h){
    // 防止窗口大小变为0
  if ( h == 0 )
  {
      h = 1;
   }
   // 重置当前的视口
   glViewport( 0, 0, (GLint)w, (GLint)h );
   GLfloat aspect = (GLfloat)w/(GLfloat)h;
   // 选择投影矩阵
   glMatrixMode( GL_PROJECTION );
       // 重置投影矩阵
   glLoadIdentity();
   // 设置视口的大小
   gluPerspective( 35.0, aspect, 1, 70.0 );
   // 选择模型观察矩阵
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();
}

void testAxeEtSphere::calculer_coord_cam()
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

void testAxeEtSphere::mousePressEvent(QMouseEvent *event)
{
    last_pos = event->pos();
}

void testAxeEtSphere::mouseMoveEvent(QMouseEvent *event)
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
