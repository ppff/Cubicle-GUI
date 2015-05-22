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
    dialog.cpp \
    afficheplan.cpp \
    creationfichier.cpp \
    savetemporary.cpp \
    selection_plan.cpp




HEADERS  += mainwindow.h \
    plan.h\
    led.h\
    cube.h \
    dialog.h \
    afficheplan.h


FORMS    += mainwindow.ui \
    dialog.ui \
    afficheplan.ui
    creationfichier.h \
    savetemporary.h \
    selection_plan.h





FORMS    += mainwindow.ui \
    creationfichier.ui \
    savetemporary.ui \
    selection_plan.ui


RESOURCES += \
    ressource.qrc
