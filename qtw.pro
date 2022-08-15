# ============================================================
# Crusta - Qt5 webengine browser
# Copyright (C) 2017 Anmol Gautam <anmol@crustabrowser.com>
#
# THIS FILE IS A PART OF CRUSTA
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# ============================================================ */

#-------------------------------------------------
#
# Project created by QtCreator 2017-03-22T20:08:06
#
#-------------------------------------------------

#-----------------------------------------------------------------
#
# Crusta now uses cmake, this file is included only for reference
#
#-----------------------------------------------------------------

#QT       += core gui charts
#QT       += location webenginewidgets webengine texttospeech multimedia

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

#RESOURCES += \
#    resource.qrc

#RC_ICONS += crusta.ico

#DESTDIR = $$PWD/../out
#OBJECTS_DIR = $$PWD/../out/.obj
#MOC_DIR = $$PWD/../out/.moc
#RCC_DIR = $$PWD/../out/.rcc
#UI_DIR = $$PWD/../out/.ui
