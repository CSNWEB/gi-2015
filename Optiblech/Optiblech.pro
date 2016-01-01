    #-------------------------------------------------
#
# Project created by QtCreator 2015-12-23T10:13:27
#
#-------------------------------------------------

QT       += core gui svg

qtHaveModule(opengl): QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Optiblech
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../src/abstractForm.cpp \
    ../src/binPacking.cpp \
    ../src/binPackingPlane.cpp \
    ../src/binPackingShelf.cpp \
    ../src/edge.cpp \
    ../src/form.cpp \
    ../src/gpc.cpp \
    ../src/inputHandler.cpp \
    ../src/outputHandler.cpp \
    ../src/plane.cpp \
    ../src/point.cpp \
    ../src/problem.cpp \
    ../src/setting.cpp \
    ../src/simpleSVG.cpp \
    svgview.cpp \
    problemmanager.cpp \
    addformdialog.cpp

HEADERS  += mainwindow.h \
    svgview.h \
    problemmanager.h \
    addformdialog.h

FORMS    += mainwindow.ui \
    addformdialog.ui

INCLUDEPATH = ../include