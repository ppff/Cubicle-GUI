#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T11:10:23
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cubicle
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp\
    led.cpp\
    cube.cpp\
    plan.cpp\
    nouveaumotif.cpp\
    gestionfichier.cpp\
    simulation_cube.cpp \
    parser.c\
    CUB_parser.c \
    controlplan2d.cpp \
    controlcube3d.cpp



HEADERS  += mainwindow.h\
    plan.h\
    led.h\
    cube.h\
    dialog.h\
    nouveaumotif.h\
    gestionfichier.h\
    simulation_cube.h\
    adapt.h \
    parser.h\
    CUB_parser.h \
    global.h \
    controlplan2d.h \
    controlcube3d.h



FORMS    += mainwindow.ui
unix:!macx {
    LIBS +=-lGL -lGLU -lglut
    DEFINES += CUBICLE_ON_LINUX

}

macx: {
   LIBS +=-framework OpenGL
   DEFINES += CUBICLE_ON_MAC

}

win32 {

    LIBS +=-lglut
    DEFINES += CUBICLE_ON_WINDOWS

}

CONFIG += c++11

DEFINES += CUBICLE_SOFTWARE

RESOURCES +=\
    ressource.qrc

