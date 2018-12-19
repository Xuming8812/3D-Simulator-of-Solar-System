#-------------------------------------------------
#
# Project created by QtCreator 2018-11-20T13:38:53
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SolarSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS GL_SILENCE_DEPRECATION

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += $$PWD/src
CONFIG += c++11

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/renderingwidget.cpp \
        src/AstronmicalObject.cpp \
        src/SolarSystem.cpp

HEADERS += \
        src/mainwindow.h \
        src/renderingwidget.h \
        src/AstronmicalObject.h \
        src/SolarSystem.h


FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

mac: LIBS += -framework GLUT
else:unix|win32: LIBS += -lglut -lGLU

LIBS += -pthread

RESOURCES += \
    qsrc.qrc
