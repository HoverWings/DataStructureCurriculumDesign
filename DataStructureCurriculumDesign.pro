#-------------------------------------------------
#
# Project created by QtCreator 2018-01-24T17:45:22
#
#-------------------------------------------------

QT       += core gui
QT       += axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataStructureCurriculumDesign
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    classScheduleLink.cpp \
    classScheduleMat.cpp \
    room.cpp \
    student.cpp \
    teacher.cpp \
    readexcel.cpp \
    excelengine.cpp

HEADERS += \
        mainwindow.h \
    classScheduleLink.h \
    classScheduleMat.h \
    room.h \
    teacher.h \
    student.h \
    readexcel.h \
    excelengine.h

FORMS += \
        mainwindow.ui
