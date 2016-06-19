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
    genotype.cpp

HEADERS += \
    course.h \
    schedule.h \
    courseDB.h \
    lecturerDB.h \
    lecturer.h \
    genotype.h

#QMAKE_CXXFLAGS += -lpq
QMAKE_LFLAGS += -L C:\PostgreSQL\9.5\bin -lpq
#message($LIBPQ_PATH)

