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
    lecturerDB.cpp \
    chromosome.cpp

HEADERS += \
    course.h \
    schedule.h \
    courseDB.h \
    lecturerDB.h \
    lecturer.h \
    chromosome.h

#QMAKE_CXXFLAGS += -lpq
QMAKE_LFLAGS += -L D:\NETB\psql\bin -lpq # jMITKO'S
#QMAKE_LFLAGS += -L MILEN -lpq
#message($LIBPQ_PATH)

