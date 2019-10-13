#include <iostream>
#include "src/db_manager.h"

using namespace std;
using namespace sql;
using namespace linukey::db_manager;

int main() {
    const string db_name = "one_db";
    const string table_name = "person";

    DbManager db_manager("linukey", "linukey", "tcp://127.0.0.1", "3306");
    if (!db_manager.UseDb(db_name)) {
        cout << "use db fail!" << endl;
        return 0;
    }

    vector<pair<string, string>> paras;

    paras.push_back(make_pair("id", "int"));
    paras.push_back(make_pair("name", "varchar(255)"));

    if (db_manager.DropTable(table_name)) {
        cout << "drop table success!" << endl;
    } else {
        cout << "drop table fail!" << endl;
    }

    const string create_table_sql = "create table person (id int, name varchar(255)) default charset=utf8;";

    if (db_manager.CreateTable(create_table_sql)) {
        cout << "create table success!" << endl;
    } else {
        cout << "create table fail!" << endl;
    }

    if (db_manager.TruncateTable(table_name)) {
        cout << "truncate table success!" << endl;
    } else {
        cout << "truncate table fail!" << endl;
    }

    const string sql = "insert into person values(?, ?);";
    Parameter para;
    para.setInt(1, 1);
    para.setString(2, "linukey");
    
    cout << "write:" << db_manager.InsertData(sql, para) << endl;

    shared_ptr<sql::ResultSet> ret = db_manager.SelectData("select * from person");
    if (ret != nullptr) {
        while (ret->next()) {
            cout << ret->getInt(1) << ":" << ret->getString(2) << endl;
        }
    }

    return 0;
}
