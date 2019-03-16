cmake_minimum_required (VERSION 2.8)

add_compile_options(-std=c++11)

# boost 目录
INCLUDE_DIRECTORIES(/usr/local/include)

project (cpp-mysql-sdk)

aux_source_directory(src DIR_SRCS)

add_library(cpp-mysql-sdk ${DIR_SRCS})
target_link_libraries(cpp-mysql-sdk mysqlcppconn)

add_executable(test src/test.cpp)
target_link_libraries(test cpp-mysql-sdk)
