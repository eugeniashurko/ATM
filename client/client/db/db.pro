TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsqlite3 \
    -lssl \
    -lcrypto

SOURCES += main.cpp \
    account.cpp \
    dbmanager.cpp \
    hashutils.cpp

HEADERS += account.h \
    dbmanager.h \
    hashutils.h
