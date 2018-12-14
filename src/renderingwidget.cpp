#include "renderingwidget.h"
#define PI 3.1415926

/**
 * @brief RenderingWidget::RenderingWidget
 * @param parent
 */
RenderingWidget::RenderingWidget(QWidget *parent):QGLWidget(parent)
{
    solarSystem = new SolarSystem();
//    objects_copy = solarSystem->getObjects();
    std::copy(solarSystem->getObjects().begin(), solarSystem->getObjects().end(), back_inserter(objects_copy));
    // Set the default currentObject to be Sun for showing motion data
    currentObject = solarSystem->getObjects()[0];
    is_adjust_view = false;
    is_fullscreen = false;
    is_highlighting = false;
    is_play = true;
    hAngle = 0.0;
    vAngle = 0.0;

    eye_distance = 30;
    for (double i : eye_goal)
        i = 0.0;
    eyeX = eyeY = 0.0;
    eyeZ = 1.0;
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(updatePosition()));
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
    loadGLTextures(":images/uranus.jpg",8);
    loadGLTextures(":images/neptune.jpg",9);
    loadGLTextures(":images/moon.jpg",10);
    loadGLTextures(":images/moon.jpg",11);

    skySphere = gluNewQuadric();
    gluQuadricNormals(skySphere, GL_SMOOTH);
    gluQuadricTexture(skySphere, GL_TRUE);

    glShadeModel(GL_SMOOTH);                                    // Enabel shade smooth
    glClearColor(0.0,0.0,0.0,0.0);                              // Set black background
    glClearDepth(1.0);                                          // Set depth buffer
    glEnable(GL_DEPTH_TEST);                                    // Enable depth test
    glEnable(GL_TEXTURE_2D);                                    // Enabel texture
    glDepthFunc(GL_LEQUAL);                                     // Type of depth test
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Perspective correction

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);

}

/**
 * @brief RenderingWidget::paintGL
 */
void RenderingWidget::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          // Clear screen and depth buffer
    glLoadIdentity();
    glColor4f(1,1,1,0.5);

    GLdouble eye_posX = eye_distance * eyeX;
    GLdouble eye_posY = eye_distance * eyeY;
    GLdouble eye_posZ = eye_distance * eyeZ;

    gluLookAt(eye_posX,eye_posY,eye_posZ,0,0,0,0,1,0);
    drawSky();

    int i = 1;
    for (auto it : solarSystem->getObjects()){
        if (it->visiblity()){
            glBindTexture(GL_TEXTURE_2D, texture[i]);
            it->draw();
        }
        i++;
    }
    glEnable(GL_DEPTH_TEST);
    rTri += 0.1;

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
 * @brief RenderingWidget::drawSky
 */
void RenderingWidget::drawSky(){
    glPushMatrix();
    GLfloat  sky_ambient[]={0.0,0.0,0.0,1.0};
    GLfloat  sky_diffuse[]={0.0,0.0,0.0,1.0};
    GLfloat  sky_specular[]={0.0,0.0,0.0,1.0};
    GLfloat  sky_shininess=20.0;
    GLfloat  sky_radious=70.0;

    // Rotation
    glTranslatef(0,0,10);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glRotatef(rTri,1.0,1.0,1.0);

    // Create sphere
    gluSphere(skySphere, sky_radious, 30, 30);
    gluQuadricOrientation(skySphere, GLU_INSIDE);


    // Set material properties
    glMaterialfv(GL_BACK, GL_AMBIENT, sky_ambient);
    glMaterialfv(GL_BACK, GL_DIFFUSE, sky_diffuse);
    glMaterialfv(GL_BACK, GL_SPECULAR, sky_specular);
    glMaterialf(GL_BACK, GL_SHININESS, sky_shininess);

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
        dummy.fill(Qt::green );
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
    eye_distance = eye_distance >=60 ? 60 : eye_distance;
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

    GLint viewport[4]; //var to hold the viewport info
    GLdouble modelview[16]; //var to hold the modelview info
    GLdouble projection[16]; //var to hold the projection matrix info
    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview); //get the modelview info
    glGetDoublev( GL_PROJECTION_MATRIX, projection); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport); //get the viewport info
    viewport[2] /= 2;
    viewport[3] /= 2;
    winX = lastPos.x();
    winY = (float)viewport[3] - lastPos.y();
    winZ = 0;

    //get the world coordinates from the screen coordinates
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
    worldX *= 10 * eye_distance;
    worldY *= 10 * eye_distance;

    int i = 0;
    for (auto it : solarSystem->getObjects()){
        GLfloat dist = it->getDistance();
        GLfloat theta = it->getAngleRevolution() / 180 * PI;
        GLfloat radius = it->getRadius();
        GLfloat x = dist * cos(theta);
        GLfloat y = dist * sin(theta);
        if (qPow(x-worldX,2) + qPow(y-worldY,2) <= radius * radius){
            currentObject = it;
            emit currentObjectChanged();
            break;
        }
        i++;
    }
}

/**
 * @brief RenderingWidget::mouseMoveEvent
 *        Adjusting the view
 * @param e
 */
void RenderingWidget::mouseMoveEvent(QMouseEvent *e){

    if (is_adjust_view){
        curPos = e->pos();
        float dH = atan((curPos.x() - lastPos.x()) / (5 * eye_distance));
        float dV = atan((curPos.y() - lastPos.y()) / (5 * eye_distance));

        hAngle -= dH;
        if (vAngle + dV > PI / 2)
            vAngle = PI / 2;
        else if (vAngle + dV < -PI / 2)
            vAngle = -PI / 2;
        else
            vAngle += dV;

        eyeX = cos(vAngle) * sin(hAngle);
        eyeY = sin(vAngle);
        eyeZ = cos(vAngle) * cos(hAngle);
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

void RenderingWidget::mouseDoubleClickEvent(QMouseEvent *e){
    is_fullscreen = !is_fullscreen;

    if (is_fullscreen){
        setWindowFlags(Qt::Widget);
        showFullScreen();
    }
    else
        this->showNormal();
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

void RenderingWidget::updatePosition(){
    for (auto it : solarSystem->getObjects()){
        it->update(1);
    }
}

/*
void RenderingWidget::outline(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0,1.0,1.0,0.2);
    glLoadIdentity();
    gluLookAt(0,0,10,0,0,0,0,1,0);
    glRotatef(rTri,0,0,1);
    glTranslatef(xTrans,yTrans,-10);
    glRotatef(rTri,1,1,1);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    gluSphere(shadow,2.2,30,30);
}
*/


