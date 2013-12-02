#include "dbmanager.h"
#include <iostream>
#include <sstream>

#include "hashutils.h"


DBManager::DBManager(std::string name):
    database(NULL)
{
   int ret = 0;
    // initialize engine
   if (SQLITE_OK != (ret = sqlite3_initialize())) {
       std::cout << "Failed to initialize library: " << ret;
   }
}


DBManager::~DBManager()
{

    closeDB();
}


void DBManager::createTables() {
    std::string createAccountQuery = "CREATE TABLE IF NOT EXISTS account "
            "(card VARCHAR(16) PRIMARY KEY,"
             "salt VARCHAR(64),"
             "pin_hash VARCHAR(64),"
             "name VARCHAR(70),"
             "available REAL,"
             "hold REAL,"
             "max_sum REAL,"
             "suppl_card VARCHAR(16))";

    sqlite3_stmt * createStmt;
    std::cout << "Creating Table Statement" << std::endl;
    sqlite3_prepare(database,
                    createAccountQuery.c_str(),
                    createAccountQuery.size(),
                    &createStmt,
                    NULL);
    std::cout << "Stepping Table Statement" << std::endl;
    if (sqlite3_step(createStmt) != SQLITE_DONE)
        std::cout << "Didn't Create Table Account!" << std::endl;
}

void DBManager::openDB(std::string fname) {
    int ret = 0;
    // open connection to a DB
    if (SQLITE_OK != (ret = sqlite3_open_v2(fname.c_str(), &database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)))
    {
        std::cout << "Failed to open connection with db: " << ret;
    }
}

void DBManager::closeDB() {
    if (database != 0)
        sqlite3_close(database);
    sqlite3_shutdown();
    database = 0;
}


void DBManager::insertAccount(const Account& a) {
    std::stringstream strs;
    strs << a.available();
    std::string available = strs.str();

    std::stringstream hstrs;
    hstrs << a.hold();
    std::string hold = hstrs.str();

    std::stringstream mstrs;
    mstrs << a.maxSum();
    std::string max_sum = mstrs.str();

    std::string sup = "NULL";
    if (a.supplemAccount()) {
        sup = a.supplemAccount()->cardNumber();
    }
    std::string insertQuery = std::string("INSERT INTO ACCOUNT "
            "VALUES ( \"") + a.cardNumber() +  std::string("\", \"")
            + a.salt() +  std::string("\", \"")
            + a.pinHash() +  std::string("\", \"")
            + a.name() +  std::string("\", ")
            + available +  std::string(", ")
            + hold +  std::string(", ")
            + max_sum +  std::string(", ");
    if (a.supplemAccount()) {
        insertQuery += "\"" +a.supplemAccount()->cardNumber()  +  std::string("\");");;
    } else {
        insertQuery += "NULL" +  std::string(");");;
    }
    sqlite3_stmt * insertStmt;
    sqlite3_prepare(database,
                    insertQuery.c_str(),
                    insertQuery.size(),
                    &insertStmt,
                    NULL);
    if (sqlite3_step(insertStmt) != SQLITE_DONE)
        std::cout << "Didn't insert into table!" << std::endl;

}

bool DBManager::existsRequest(std::string card) {
    bool res = false;
    std::string selectQuery = std::string("SELECT COUNT(*) FROM ACCOUNT "
                                                 "WHERE card = \"") + card + std::string("\";");
    sqlite3_stmt * getStmt;
    int ret = 0;
    if (SQLITE_OK != (ret = sqlite3_prepare(database,
                    selectQuery.c_str(),
                    selectQuery.size(),
                    &getStmt,
                    NULL))) {
        std::cout << "Failed to prepare select statement" << std::endl;
    }
    if (SQLITE_ROW != (ret = sqlite3_step(getStmt)))
    {
        std::cout << "Failed to step select" << std::endl;
    }
    std::istringstream hs(reinterpret_cast<const char*>(sqlite3_column_text(getStmt, 0)));
    int count;
    hs >> count;

    if (count != 0) {
        res = true;
    }
    return res;
}

