#include "parameter.h"

#include <iostream>
#include <vector>

using std::make_pair;
using std::string;

namespace linukey {
namespace db_manager {

void Parameter::clear() {
    _bigint.clear();
    _boolean.clear();
    _datetime.clear();
    _double.clear();
    _int.clear();
    _uint.clear();
    _int64.clear();
    _uint64.clear();
    _null.clear();
    _string.clear();
}

void Parameter::setBigInt(int index, const string& val) {
    _bigint.push_back(make_pair(index, val));
}

void Parameter::setBoolean(int index, bool val) {
    _boolean.push_back(make_pair(index, val));
}

void Parameter::setDateTime(int index, const string& val) {
    _datetime.push_back(make_pair(index, val));
}

void Parameter::setDouble(int index, double val) {
    _double.push_back(make_pair(index, val));
}

void Parameter::setInt(int index, int32_t val) {
    _int.push_back(make_pair(index, val));
}

void Parameter::setUInt(int index, uint32_t val) {
    _uint.push_back(make_pair(index, val));
}

void Parameter::setInt64(int index, int64_t val) {
    _int64.push_back(make_pair(index, val));
}

void Parameter::setUInt64(int index, uint64_t val) {
    _uint64.push_back(make_pair(index, val));
}

void Parameter::setNull(int index, int val) {
    _null.push_back(make_pair(index, val));
}

void Parameter::setString(int index, const string& val) {
    _string.push_back(make_pair(index, val));
}

}
}
