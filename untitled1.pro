#-------------------------------------------------
#
# Project created by QtCreator 2017-05-05T03:06:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Maze.cpp \
    myscene.cpp \
    Node.cpp

HEADERS  += mainwindow.h \
    Maze.h \
    myscene.h \
    Node.h

FORMS    += mainwindow.ui

RESOURCES += \
    myimages.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lstdc++
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lstdc++
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lstdc++

INCLUDEPATH += $$PWD/../../../../usr/local/lib
DEPENDPATH += $$PWD/../../../../usr/local/lib

DISTFILES +=
