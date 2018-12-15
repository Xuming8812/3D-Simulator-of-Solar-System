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
#include <thread>
#include <QDebug>
#include <QtOpenGL>
#include <vector>
#include <QMouseEvent>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
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
    void mouseDoubleClickEvent(QMouseEvent* e);

    void drawSky();
//    void outline();

    SolarSystem* getSolarSystem();
    AstronmicalObject* getCurrentObject();

private:

    GLfloat rTri, rQuad;
    GLUquadricObj *shadow;
    GLUquadricObj *skySphere;
    GLdouble eye_distance;
    GLdouble eyeX, eyeY,eyeZ;
    GLdouble eye_goal[3];
    GLuint texture[10];

    QPoint lastPos, curPos;
    GLfloat hAngle, vAngle;

    GLfloat positions[10][2];

    SolarSystem *solarSystem;
    AstronmicalObject *currentObject;

    GLint viewport[4]; //var to hold the viewport info
    GLdouble modelview[16]; //var to hold the modelview info
    GLdouble projection[16]; //var to hold the projection matrix info

    bool is_adjust_view;
    bool is_fullscreen;
    bool is_matrix_set;
signals:
    void currentObjectChanged();

public:
    QTimer timer;
    bool is_highlighting;
    bool is_play;
    std::vector<AstronmicalObject> objects_copy;

private slots:
    void updatePosition();

};

#endif // RENDERINGWIDGET_H
