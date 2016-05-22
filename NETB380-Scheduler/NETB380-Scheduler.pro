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
    studentgroup.cpp \
    schedule.cpp

HEADERS += \
    lecturer.h \
    course.h \
    studentgroup.h \
    schedule.h
