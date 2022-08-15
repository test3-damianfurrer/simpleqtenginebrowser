QT       += core gui
QT       += location webenginewidgets webengine multimedia

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = qtw
TEMPLATE = app

target.path = /usr/local/bin/
INSTALLS += target

SOURCES += qtw.cpp \
    qtwview.cpp \
    qtwengineview.cpp

HEADERS  += \
    qtwview.h \
    qtwengineview.h
