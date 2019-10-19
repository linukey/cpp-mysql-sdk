#ifndef __CPP_MYSQL_PARAMETER_H__
#define __CPP_MYSQL_PARAMETER_H__

#include <iostream>
#include <vector>

namespace cpp_mysql {

struct Parameter {
    void setBigInt(int, const std::string&);
    void setBoolean(int, bool);
    void setDateTime(int, const std::string&);
    void setDouble(int, double);
    void setInt(int, int32_t);
    void setUInt(int, uint32_t);
    void setInt64(int, int64_t);
    void setUInt64(int, uint64_t);
    void setNull(int, int);
    void setString(int, const std::string&);

    void clear();

private:

    std::vector<std::pair<int, const std::string>> _bigint;
    std::vector<std::pair<int, bool>> _boolean;
    std::vector<std::pair<int, const std::string>> _datetime;
    std::vector<std::pair<int, double>> _double;
    std::vector<std::pair<int, int32_t>> _int;
    std::vector<std::pair<int, uint32_t>> _uint;
    std::vector<std::pair<int, int64_t>> _int64;
    std::vector<std::pair<int, uint64_t>> _uint64;
    std::vector<std::pair<int, int>> _null;
    std::vector<std::pair<int, const std::string>> _string;

    friend class DbManager;
};

}

#endif