bool DBManager::authRequest(std::string card, std::string pin) {
    bool success = false;

    // we get salt from database by card number
    std::string selectSaltQuery = std::string("SELECT salt FROM ACCOUNT "
                                                 "WHERE card = \"") + card + std::string("\";");
    sqlite3_stmt * getSaltStmt;
    int ret = 0;
    if (SQLITE_OK != (ret = sqlite3_prepare(database,
                    selectSaltQuery.c_str(),
                    selectSaltQuery.size(),
                    &getSaltStmt,
                    NULL))) {
        std::cout << "Failed to prepare select statement" << std::endl;
    }
    if (SQLITE_ROW != (ret = sqlite3_step(getSaltStmt)))
    {
        std::cout << "Failed to step select" << std::endl;
    }
    std::string salt = reinterpret_cast<const char*>(sqlite3_column_text(getSaltStmt, 0));

    // we generate hash
    std::string pin_hash = HashUtils::generateHash(pin, salt);

    // we get hash from db
    std::string selectHashQuery = std::string("SELECT pin_hash FROM ACCOUNT "
                                                 "WHERE card = \"") + card + std::string("\";");
    sqlite3_stmt * getHashStmt;
    if (SQLITE_OK != (ret = sqlite3_prepare(database,
                    selectHashQuery.c_str(),
                    selectHashQuery.size(),
                    &getHashStmt,
                    NULL))) {
        std::cout << "Failed to prepare select statement" << std::endl;
    }
    if (SQLITE_ROW != (ret = sqlite3_step(getHashStmt)))
    {
        std::cout << "Failed to step select" << std::endl;
    }
    std::string hash_from_db = reinterpret_cast<const char*>(sqlite3_column_text(getHashStmt, 0));

    // and compare them
    if (pin_hash == hash_from_db) {
        success = true;
    }

    return success;
}

std::string DBManager::nameRequest(std::string card) {

    std::string name = "";

    std::string selectNameQuery = std::string("SELECT name FROM ACCOUNT "
                                                 "WHERE card = \"") + card + std::string("\";");
    sqlite3_stmt * getNameStmt;
    int ret = 0;
    if (SQLITE_OK != (ret = sqlite3_prepare(database,
                    selectNameQuery.c_str(),
                    selectNameQuery.size(),
                    &getNameStmt,
                    NULL))) {
        std::cout << "Failed to prepare select statement" << std::endl;
    }
    if (SQLITE_ROW != (ret = sqlite3_step(getNameStmt)))
    {
        std::cout << "Failed to step select" << std::endl;
    }
    name = reinterpret_cast<const char*>(sqlite3_column_text(getNameStmt, 0));
    return name;
}


double DBManager::availableRequest(std::string card) {
    std::string selectAvailableQuery = std::string("SELECT available FROM ACCOUNT "
                                                 "WHERE card = \"") + card + std::string("\";");
    sqlite3_stmt * getAvailableStmt;
    int ret = 0;
    if (SQLITE_OK != (ret = sqlite3_prepare(database,
                    selectAvailableQuery.c_str(),
                    selectAvailableQuery.size(),
                    &getAvailableStmt,
                    NULL))) {
        std::cout << "Failed to prepare select statement" << std::endl;
    }
    if (SQLITE_ROW != (ret = sqlite3_step(getAvailableStmt)))
    {
        std::cout << "Failed to step select" << std::endl;
    }

    std::istringstream as(reinterpret_cast<const char*>(sqlite3_column_text(getAvailableStmt, 0)));
    double available;
    as >> available;
    return available;
}


double DBManager::holdRequest(std::string card) {
    std::string selectHoldQuery = std::string("SELECT hold FROM ACCOUNT "
                                                 "WHERE card = \"") + card + std::string("\";");
    sqlite3_stmt * getHoldStmt;
    int ret = 0;
    if (SQLITE_OK != (ret = sqlite3_prepare(database,
                    selectHoldQuery.c_str(),
                    selectHoldQuery.size(),
                    &getHoldStmt,
                    NULL))) {
        std::cout << "Failed to prepare select statement" << std::endl;
    }
    if (SQLITE_ROW != (ret = sqlite3_step(getHoldStmt)))
    {
        std::cout << "Failed to step select" << std::endl;
    }
    std::istringstream hs(reinterpret_cast<const char*>(sqlite3_column_text(getHoldStmt, 0)));
    double hold;
    hs >> hold;
    return hold;
}


