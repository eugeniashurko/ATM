#include <QApplication>
#include <iostream>

#include "gui/mainwindow.h"
#include "client/connectionmanager.h"
#include "server/account.h"

int main(int argc, char *argv[])
{

//    Account * account1 = new Account("1111111", "1111", "Jack", "London");
//    printf("card: %s", qPrintable(account1->cardNumber()));
//    cout<<endl;
//    printf("name: %s", qPrintable(account1->name()));
//    cout<<endl;
//    printf("surname: %s", qPrintable(account1->surname()));
//    cout<<endl;
//    cout<<"balance: "<<account1->balance();
//    cout<<endl;
//    cout<<"blocked sum: "<<account1->blockedSum();
//    cout<<endl;
//    cout<<"maxBalance: "<<account1->maxBalance();
//    cout<<endl;



    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ConnectionManager * m = new ConnectionManager();
    m->connect();


    return a.exec();
}
