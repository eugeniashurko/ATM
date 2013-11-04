#-------------------------------------------------
#
# Project created by QtCreator 2013-11-01T10:58:16
#
#-------------------------------------------------

QT       += core gui \
network \
sql \
webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ATM
TEMPLATE = app


SOURCES += main.cpp\
        gui/mainwindow.cpp \
        gui/startwidget.cpp \
    server/account.cpp \
    server/dbmanager.cpp \
    gui/authwidget.cpp \
    gui/menuwidget.cpp \
    gui/farewellwidget.cpp \
    client/connectionmanager.cpp

HEADERS  += gui/mainwindow.h \
    gui/startwidget.h \
    server/account.h \
    server/dbmanager.h \
    gui/authwidget.h \
    gui/menuwidget.h \
    gui/farewellwidget.h \
    client/connectionmanager.h

FORMS    += gui/mainwindow.ui \
    gui/startwidget.ui \
    gui/authwidget.ui \
    gui/menuwidget.ui \
    gui/farewellwidget.ui