double DBManager::maxSumRequest(std::string card) {
    std::string selectHoldQuery = std::string("SELECT max_sum FROM ACCOUNT "
                                                 "WHERE card = \"") + card + std::string("\";");
    sqlite3_stmt * getHoldStmt;
    int ret = 0;
    if (SQLITE_OK != (ret = sqlite3_prepare(database,
                    selectHoldQuery.c_str(),
                    selectHoldQuery.size(),
                    &getHoldStmt,
                    NULL))) {
        std::cout << "Failed to prepare select statement" << std::endl;
    }
    if (SQLITE_ROW != (ret = sqlite3_step(getHoldStmt)))
    {
        std::cout << "Failed to step select" << std::endl;
    }
    std::istringstream hs(reinterpret_cast<const char*>(sqlite3_column_text(getHoldStmt, 0)));
    double max_sum;
    hs >> max_sum;
    return max_sum;
}

std::string DBManager::supplementaryRequest(std::string card) {
    std::string suppl_card = "";

    std::string selectNameQuery = std::string("SELECT suppl_card FROM ACCOUNT "
                                                 "WHERE card = \"") + card + std::string("\";");
    sqlite3_stmt * getNameStmt;
    int ret = 0;
    if (SQLITE_OK != (ret = sqlite3_prepare(database,
                    selectNameQuery.c_str(),
                    selectNameQuery.size(),
                    &getNameStmt,
                    NULL))) {
        std::cout << "Failed to prepare select statement" << std::endl;
    }
    if (SQLITE_ROW != (ret = sqlite3_step(getNameStmt)))
    {
        std::cout << "Failed to step select" << std::endl;
    }
    if (NULL != sqlite3_column_text(getNameStmt, 0)) {
        suppl_card = reinterpret_cast<const char*>(sqlite3_column_text(getNameStmt, 0));
    } else {
        suppl_card = "";
    }

    return suppl_card;
}


bool DBManager::changeAvailable(std::string card, double sum) {
    bool success = false;

    std::stringstream strs;
    strs << sum;
    std::string available = strs.str();

    std::string setQuery = std::string("UPDATE ACCOUNT "
                                                "SET available=") + available +
                                   std::string(" WHERE card = \"") + card + std::string("\";");
    sqlite3_stmt * setStmt;
    sqlite3_prepare(database,
                    setQuery.c_str(),
                    setQuery.size(),
                    &setStmt,
                    NULL);
    if (sqlite3_step(setStmt) != SQLITE_DONE)
        std::cout << "Didn't update table!" << std::endl;
    else
        success = true;

    return success;
}


bool DBManager::changeHold(std::string card, double sum) {
    bool success = false;

    std::stringstream strs;
    strs << sum;
    std::string hold = strs.str();

    std::string setQuery = std::string("UPDATE ACCOUNT "
                                                "SET hold=") + hold +
                                   std::string(" WHERE card = \"") + card + std::string("\";");
    sqlite3_stmt * setStmt;
    sqlite3_prepare(database,
                    setQuery.c_str(),
                    setQuery.size(),
                    &setStmt,
                    NULL);
    if (sqlite3_step(setStmt) != SQLITE_DONE)
        std::cout << "Didn't update table!" << std::endl;
    else
        success = true;

    return success;
}


bool DBManager::changeMaxSum(std::string card, double sum) {
    bool success = false;

    std::stringstream strs;
    strs << sum;
    std::string max_sum = strs.str();

    std::string setQuery = std::string("UPDATE ACCOUNT "
                                                "SET max_sum=") + max_sum +
                                   std::string(" WHERE card = \"") + card + std::string("\";");
    sqlite3_stmt * setStmt;
    sqlite3_prepare(database,
                    setQuery.c_str(),
                    setQuery.size(),
                    &setStmt,
                    NULL);
    if (sqlite3_step(setStmt) != SQLITE_DONE)
        std::cout << "Didn't update table!" << std::endl;
    else
        success = true;

    return success;
}

bool DBManager::changeSupplCard(std::string card, std::string suppl_card) {
    bool success = false;
    std::string setQuery;
    if (suppl_card == "") {
        setQuery = std::string("UPDATE ACCOUNT "
                                                    "SET suppl_card=NULL "
                                                    "WHERE card = \"") + card + std::string("\";");
    } else {
        if (!existsRequest(suppl_card)) {
            return success;
        }
        setQuery = std::string("UPDATE ACCOUNT "
                                                    "SET suppl_card=") + suppl_card +
                                       std::string(" WHERE card = \"") + card + std::string("\";");
    }

    sqlite3_stmt * setStmt;
    sqlite3_prepare(database,
                    setQuery.c_str(),
                    setQuery.size(),
                    &setStmt,
                    NULL);
    if (sqlite3_step(setStmt) != SQLITE_DONE)
        std::cout << "Didn't update table!" << std::endl;
    else
        success = true;

    return success;
}

