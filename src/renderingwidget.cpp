#include "renderingwidget.h"
#include <string>
#define PI 3.1415926
#define FREQ 100    // frequency of timer

/**
 * @brief RenderingWidget::RenderingWidget
 * @param parent
 */
RenderingWidget::RenderingWidget(QWidget *parent):QGLWidget(parent)
{
    solarSystem = new SolarSystem();

    // Make a copy of obejects in solarsystem
    for (auto it : solarSystem->getObjects()){
        AstronmicalObject cur = *it;
        objects_copy.push_back(cur);
    }
    // Set the default currentObject to be Sun for showing motion data
    currentObject = solarSystem->getObjects()[0];
    is_adjust_view = false;
    is_fullscreen = false;
    is_highlighting = false;
    is_matrix_set = false;
    is_draw_shadow =  false;
    is_play = true;
    timeSpeed = 1.0;
    hAngle = 0.0;
    vAngle = 0.0;

    eye_distance = 30;
    for (double i : eye_goal)
        i = 0.0;
    eyeX = eyeY = 0.0;
    eyeZ = 1.0;
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(updatePosition()));
    timer.start(1000/FREQ);

    rTri = 0;                 // Revolution angle
    rQuad = 0;                // Rotate angle
}

/**
 * @brief RenderingWidget::~RenderingWidget
 * destructor of RenderingWidget
 */
RenderingWidget::~RenderingWidget(){
    delete solarSystem;
}

/**
 * @brief RenderingWidget::initializeGL
 * basic settings for rendering environment
 */
