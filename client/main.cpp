#include "gui/mainwindow.h"
#include "server/dbmanager.h"
#include <QApplication>
#include <iostream>
//#include "server/account.h"

int main(int argc, char *argv[])
{
    // db initialization now
//    DBManager * m = new DBManager;
//    if (!m->openDB()) {
//        cout<<"Failed to open db"<<endl;
//        printf("Last error: %s", qPrintable(m->lastError().text()));
//    } else
//        cout<<"Database opened successfully"<<endl;
//    if (!m->createAccountTable()) {
//      cout<<"Failed to create table"<<endl;
//     printf("Last error: %s", qPrintable(m->lastError().text()));
//  } else
//        cout<<"Table created successfully"<<endl;

    Account * account1 = new Account("1111111", "1111", "Jack", "London");
    printf("card: %s", qPrintable(account1->cardNumber()));
    cout<<endl;
//    printf("pin: %s", qPrintable(account1->PIN()));
//    cout<<endl;
    printf("name: %s", qPrintable(account1->name()));
    cout<<endl;
    printf("surname: %s", qPrintable(account1->surname()));
    cout<<endl;
    cout<<"balance: "<<account1->balance();
    cout<<endl;
    cout<<"blocked sum: "<<account1->blockedSum();
    cout<<endl;
    cout<<"maxBalance: "<<account1->maxBalance();
    cout<<endl;
//    if (!m->insertAccount(*account1)) {
//        cout<<"Insertion failed"<<endl;
//        printf("Last error: %s", qPrintable(m->lastError().text()));

//    } else {
//        cout<<"Insertion successful"<<endl;
//    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
