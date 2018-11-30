#ifndef RENDERINGWIDGET_H
#define RENDERINGWIDGET_H
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <QGLWidget>
#include <qgl.h>
#include <QTimer>
#include <QDebug>
#include <QtOpenGL>
#include <vector>
#include <QMouseEvent>
#include "SolarSystem.h"
#include "AstronmicalObject.h"

class RenderingWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit RenderingWidget(QWidget *parent);
    ~RenderingWidget();
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void loadGLTextures(QString filename, int id);
    void wheelEvent(QWheelEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void drawStar();
    void drawSky();
    void drawSky(GLfloat x,GLfloat y,GLfloat z,GLfloat width,GLfloat height,GLfloat len);
    SolarSystem* getSolarSystem();
    AstronmicalObject* getCurrentObject();

private:
    QTimer timer;
    GLfloat rTri, rQuad;
    GLUquadricObj *mySphere;
    GLdouble eye_distance;
    GLdouble eyeX, eyeY,eyeZ;
    GLdouble eye_goal[3];
    GLuint texture[10];

    QPoint lastPos, curPos;
    GLfloat hAngle, vAngle;

    SolarSystem *solarSystem;
    AstronmicalObject *currentObject;

    bool is_adjust_view;

};

#endif // RENDERINGWIDGET_H
