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

LIBS += -lqjson

SOURCES += main.cpp\
    client/gui/mainwindow.cpp \
    client/gui/widgets/startwidget.cpp \
    client/gui/widgets/authwidget.cpp \
    client/gui/widgets/menuwidget.cpp \
    client/gui/widgets/balancewidget.cpp \
    client/gui/widgets/withdrawwidget.cpp \
    client/gui/dialogues/farewelldialogue.cpp \
    client/gui/widgets/periodictransfer.cpp \
    client/gui/widgets/periodic_tr_subwidgets/step1.cpp \
    client/gui/widgets/periodic_tr_subwidgets/step2.cpp \
    client/gui/widgets/periodic_tr_subwidgets/step3.cpp \
    client/gui/widgets/periodic_tr_subwidgets/step4.cpp \
    client/gui/widgets/periodic_tr_subwidgets/summary.cpp \
    client/gui/dialogues/withdrawalreceipt.cpp \
    client/gui/widgets/customsuminput.cpp \
    client/gui/widgets/withdrawresultok.cpp \
    client/gui/widgets/transfer.cpp \
    client/gui/widgets/supportwidget.cpp \
    client/gui/dialogues/transferreceipt.cpp \
    client/gui/dialogues/servererror.cpp \
    client/gui/widgets/servererrorwidget.cpp \
    client/gui/widgets/pinremindwidget.cpp \
    client/gui/widgets/overflowwidget.cpp \
    client/gui/widgets/newoverflowwidget.cpp \
    client/gui/dialogues/pinreminddialogue.cpp \
    client/logic/networking/connectionmanager.cpp \
    client/logic/networking/session.cpp \
    client/logic/utils/LogFile.cpp \
    client/logic/utils/Validate.cpp \
    client/logic/utils/Service.cpp \
    client/logic/teller.cpp \
    client/logic/Notes.cpp \
    client/logic/banknotecombination.cpp


HEADERS  += client/gui/mainwindow.h \
    client/gui/widgets/startwidget.h \
    client/gui/widgets/authwidget.h \
    client/gui/widgets/menuwidget.h \
    client/gui/widgets/balancewidget.h \
    client/gui/widgets/withdrawwidget.h \
    client/gui/widgets/periodictransfer.h \
    client/gui/widgets/periodic_tr_subwidgets/step1.h \
    client/gui/widgets/periodic_tr_subwidgets/step2.h \
    client/gui/widgets/periodic_tr_subwidgets/step3.h \
    client/gui/widgets/periodic_tr_subwidgets/step4.h \
    client/gui/widgets/periodic_tr_subwidgets/summary.h \
    client/gui/widgets/customsuminput.h \
    client/gui/widgets/withdrawresultok.h \
    client/gui/widgets/transfer.h \
    client/gui/widgets/supportwidget.h \
    client/gui/widgets/servererrorwidget.h \
    client/gui/widgets/pinremindwidget.h \
    client/gui/widgets/overflowwidget.h \
    client/gui/widgets/newoverflowwidget.h \
    client/gui/dialogues/farewelldialogue.h \
    client/gui/dialogues/withdrawalreceipt.h \
    client/gui/dialogues/transactionreceipt.h \
    client/gui/dialogues/transferreceipt.h \
    client/gui/dialogues/servererror.h \
    client/gui/dialogues/pinreminddialogue.h \
    client/logic/networking/connectionmanager.h \
    client/logic/networking/session.h \
    client/logic/utils/LogFile.h \
    client/logic/utils/Validate.h \
    client/logic/utils/Service.h \
    client/logic/teller.h \
    client/logic/Notes.h \
    client/logic/banknotecombination.h


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
    client/gui/widgets/customsuminput.ui \
    client/gui/dialogues/withdrawalreceipt.ui \
    client/gui/widgets/step.ui \
    client/gui/widgets/withdrawresultok.ui \
    client/gui/widgets/transfer.ui \
    client/gui/widgets/supportwidget.ui \
    client/gui/dialogues/transferreceipt.ui \
    client/gui/dialogues/servererror.ui \
    client/gui/widgets/servererrorwidget.ui \
    client/gui/widgets/pinremindwidget.ui \
    client/gui/widgets/overflowwidget.ui \
    client/gui/widgets/newoverflowwidget.ui \
    client/gui/dialogues/pinreminddialogue.ui
