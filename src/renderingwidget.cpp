#include "renderingwidget.h"
#define PI 3.1415926

/**
 * @brief RenderingWidget::RenderingWidget
 * @param parent
 */
RenderingWidget::RenderingWidget(QWidget *parent):QGLWidget(parent)
{
    solarSystem = new SolarSystem();
    // Set the default currentObject to be Sun for showing motion data
    currentObject = solarSystem->getObjects()[0];
    is_adjust_view = false;
    hAngle = 0.0;
    vAngle = 0.0;

    eye_distance = 80;
    for (double i : eye_goal)
        i = 0.0;
    eyeX = eyeY = 0.0;
    eyeZ = 1.0;
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);

    rTri = 0;                 // Revolution angle
    rQuad = 0;                // Rotate angle
}

RenderingWidget::~RenderingWidget(){
    delete solarSystem;
}

/**
 * @brief RenderingWidget::initializeGL
 * basic settings for rendering environment
 */
void RenderingWidget::initializeGL(){

    // Load the texture of sun
    loadGLTextures(":images/stars.jpg",0);
    loadGLTextures(":images/sun.jpg",1);
    loadGLTextures(":images/mercury.jpg",2);
    loadGLTextures(":images/venus_surface.jpg",3);
    loadGLTextures(":images/earth_daymap.jpg",4);
    loadGLTextures(":images/mars.jpg",5);
    loadGLTextures(":images/jupiter.jpg",6);
    loadGLTextures(":images/saturn.jpg",7);
    loadGLTextures(":images/neptune.jpg",8);

    mySphere = gluNewQuadric();
    gluQuadricNormals(mySphere, GL_SMOOTH);
    gluQuadricTexture(mySphere, GL_TRUE);

    glShadeModel(GL_SMOOTH);                                    // Enabel shade smooth
    glClearColor(0.0,0.0,0.0,0.0);                              // Set black background
    glClearDepth(1.0);                                          // Set depth buffer
    glEnable(GL_DEPTH_TEST);                                    // Enable depth test
    glEnable(GL_TEXTURE_2D);                                    // Enabel texture
    glDepthFunc(GL_LEQUAL);                                     // Type of depth test
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Perspective correction

    GLfloat lightAmbient[4] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat lightDiffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lightPosition[4] = { 20, 0.0, 0.0, 1.0 };
    glLightfv( GL_LIGHT1, GL_AMBIENT, lightAmbient );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, lightDiffuse );
    glLightfv( GL_LIGHT1, GL_POSITION, lightPosition );

    glEnable(GL_LIGHTING);
    glEnable( GL_LIGHT1 );

}

/**
 * @brief RenderingWidget::paintGL
 */
void RenderingWidget::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          // Clear screen and depth buffer
    glLoadIdentity();
    glColor3f(1,1,1);

    GLdouble eye_posX = eye_distance * eyeX;
    GLdouble eye_posY = eye_distance * eyeY;
    GLdouble eye_posZ = eye_distance * eyeZ;

    int i = 1;
//    gluPerspective(75.0f, 1.0f, 1.0f, 40000000);
    gluLookAt(eye_posX,eye_posY,eye_posZ,0,0,0,0,1,0);
    drawSky();
//    drawSky(0,0,0,150,150,150);

//    gluLookAt(0,0,80,0,0,0,0,1,0);
//    glBindTexture(GL_TEXTURE_2D, texture[0]);

//    drawStar();

    for (auto it : solarSystem->getObjects()){
        glBindTexture(GL_TEXTURE_2D, texture[i++]);
        it->draw();
        it->update(1);
    }

//    gluPerspective(75.0f, 1.0f, 1.0f, 40000000);
//    gluLookAt(0, -700, 700, 0, 0, 0, 0, 0, 1);


    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);


//    glBindTexture(GL_TEXTURE_2D, texture[1]);
//    drawStar();
//    gluLookAt(80,0,0,0,0,0,0,1,1);

//    glTranslatef(0.0,0.0,-6.0);
//    glRotatef(rTri,1.0,1.0,1.0);

//    glColor3f(1,0.5,0.5);
//    glutWireSphere(3,30,30);
//    gluLookAt(0,0,-6.0, 10,0,0, 0,0,0);

    // Update the angles of revolution and rotation
    rTri += 0.2;
//    rQuad -= 0.15;
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
    GLfloat  sun_radious=10.0;
//    GLfloat  sun_rotSpeed= (GLfloat)360/58/100;

    // Revolution
    glRotatef(rQuad,0.0,0.0,1.0);

    // Rotation
    glTranslatef(20, 0, -5);
    glRotatef(rTri,0.0,1.0,0.0);

    // Create sphere
    gluSphere(mySphere, sun_radious, 30, 30);

    // Set material properties
    glMaterialfv(GL_BACK, GL_AMBIENT, sun_ambient);
    glMaterialfv(GL_BACK, GL_DIFFUSE, sun_diffuse);
    glMaterialfv(GL_BACK, GL_SPECULAR, sun_specular);
    glMaterialf(GL_BACK, GL_SHININESS, sun_shininess);

    glPopMatrix();
}

