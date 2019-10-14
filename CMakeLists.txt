cmake_minimum_required (VERSION 3.13)
project (cpp-mysql-sdk)

#在Ubuntu 19版本开发的时候，开启rpath选项会有执行错误问题，怪得很
set(CMAKE_SKIP_BUILD_RPATH TRUE)

add_compile_options(-std=c++11)

include_directories(/usr/local/include/mysql-connector)
link_directories(/usr/local/lib/mysql-connector)

aux_source_directory(src DIR_SRCS)

add_library(cpp-mysql-sdk SHARED ${DIR_SRCS})
target_link_libraries(cpp-mysql-sdk mysqlcppconn)

add_executable(test test.cpp)
target_link_libraries(test cpp-mysql-sdk)
