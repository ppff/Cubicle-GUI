#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T11:10:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cubicle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    led.cpp \
    cube.cpp \
    plan.cpp \
    savetemporary.cpp




HEADERS  += mainwindow.h \
    plan.h\
    led.h\
    cube.h \
    savetemporary.h





FORMS    += mainwindow.ui \
    savetemporary.ui

RESOURCES += \
    ressource.qrc