void RenderingWidget::drawSky(){
    glPushMatrix();
    GLfloat  sky_ambient[]={0.0,0.0,0.0,1.0};
    GLfloat  sky_diffuse[]={0.0,0.0,0.0,1.0};
    GLfloat  sky_specular[]={0.0,0.0,0.0,1.0};
    GLfloat  sky_shininess=20.0;
    GLfloat  sky_radious=130.0;
//    GLfloat  sun_rotSpeed= (GLfloat)360/58/100;

    // Revolution
//    glRotatef(rQuad,0.0,0.0,1.0);

    // Rotation
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTranslatef(0, 0, -sky_radious-10);
    glRotatef(rTri,0.0,1.0,0.0);

    // Create sphere
    gluSphere(mySphere, sky_radious, 30, 30);


    // Set material properties
    glMaterialfv(GL_BACK, GL_AMBIENT, sky_ambient);
    glMaterialfv(GL_BACK, GL_DIFFUSE, sky_diffuse);
    glMaterialfv(GL_BACK, GL_SPECULAR, sky_specular);
    glMaterialf(GL_BACK, GL_SHININESS, sky_shininess);

    glPopMatrix();
}

/**
 * @brief RenderingWidget::drawSky
 * @param x: the center of sky in x-axis
 * @param y: the center of sky in y-axis
 * @param z: the center of sky in z-axis
 * @param width
 * @param height
 * @param len
 */
void RenderingWidget::drawSky(GLfloat x,GLfloat y,GLfloat z,GLfloat width,GLfloat height,GLfloat len)
{
    x=x-width/2;
    y=y-height/2;
    z=z-len/2;

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glRotated(rTri,1,1,1);
    //back face
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x+width, y, z);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x+width, y+height, z);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y+height, z);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, y, z);

    glEnd();

    //left face
    glBegin(GL_QUADS);
    glNormal3f(1.0,0.0,0.0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, y+height, z);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, y+height, z+len);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y, z+len);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, y, z);

    glEnd();

    //front face
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, y, z+len);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, y+height, z+len);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x+width, y+height, z+len);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x+width, y, z+len);

    glEnd();

    //right face
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x+width, y, z);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x+width, y, z+len);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x+width, y+height, z+len);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x+width, y+height, z);

    glEnd();

    //top face
    glBegin(GL_QUADS);
    glNormal3f(0.0,-1.0,0.0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x+width, y+height, z);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x+width, y+height, z+len);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y+height, z+len);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, y+height, z);

    glEnd();

    //bottom face
    glBegin(GL_QUADS);
    glNormal3f(0.0,1.0,0.0);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, y, z);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, y, z+len);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x+width, y, z+len);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x+width, y, z);

    glEnd();

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


/**
 * @brief RenderingWidget::wheelEvent
 *        Zoom In/Out
 * @param e
 */
void RenderingWidget::wheelEvent(QWheelEvent *e)
{
    eye_distance += e->delta() * 0.01;
    eye_distance = eye_distance < 0 ? 0 : eye_distance;

    updateGL();
}

/**
 * @brief RenderingWidget::mousePressEvent
 *        Record the position of mouse and begin adjusting the view
 * @param e
 */
void RenderingWidget::mousePressEvent(QMouseEvent *e){
    if (e->button() == Qt::LeftButton){
        is_adjust_view = true;
        lastPos = e->pos();
    }

    qDebug() << e->button() << "  " << e->globalPos() << "  " << e->pos();

}

/**
 * @brief RenderingWidget::mouseMoveEvent
 *        Adjusting the view
 * @param e
 */
void RenderingWidget::mouseMoveEvent(QMouseEvent *e){

    if (is_adjust_view){
        curPos = e->pos();
        float dH = atan((curPos.x() - lastPos.x()) / (10 * eye_distance));
        float dV = atan((curPos.y() - lastPos.y()) / (10 * eye_distance));

        hAngle -= dH;
        vAngle += dV;

        eyeX = cos(vAngle) * sin(hAngle);
        eyeY = sin(vAngle);
        eyeZ = cos(vAngle) * cos(hAngle);
        updateGL();
        lastPos = curPos;
    }
}

/**
 * @brief RenderingWidget::mouseReleaseEvent
 *        Stop adjusting the view
 * @param e
 */
void RenderingWidget::mouseReleaseEvent(QMouseEvent *e){
    is_adjust_view = false;
}

/**
 * @brief RenderingWidget::getSolarSystem
 * @return
 */
SolarSystem* RenderingWidget::getSolarSystem(){
    return solarSystem;
}

/**
 * @brief RenderingWidget::getCurrentObject
 * @return
 */
AstronmicalObject* RenderingWidget::getCurrentObject(){
    return currentObject;
}