void RenderingWidget::initializeGL(){

    // Load the textures of the objects
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

    // Initialize the sphere for sky
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

    // Enable lighting
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

    // Compute the position of camera
    GLdouble eye_posX = eye_distance * eyeX;
    GLdouble eye_posY = eye_distance * eyeY;
    GLdouble eye_posZ = eye_distance * eyeZ;

    // Set the position of camera
    gluLookAt(eye_posX,eye_posY,eye_posZ,0,0,0,0,1,0);

    // Dray the sky background
    drawSky();

    // Draw the objects with textures
    int i = 1;
    for (auto it : solarSystem->getObjects()){
        if (it->visiblity()){
            glBindTexture(GL_TEXTURE_2D, texture[i]);
            it->draw();
        }
        i++;
    }
    glEnable(GL_DEPTH_TEST);

    // Rotate the sky background
    rTri += 0.05;

    //enable draw shadow
    if (is_draw_shadow)
//        drawShadow(obj_r,obj_x,obj_y);
    glEnable(GL_DEPTH_TEST);

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
 * draw sky background
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
    gluSphere(skySphere, static_cast<double>(sky_radious), 30, 30);
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

    // Create texture
    glGenTextures(1, &texture[id]);
    glBindTexture(GL_TEXTURE_2D,texture[id]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}


/**
 * @brief RenderingWidget::wheelEvent
 * zoom in/out with mouse wheel
 * @param e
 */
void RenderingWidget::wheelEvent(QWheelEvent *e)
{
    // Change the position of camera based on mouse wheel
    eye_distance += e->delta() * 0.01;
    eye_distance = eye_distance < 0 ? 0 : eye_distance;
    eye_distance = eye_distance >=60 ? 60 : eye_distance;
}

/**
 * @brief RenderingWidget::mousePressEvent
 * record the position of mouse and begin adjusting the view
 * @param e
 */
void RenderingWidget::mousePressEvent(QMouseEvent *e){
    if (e->button() == Qt::LeftButton){
        is_adjust_view = true;
        lastPos = e->pos();
    }

    // mouse position in screen coordinates
    GLfloat winX, winY, winZ;
    // mouse position in world coordinates
    GLdouble worldX, worldY, worldZ;

    // store the matrice for unprojection
    if (!is_matrix_set) {
        is_matrix_set = true;
        glGetDoublev( GL_MODELVIEW_MATRIX, modelview); //get the modelview info
        glGetDoublev( GL_PROJECTION_MATRIX, projection); //get the projection matrix info
        glGetIntegerv( GL_VIEWPORT, viewport); //get the viewport info
        viewport[2] /= 2;
        viewport[3] /= 2;
    }

    winX = lastPos.x();
    winY = viewport[3] - lastPos.y();
    winZ = 0;

    // get the world coordinates from the screen coordinates
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
    worldX *= 10 * eye_distance;
    worldY *= 10 * eye_distance;

    // iterate through the all the objects to check which one is selected
    for (auto it : solarSystem->getObjects()){
        GLfloat dist = it->getDistance();
        GLfloat theta = it->getAngleRevolution() / 180.0f * static_cast<float>(PI);
        GLdouble radius = static_cast<double>(it->getRadius());
        if (dist != 0)
            dist = 1.2*dist*dist/sqrt((1.2*dist*sin(theta))*(1.2*dist*sin(theta))+(dist*cos(theta))*(dist*cos(theta)));
        GLfloat x = dist * cos(theta);
        GLfloat y = dist * sin(theta) * cos(vAngle);

        // check whether mouse position is inside the object
        if (qPow(static_cast<double>(x)-worldX,2) + qPow(static_cast<double>(y)-worldY,2) <= (radius+0.2) * (radius+0.2)){
            currentObject = it;
            is_draw_shadow = true;
            if (it->getName()  ==  "Sun"){
                obj_x = -qSqrt(qPow(1.2,2) - qPow(1,2));
                obj_y = y;
                obj_r = radius;
            }
            else{
                obj_x = x;
                obj_y = y;
                obj_r = radius;
            }
            updateGL();
            emit currentObjectChanged();
            break;
        }
    }
}

/**
 * @brief RenderingWidget::mouseMoveEvent
 * adjusting the view
 * @param e
 */
void RenderingWidget::mouseMoveEvent(QMouseEvent *e){

    if (is_adjust_view){
        curPos = e->pos();
        float dH = static_cast<float>(atan((curPos.x() - lastPos.x()) / (5 * eye_distance)));
        float dV = static_cast<float>(atan((curPos.y() - lastPos.y()) / (5 * eye_distance)));

        hAngle -= dH;
        if (vAngle + dV > static_cast<float>(PI)/ 2)
            vAngle = static_cast<float>(PI) / 2;
        else if (vAngle + dV < -static_cast<float>(PI) / 2)
            vAngle = -static_cast<float>(PI) / 2;
        else
            vAngle += dV;

        eyeX = cos(static_cast<double>(vAngle)) * sin(static_cast<double>(hAngle));
        eyeY = sin(static_cast<double>(vAngle));
        eyeZ = cos(static_cast<double>(vAngle)) * cos(static_cast<double>(hAngle));
        lastPos = curPos;
    }
}

/**
 * @brief RenderingWidget::mouseReleaseEvent
 * stop adjusting the view
 * @param e
 */
void RenderingWidget::mouseReleaseEvent(QMouseEvent *e){

    is_adjust_view = false;
}

/**
 * @brief RenderingWidget::mouseDoubleClickEvent
 * to reset the view quickly with double click
 * @param e
 */
void RenderingWidget::mouseDoubleClickEvent(QMouseEvent *e){
    if (vAngle != 0)
        vAngle = 0;
    else
        vAngle = -PI / 2;
    hAngle = 0.0;
    eyeX = cos(static_cast<double>(vAngle)) * sin(static_cast<double>(hAngle));
    eyeY = sin(static_cast<double>(vAngle));
    eyeZ = cos(static_cast<double>(vAngle)) * cos(static_cast<double>(hAngle));
}

/**
 * @brief RenderingWidget::getSolarSystem
 * @return member variable solarSystem
 */
SolarSystem* RenderingWidget::getSolarSystem(){
    return solarSystem;
}

/**
 * @brief RenderingWidget::getCurrentObject
 * @return current selected object
 */
AstronmicalObject* RenderingWidget::getCurrentObject(){
    return currentObject;
}

/**
 * @brief RenderingWidget::updatePosition
 * update the position of objects
 */
void RenderingWidget::updatePosition(){
    for (auto it : solarSystem->getObjects()){
        it->update(timeSpeed/24);
    }
}

void RenderingWidget::drawShadow(GLfloat radius, GLfloat x, GLfloat y){
    glPushMatrix();
    glColor3f(1,1,1);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    for (int i=0; i<100; i++){
        glVertex2f(x+radius*cos(2*PI/100*i),y+radius*sin(2*PI/100*i));
    }
    glEnd();
}

void dragObject(){

}
