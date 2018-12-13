#ifndef NEHEWIDGE_H
#define NEHEWIDGE_H


#include <qgl.h>
#include <QGLWidget>
#include <QTimer>
#include <GLUT/glut.h>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <math.h>
#include <QSize>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <QtMath>


const GLfloat pi = acos(-1.0);

class NeHeWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit NeHeWidget(QWidget* parent, bool fs = false);
    ~NeHeWidget();
    void initializeGL();
    void paintGL();
    void loadGLTextures(QString filename, int id);
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void locate();

public slots:
    void outline();

signals:
    void press();


protected:
    bool fullscreen;
    GLfloat xTrans, yTrans;
    GLfloat rTri;
    GLfloat rQuad;
    GLfloat radius;
    QTimer *timer;
    GLUquadric *mySphere;
    QPoint lastPos;
    GLuint texture[10];
    glm::vec3 projected_c;
};




#endif // NEHEWIDGE_H
