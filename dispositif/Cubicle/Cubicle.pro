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
        mainwindow.cpp\
    led.cpp\
    cube.cpp\
    plan.cpp\
    dialog.cpp\
    afficheplan.cpp\
    save.cpp\
    toolbar.cpp \
    personbutton.cpp




HEADERS  += mainwindow.h\
    plan.h\
    led.h\
    cube.h\
    dialog.h\
    afficheplan.h\
    save.h\
    toolbar.h \
    personbutton.h



FORMS    += mainwindow.ui\
    dialog.ui\
    afficheplan.ui\
    save.ui\
    toolbar.ui


RESOURCES += \
    ressource.qrc
