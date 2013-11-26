#include <QApplication>
#include <QDebug>
#include <QFile>
#include <iostream>
#include <string>
#include "client/gui/mainwindow.h"
#include "client/logic/networking/connectionmanager.h"
#include "client/logic/utils/LogFile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
