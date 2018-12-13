#include "nehewidget.h"
#include <QDebug>
#include <math.h>


NeHeWidget::NeHeWidget(QWidget* parent, bool fs) : QGLWidget(parent)
{
    fullscreen = fs;
    rTri = 0.0;
    rQuad = 0.0;
    xTrans = 0.0;
    yTrans = 0.0;

    lastPos.setX(300);
    lastPos.setY(150);
    setGeometry(100,100,600,300);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(0.1);

    if(fullscreen){
        showFullScreen();
    }
}

NeHeWidget::~NeHeWidget(){

}

void NeHeWidget::initializeGL(){
    loadGLTextures(":images/earth_daymap.jpg",1);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.6, 0.8, 0.6, 0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    mySphere = gluNewQuadric();
    gluQuadricNormals(mySphere,GL_SMOOTH);
    gluQuadricTexture(mySphere,GL_TRUE);
}

void NeHeWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//draw sphere
    glColor3f(1,1,1);
    glLoadIdentity();
    gluLookAt(0,0,10,0,0,0,0,1,0);
 //   glRotatef(rTri,0,1,0);
//    glRotatef(rTri,0,0,1);
    glTranslatef(xTrans,yTrans,-10);
    glRotatef(rTri,1,1,1);
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    gluSphere(mySphere,2,30,30);
    GLfloat  sun_ambient[]={0.0,0.0,0.0,1.0};
    GLfloat  sun_diffuse[]={0.0,0.0,0.0,1.0};
    GLfloat  sun_specular[]={0.0,0.0,0.0,1.0};
    GLfloat  sun_shininess=20.0;
    glMaterialfv(GL_BACK, GL_AMBIENT, sun_ambient);
    glMaterialfv(GL_BACK, GL_DIFFUSE, sun_diffuse);
    glMaterialfv(GL_BACK, GL_SPECULAR, sun_specular);
    glMaterialf(GL_BACK, GL_SHININESS, sun_shininess);
    rTri += 0.1;
    rTri = rTri == 360 ? 0 : rTri;
    if (qPow(lastPos.x()-(projected_c.x-300)/16 -300,2) + qPow(lastPos.y()-150+(projected_c.y-150)/8,2) <= 30*30){
        timer->stop();
        outline();
    }
}

void NeHeWidget::resizeGL(int width, int height){
    if (height == 0){
        height = 1;
    }
    glViewport(0, 0, static_cast<GLint>(width), static_cast<GLint>(height));
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0,static_cast<double>(width*1.0/height),10,20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void NeHeWidget::mousePressEvent(QMouseEvent* e){
    lastPos = e->pos();
    locate();
    qDebug() << lastPos;
}

void NeHeWidget::mouseMoveEvent(QMouseEvent* e){
    GLfloat dx = (e->x() - lastPos.x())/20.0;
    GLfloat dy = (e->y() - lastPos.y())/20.0;
    if (e->buttons() & Qt::LeftButton){
        if (qPow(lastPos.x()-(projected_c.x-300)/16 -300,2) + qPow(lastPos.y()-150+(projected_c.y-150)/8,2) <= 30*30){
            xTrans += dx;
            yTrans -= dy;
            rTri  += 10;
            locate();
            updateGL();
        }
    }
    lastPos = e->pos();
}

void NeHeWidget::outline(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0,1.0,1.0,0.2);
    glLoadIdentity();
    gluLookAt(0,0,10,0,0,0,0,1,0);
    glTranslatef(xTrans,yTrans,-10);
    glRotatef(rTri,1,1,1);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    gluSphere(mySphere,2.2,30,30);
    GLfloat  sun_ambient[]={0.0,0.0,0.0,1.0};
    GLfloat  sun_diffuse[]={0.0,0.0,0.0,1.0};
    GLfloat  sun_specular[]={0.0,0.0,0.0,1.0};
    GLfloat  sun_shininess=20.0;
    glMaterialfv(GL_BACK, GL_AMBIENT, sun_ambient);
    glMaterialfv(GL_BACK, GL_DIFFUSE, sun_diffuse);
    glMaterialfv(GL_BACK, GL_SPECULAR, sun_specular);
    glMaterialf(GL_BACK, GL_SHININESS, sun_shininess);
    rTri += 0.1;
    rQuad += 0.001;
}

void NeHeWidget::loadGLTextures(QString filename, int id){
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

void NeHeWidget::locate(){
    glm::vec3 center = glm::vec3(xTrans, yTrans, -10);
//    glm::vec3 radius = glm::vec3(xTrans+2, yTrans+2, -10);
    glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(xTrans, yTrans, -10.0f));
    glm::mat4 projection = glm::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 10.0f, 20.0f);
    glm::vec4 viewport(0.0f, 0.0f, 600.0f, 300.0f);
    projected_c = glm::project(center, modelview, projection, viewport);
//    glm::vec3 projected_r = glm::project(radius, modelview, projection, viewport);
    qDebug() << (projected_c.x-300)/16 +300 << " " << 150-(projected_c.y-150)/8 << " " << projected_c.z;
//    qDebug() << projected_r.x << " " << projected_r.y;
}

