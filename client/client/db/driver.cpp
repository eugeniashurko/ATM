#include <memory>   // std::auto_ptr
#include <iostream>

#include <odb/database.hxx>
#include <odb/transaction.hxx>

#include <odb/sqlite/database.hxx>

#include "account.h"
#include "account-odb.hxx"

using namespace std;
using namespace odb::core;

int
main (int argc, char* argv[])
{
  try
  {
    auto_ptr<database> db (new odb::sqlite::database (argc, argv));
            //unsigned long a1_id, a2_id, a3_id;

            Account a1("11111111111111111",
                       "1111",
                       "George",
                       "Washington",
                       1000.0,
                       200.0);

            Account a2("222222222222222222",
                       "2222",
                       "Bogdan",
                       "Kulynych",
                       200.0,
                       50.0);

            Account a3("33333333333333333",
                       "3333",
                       "Jon",
                       "Snow",
                       10000.0);

          transaction t (db->begin ());

          // Make objects persistent and save their ids for later use.
          //
          //a1_id = 
          db->persist(a1);
          //a2_id = 
          db->persist(a2);
          //a3_id = 
          db->persist(a3);

          t.commit ();
        }
    catch (const odb::exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
