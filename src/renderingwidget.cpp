#include "renderingwidget.h"

/**
 * @brief RenderingWidget::RenderingWidget
 * @param parent
 */
RenderingWidget::RenderingWidget(QWidget *parent):QGLWidget(parent)
{
    rTri = 0;                 // Revolution angle
    rQuad = 0;                // Rotate angle
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

/**
 * @brief RenderingWidget::initializeGL
 * basic settings for rendering environment
 */
void RenderingWidget::initializeGL(){

    // Load the texture of sun
    loadGLTextures( "/Users/gengyoung/LayoutDEMO/images/sun.jpg",1);
    mySphere = gluNewQuadric();


    glShadeModel(GL_SMOOTH);                                    // Enabel shade smooth
    glClearColor(0.0,0.0,0.0,0.0);                              // Set black background
    glClearDepth(1.0);                                          // Set depth buffer
    glEnable(GL_DEPTH_TEST);                                    // Enable depth test
    glEnable(GL_TEXTURE_2D);                                    // Enabel texture
    glDepthFunc(GL_LEQUAL);                                     // Type of depth test
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Perspective correction
    gluQuadricNormals(mySphere, GL_SMOOTH);
    gluQuadricTexture(mySphere, GL_TRUE);

}

/**
 * @brief RenderingWidget::paintGL
 */
void RenderingWidget::paintGL(){



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          // Clear screen and depth buffer
    glLoadIdentity();

    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    drawStar();
    gluLookAt(80,0,0,0,0,0,0,1,1);


    glTranslatef(0.0,0.0,-6.0);
    glRotatef(rTri,1.0,1.0,1.0);

    glColor3f(1,0.5,0.5);
    glutWireSphere(3,30,30);
    gluLookAt(0,0,-6.0, 10,0,0, 0,0,0);

    // Update the angles of revolution and rotation
    rTri += 0.2;
    rQuad -= 0.15;
}

/**
 * @brief RenderingWidget::resizeGL
 * @param width: the width of window
 * @param height: the height of window
 */
void RenderingWidget::resizeGL(int width, int height){
    height = height == 0 ? 1 : height;
    glViewport(0,0,static_cast<GLint>(width), static_cast<GLint>(height));      // Reset viewport
    glMatrixMode(GL_PROJECTION);                                                // Projection Mode
    glLoadIdentity();
    gluPerspective(45.0,static_cast<double>(width*1.0/height),0.1,100.0);
    glMatrixMode(GL_MODELVIEW);                                                 // Modelview Mode
    glLoadIdentity();
}

/**
 * @brief RenderingWidget::drawStar
 * a demo to draw the sun
 */
void RenderingWidget::drawStar(){
    glPushMatrix();
    GLfloat  sun_ambient[]={0.0,0.0,0.0,1.0};
    GLfloat  sun_diffuse[]={0.0,0.0,0.0,1.0};
    GLfloat  sun_specular[]={0.0,0.0,0.0,1.0};
    GLfloat  sun_shininess=20.0;
//    GLfloat  sun_radious=10.0;
//    GLfloat  sun_rotSpeed= (GLfloat)360/58/100;

    // Revolution
    glRotatef(rQuad,0.0,0.0,1.0);

    // Rotation
    glTranslatef(2, 0, -5);
    glRotatef(rTri,0.0,1.0,0.0);

    // Create sphere
    gluSphere(mySphere, 0.5, 30, 30);


    // Set material properties
    glMaterialfv(GL_BACK, GL_AMBIENT, sun_ambient);
    glMaterialfv(GL_BACK, GL_DIFFUSE, sun_diffuse);
    glMaterialfv(GL_BACK, GL_SPECULAR, sun_specular);
    glMaterialf(GL_BACK, GL_SHININESS, sun_shininess);

    glPopMatrix();
}

/**
 * @brief RenderingWidget::loadGLTextures
 * @param filename: filename of the texture image
 * @param id: texture id
 */
void RenderingWidget::loadGLTextures(QString filename, int id){
    QImage tex,buf;
    if (!buf.load(filename)){
        qWarning("Could not read image file!");
        QImage dummy( 128, 128,QImage::Format_RGB32 );
        dummy.fill( Qt::green );
        buf = dummy;
    }

    tex = QGLWidget::convertToGLFormat(buf);
    glGenTextures(1, &texture[id]);                     // Create texture

    glBindTexture(GL_TEXTURE_2D,texture[id]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

