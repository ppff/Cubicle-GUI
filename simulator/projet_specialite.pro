#-------------------------------------------------
#
# Project created by QtCreator 2015-01-11T17:39:08
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = simulator

TEMPLATE = app

OBJECTS_DIR = obj
MOC_DIR = moc
UI_DIR = ui

QMAKE_CXXFLAGS += -std=c++11 \
                  -Wall -Werror


SOURCES += main.cpp\
        mainwindow.cpp \
    simulation_cube.cpp \
    motif.cpp \
    groupe.cpp \
    cartesd.cpp \
    memoireinterne.cpp

HEADERS  += mainwindow.h \
    simulation_cube.h \
    global.h \
    motif.h \
    groupe.h \
    cartesd.h \
    memoireinterne.h \
    adapt.h

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
RESOURCES += \
    ressources.qrc
