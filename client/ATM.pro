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
    client/gui/mainwindow.cpp \
    client/gui/widgets/startwidget.cpp \
    client/gui/widgets/authwidget.cpp \
    client/gui/widgets/menuwidget.cpp \
    client/gui/widgets/balancewidget.cpp \
    client/gui/widgets/withdrawwidget.cpp \
    client/connectionmanager.cpp \
    client/gui/dialogues/farewelldialogue.cpp \
    client/gui/widgets/periodictransfer.cpp \
    client/gui/widgets/periodic_tr_subwidgets/step1.cpp \
    client/gui/widgets/periodic_tr_subwidgets/step2.cpp \
    client/gui/widgets/periodic_tr_subwidgets/step3.cpp \
    client/gui/widgets/periodic_tr_subwidgets/step4.cpp \
    client/gui/widgets/periodic_tr_subwidgets/summary.cpp \
    client/gui/dialogues/authdialogue.cpp \
    client/gui/dialogues/withdrawalreceipt.cpp \
    client/gui/widgets/customsuminput.cpp \
    client/gui/widgets/withdrawresultok.cpp

HEADERS  += client/gui/mainwindow.h \
    client/gui/widgets/startwidget.h \
    client/gui/widgets/authwidget.h \
    client/gui/widgets/menuwidget.h \
    client/gui/widgets/balancewidget.h \
    client/gui/widgets/withdrawwidget.h \
    client/connectionmanager.h \
    client/gui/dialogues/farewelldialogue.h \
    client/gui/widgets/periodictransfer.h \
    client/gui/widgets/periodic_tr_subwidgets/step1.h \
    client/gui/widgets/periodic_tr_subwidgets/step2.h \
    client/gui/widgets/periodic_tr_subwidgets/step3.h \
    client/gui/widgets/periodic_tr_subwidgets/step4.h \
    client/gui/widgets/periodic_tr_subwidgets/summary.h \
    client/gui/dialogues/authdialogue.h \
    client/gui/dialogues/withdrawalreceipt.h \
    client/gui/widgets/customsuminput.h \
    client/gui/widgets/withdrawresultok.h

FORMS    += client/gui/mainwindow.ui \
    client/gui/widgets/startwidget.ui \
    client/gui/widgets/authwidget.ui \
    client/gui/widgets/menuwidget.ui \
    client/gui/widgets/balancewidget.ui \
    client/gui/widgets/withdrawwidget.ui \
    client/gui/dialogues/farewelldialogue.ui \
    client/gui/widgets/periodictransfer.ui \
    client/gui/widgets/periodic_tr_subwidgets/step1.ui \
    client/gui/widgets/periodic_tr_subwidgets/step2.ui \
    client/gui/widgets/periodic_tr_subwidgets/step3.ui \
    client/gui/widgets/periodic_tr_subwidgets/step4.ui \
    client/gui/widgets/periodic_tr_subwidgets/summary.ui \
    client/gui/dialogues/authdialogue.ui \
    client/gui/dialogues/withdrawalreceipt.ui \
    client/gui/widgets/step.ui \
    client/gui/widgets/customsuminput.ui \
    client/gui/widgets/withdrawresultok.ui
