#-------------------------------------------------
#
# Project created by QtCreator 2017-10-03T10:46:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ProcessForm
TEMPLATE = app
LIBS += -L/path/to -lpsapi

SOURCES += main.cpp\
        mainwindow.cpp \
    graph.cpp \
    qcustomplot.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    graph.h \
    qcustomplot.h \
    form.h

FORMS    += \
    mainwindow.ui \
    form.ui

RESOURCES += \
    resource.qrc
