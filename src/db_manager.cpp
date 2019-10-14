#include "db_manager.h"
#include "log.h"

#include <iostream>
#include <memory>
#include <vector>

using std::string;
using std::vector;
using std::pair;
using std::shared_ptr;

using sql::PreparedStatement;
using sql::Statement;
using sql::SQLString;
using sql::Connection;
using sql::SQLException;

using linukey::log::LOGOUT;

namespace linukey {
namespace db_manager {

DbManager::DbManager(const string& user_name, const string& passwd, const string& hostname, const string& port) {
    _driver = sql::mysql::get_mysql_driver_instance();
    DB_CHECK(_driver == nullptr, LOGOUT(log::FATAL, "%", "get_mysql_driver_fatal!"));

    _connection = shared_ptr<Connection>(_driver->connect(hostname + ":" + port, user_name, passwd));
    DB_CHECK(_connection == nullptr, LOGOUT(log::FATAL, "%", "get_mysql_conn_fatal!"));

    LOGOUT(log::TRACE, "connection db_server %:%", hostname.c_str(), port);
}

bool DbManager::CreateTable(const string& sql) const {
    SQLString sql_s(sql);
    // 注意, execute方法返回的true和false，代表两种不同的操作，分别是查询，更新或插入
    // 而不是执行结果的成功或失败。
    // 执行失败会抛异常
    try {
        shared_ptr<Statement> statement(_connection->createStatement());
        statement->execute(sql_s);
        LOGOUT(log::TRACE, "%", sql);
    } catch (const SQLException& ex) {
        LOGOUT(log::FATAL, "sql_execute_fatal! sql:%, reason:%, sql_state:%, errno: %",
            sql, ex.what(), ex.getSQLState().c_str(), ex.getErrorCode());
        return false;
    }

    return true;
}

bool DbManager::DropTable(const string& table_name) const {
    string sql_string = string("drop table ") + table_name;
    SQLString sql_s(sql_string);

    try {
        shared_ptr<Statement> statement(_connection->createStatement());
        statement->execute(sql_s);
        LOGOUT(log::TRACE, "%", sql_string);
    } catch (const SQLException& ex) {
        LOGOUT(log::FATAL, "sql_execute_fatal! sql:%, reason:%, sql_state:%, errno: %",
            sql_string, ex.what(), ex.getSQLState().c_str(), ex.getErrorCode());
        return false;
    }

    return true;
}

bool DbManager::TruncateTable(const string& table_name) const {
    string sql_string = string("truncate table ") + table_name;
    SQLString sql_s(sql_string);

    try {
        shared_ptr<Statement> statement(_connection->createStatement());
        statement->execute(sql_s);
        LOGOUT(log::TRACE, "%", sql_string);
    } catch (const SQLException& ex) {
        LOGOUT(log::FATAL, "sql_execute_fatal! sql:%, reason:%, sql_state:%, errno: %",
            sql_string, ex.what(), ex.getSQLState().c_str(), ex.getErrorCode());
        return false;
    }

    return true;
}

bool DbManager::UseDb(const std::string& db_name) const {
    try {
        _connection->setSchema(db_name);
    } catch (const SQLException& ex) {
        LOGOUT(log::FATAL, "set_schema_fatal!, reason:%, sql_state:%, errno: %",
            ex.what(), ex.getSQLState().c_str(), ex.getErrorCode());
        return false;
    }

    return true;
}

shared_ptr<sql::ResultSet> DbManager::SelectData(const string& sql) const {
    try {
        shared_ptr<Statement> statement(_connection->createStatement());
        return shared_ptr<sql::ResultSet>(statement->executeQuery(sql));
    } catch (const SQLException& ex) {
        LOGOUT(log::FATAL, "sql_execute_fatal! sql:%, reason:%, sql_state:%, errno: %",
            sql, ex.what(), ex.getSQLState().c_str(), ex.getErrorCode());
        return shared_ptr<sql::ResultSet>();
    }
}

shared_ptr<sql::ResultSet> DbManager::SelectData(const std::string& sql, const Parameter& paras) const {
    try {
        shared_ptr<PreparedStatement> statement(_connection->prepareStatement(SQLString(sql)));

        for (const auto& para : paras._bigint)
            statement->setBigInt(para.first, SQLString(para.second));
        for (const auto& para : paras._boolean)
            statement->setBoolean(para.first, para.second);
        for (const auto& para : paras._datetime)
            statement->setDateTime(para.first, para.second);
        for (const auto& para : paras._double)
            statement->setDouble(para.first, para.second);
        for (const auto& para : paras._int)
            statement->setInt(para.first, para.second);
        for (const auto& para : paras._uint)
            statement->setUInt(para.first, para.second);
        for (const auto& para : paras._int64)
            statement->setInt64(para.first, para.second);
        for (const auto& para : paras._uint64)
            statement->setUInt64(para.first, para.second);
        for (const auto& para : paras._null)
            statement->setNull(para.first, para.second);
        for (const auto& para : paras._string)
            statement->setString(para.first, para.second);

        return shared_ptr<sql::ResultSet>(statement->executeQuery());
    } catch (const SQLException& ex) {
        LOGOUT(log::FATAL, "sql_execute_fatal! sql:%, reason:%, sql_state:%, errno: %",
            sql, ex.what(), ex.getSQLState().c_str(), ex.getErrorCode());
        return shared_ptr<sql::ResultSet>();
    }
}

int DbManager::InsertData(const std::string& sql, const Parameter& paras) const {
    try {
        shared_ptr<PreparedStatement> statement(_connection->prepareStatement(SQLString(sql)));

        for (const auto& para : paras._bigint)
            statement->setBigInt(para.first, SQLString(para.second));
        for (const auto& para : paras._boolean)
            statement->setBoolean(para.first, para.second);
        for (const auto& para : paras._datetime)
            statement->setDateTime(para.first, para.second);
        for (const auto& para : paras._double)
            statement->setDouble(para.first, para.second);
        for (const auto& para : paras._int)
            statement->setInt(para.first, para.second);
        for (const auto& para : paras._uint)
            statement->setUInt(para.first, para.second);
        for (const auto& para : paras._int64)
            statement->setInt64(para.first, para.second);
        for (const auto& para : paras._uint64)
            statement->setUInt64(para.first, para.second);
        for (const auto& para : paras._null)
            statement->setNull(para.first, para.second);
        for (const auto& para : paras._string) {
            statement->setString(para.first, para.second);
        }
        
        return statement->executeUpdate();
    } catch (const SQLException& ex) {
        LOGOUT(log::FATAL, "sql_execute_fatal! sql:%, reason:%, sql_state:%, errno: %",
            sql, ex.what(), ex.getSQLState().c_str(), ex.getErrorCode());
        return 0;
    }
}

int DbManager::DeleteData(const std::string& sql, const Parameter& paras) const {
    try {
        shared_ptr<PreparedStatement> statement(_connection->prepareStatement(SQLString(sql)));

        for (const auto& para : paras._bigint)
            statement->setBigInt(para.first, SQLString(para.second));
        for (const auto& para : paras._boolean)
            statement->setBoolean(para.first, para.second);
        for (const auto& para : paras._datetime)
            statement->setDateTime(para.first, para.second);
        for (const auto& para : paras._double)
            statement->setDouble(para.first, para.second);
        for (const auto& para : paras._int)
            statement->setInt(para.first, para.second);
        for (const auto& para : paras._uint)
            statement->setUInt(para.first, para.second);
        for (const auto& para : paras._int64)
            statement->setInt64(para.first, para.second);
        for (const auto& para : paras._uint64)
            statement->setUInt64(para.first, para.second);
        for (const auto& para : paras._null)
            statement->setNull(para.first, para.second);
        for (const auto& para : paras._string) {
            statement->setString(para.first, para.second);
        }
        
        return statement->executeUpdate();
    } catch (const SQLException& ex) {
        LOGOUT(log::FATAL, "sql_execute_fatal! sql:%, reason:%, sql_state:%, errno: %",
            sql, ex.what(), ex.getSQLState().c_str(), ex.getErrorCode());
        return 0;
    }
}

int DbManager::UpdateData(const std::string& sql, const Parameter& paras) const {
    try {
        shared_ptr<PreparedStatement> statement(_connection->prepareStatement(SQLString(sql)));
        for (const auto& para : paras._bigint)
            statement->setBigInt(para.first, SQLString(para.second));
        for (const auto& para : paras._boolean)
            statement->setBoolean(para.first, para.second);
        for (const auto& para : paras._datetime)
            statement->setDateTime(para.first, para.second);
        for (const auto& para : paras._double)
            statement->setDouble(para.first, para.second);
        for (const auto& para : paras._int)
            statement->setInt(para.first, para.second);
        for (const auto& para : paras._uint)
            statement->setUInt(para.first, para.second);
        for (const auto& para : paras._int64)
            statement->setInt64(para.first, para.second);
        for (const auto& para : paras._uint64)
            statement->setUInt64(para.first, para.second);
        for (const auto& para : paras._null)
            statement->setNull(para.first, para.second);
        for (const auto& para : paras._string) {
            statement->setString(para.first, para.second);
        }
 
        return statement->executeUpdate();
    } catch (const SQLException& ex) {
        LOGOUT(log::FATAL, "sql_execute_fatal! sql:%, reason:%, sql_state:%, errno: %",
            sql, ex.what(), ex.getSQLState().c_str(), ex.getErrorCode());
        return 0;
    }
}

}
}
