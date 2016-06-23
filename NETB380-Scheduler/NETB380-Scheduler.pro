QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = NETB380-Scheduler
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    lecturer.cpp \
    course.cpp \
    schedule.cpp \
    courseDB.cpp \
    lecturerDB.cpp \
    chromosome.cpp \
    window.cpp

HEADERS += \
    course.h \
    schedule.h \
    courseDB.h \
    lecturerDB.h \
    lecturer.h \
    chromosome.h \
    window.h

#QMAKE_CXXFLAGS += -lpq
#QMAKE_LFLAGS += -L D:\PSQL\bin -lpq
QMAKE_LFLAGS += -L D:\PSQL\bin -lpq # jMITKO'S
#message($LIBPQ_PATH)

