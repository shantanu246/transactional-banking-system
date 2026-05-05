#include <iostream>
#include "sqlite3.h"

using namespace std;

int main()
{
    sqlite3 *db;
    if(sqlite3_open("bank.db",&db))
    {
        cout<<"Cannot open DB";
        return 1;
    }
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(
      db,
      "SELECT * FROM AccountDetails;",
      -1,
      &stmt,
      nullptr
    );

    while(sqlite3_step(stmt)==SQLITE_ROW)
    {
        cout
        << sqlite3_column_int(stmt,0) << " "
        << (const char*)sqlite3_column_text(stmt,1) << " "
        << (const char*)sqlite3_column_text(stmt,2) << " "
        << sqlite3_column_int(stmt,3)
        << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}