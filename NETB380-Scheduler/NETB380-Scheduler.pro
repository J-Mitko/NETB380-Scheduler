QT += core
QT -= gui

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
    population.cpp

HEADERS += \
    lecturer.h \
    course.h \
    schedule.h \
    courseDB.h \
    population.h

#QMAKE_CXXFLAGS += -lpq
QMAKE_LFLAGS += -L D:\PSQL\lib -lpq
#message($LIBPQ_PATH)

