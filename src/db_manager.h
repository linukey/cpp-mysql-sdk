#ifndef __LINUKEY_DB_LAYER_H__
#define __LINUKEY_DB_LAYER_H__

#include "db.h"
#include "parameter.h"

#include <iostream>
#include <vector>
#include <memory>

namespace linukey {
namespace db_manager {

class DbManager {

public:

    /*
     * user_name : 用户名
     * passwd : 密码
     * hostname : 服务器ip
     * hostname : 服务器port
     */
    DbManager(const std::string& user_name,
              const std::string& passwd,
              const std::string& hostname = "127.0.0.1",
              const std::string& port = "3306");

    /*
     * 切换数据库
     *
     * db_name : 数据库
     *
     * return  : 成功 / 失败
     */
    bool UseDb(const std::string& db_name);

    /*
     * 创建表
     *
     * table_name : 表名
     *
     * sql : 执行语句
     */
    bool CreateTable(const std::string& sql);

    /*
     * 删除表
     *
     * table_name : 表名
     *
     */
    bool DropTable(const std::string& table_name);

    /*
     * 清空表
     *
     * table_name : 表名
     *
     * return : 成功 / 失败
     */
    bool TruncateTable(const std::string& table_name);
    
    /*
     * 查询数据
     *
     * resultset : 查询到的数据集
     * sql : 执行语句
     *
     * return : 成功 / 失败
     */
    std::shared_ptr<sql::ResultSet> SelectData(const std::string& sql);

    /*
     * 插入数据
     * 
     * sql : 执行语句
     * paras : 参数
     * 
     * return : 此次操作影响数据条数
     */
    int InsertData(const std::string& sql, const Parameter& paras);

private:
    sql::mysql::MySQL_Driver *_driver = nullptr;
    std::shared_ptr<sql::Connection> _connection;
};

}
}

#endif
