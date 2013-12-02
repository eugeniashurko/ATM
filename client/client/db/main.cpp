#include <iostream>

#include "dbmanager.h"


using namespace std;

int main()
{
    DBManager m("bank.db");
    m.openDB("bank.db");
    m.createTables();
    Account a1("11111111111111111",
               "1111",
               "George Washington",
               1000.0,
               200.0);

    Account a2("222222222222222222",
               "2222",
               "Bogdan Kulynych",
               200.0,
               50.0);

    Account a3("33333333333333333",
               "3333",
               "Jon Snow",
               10000.0);
    m.insertAccount(a1);
    m.insertAccount(a2);
    m.insertAccount(a3);
    std::cout << "Exists:" << std::boolalpha << m.existsRequest("3434") << std::endl;
    std::cout << "Exists:" << std::boolalpha << m.existsRequest("11111111111111111") << std::endl;
    std::cout << std::boolalpha << m.authRequest("11111111111111111", "1111") << std::endl;
    std::cout << std::boolalpha << m.authRequest("11111111111111111", "1311") << std::endl;
    std::cout << "Name: " << m.nameRequest("11111111111111111") << std::endl;
    std::cout << "Available: " << m.availableRequest("11111111111111111") << std::endl;
    std::cout << "Hold: " << m.holdRequest("11111111111111111") << std::endl;
    m.changeAvailable("222222222222222222", 340);
    m.changeHold("222222222222222222", 0);
    if (m.supplementaryRequest("11111111111111111") == "") {
        std::cout << "Suppl card: is empty" << std::endl;
    } else {
        std::cout << "Suppl card: " << m.supplementaryRequest("11111111111111111") << std::endl;
    }
    m.changeSupplCard("11111111111111111", "222222222222222222");
    m.changeMaxSum("11111111111111111", 300);
    if (m.supplementaryRequest("11111111111111111") == "") {
        std::cout << "Suppl card: is empty" << std::endl;
    } else {
        std::cout << "Suppl card: " << m.supplementaryRequest("11111111111111111") << std::endl;
        std::cout << "Max sum: " << m.maxSumRequest("11111111111111111") << std::endl;
    }
    m.changeSupplCard("11111111111111111", "");
    if (m.supplementaryRequest("11111111111111111") == "") {
        std::cout << "Suppl card: is empty" << std::endl;
    } else {
        std::cout << "Suppl card: " << m.supplementaryRequest("11111111111111111") << std::endl;
        std::cout << "Max sum: " << m.maxSumRequest("11111111111111111") << std::endl;
    }
    return 0;
}

