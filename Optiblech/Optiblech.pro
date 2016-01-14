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
    ../src/abstractFormConfiguration.cpp \
    ../src/abstractFormConfigurationTuple.cpp \
    ../src/binPacking.cpp \
    ../src/binPackingPlane.cpp \
    ../src/binPackingShelf.cpp \
    ../src/edge.cpp \
    ../src/form.cpp \
    ../src/formCombiner.cpp \
    ../src/globalParams.cpp \
    ../src/gpc.cpp \
    ../src/inputHandler.cpp \
    ../src/outputHandler.cpp \
    ../src/plane.cpp \
    ../src/point.cpp \
    ../src/pointSetAlgorithms.cpp \
    ../src/problem.cpp \
    ../src/setting.cpp \
    svgview.cpp \
    problemmanager.cpp \
    manageformdialog.cpp \
    managepointsdialog.cpp \
    formview.cpp \ 
    ../src/validator.cpp

HEADERS  += mainwindow.h \
    svgview.h \
    problemmanager.h \
    manageformdialog.h \
    managepointsdialog.h \
    formview.h

FORMS    += mainwindow.ui \
    manageformdialog.ui \
    managepointsdialog.ui

INCLUDEPATH = ../include


CONFIG += c++11
CONFIG += -stdlib=libstdc++
QMAKE_CXX = clang++
QMAKE_CC = clang

RESOURCES += \
    resources.qrc

