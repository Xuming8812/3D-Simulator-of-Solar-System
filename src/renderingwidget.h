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
#include <QtOpenGL>

class RenderingWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit RenderingWidget(QWidget *parent);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void loadGLTextures(QString filename, int id);
    void drawStar();

private:
    QTimer timer;
    GLfloat rTri, rQuad;
    GLUquadricObj *mySphere;
    GLuint texture[10];

};

#endif // RENDERINGWIDGET_H
