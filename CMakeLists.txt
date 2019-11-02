cmake_minimum_required (VERSION 3.10.2)
project (cpp-mysql-sdk)

#set(CMAKE_SKIP_BUILD_RPATH TRUE)

add_compile_options(-std=c++11)

include_directories(/usr/local/mysql/connector-c++-8.0/include/jdbc/)
link_directories(/usr/local/mysql/connector-c++-8.0/lib64/debug)

aux_source_directory(src DIR_SRCS)

add_library(cpp-mysql-sdk SHARED ${DIR_SRCS})
target_link_libraries(cpp-mysql-sdk mysqlcppconn-static -lpthread -lz -ldl)

add_executable(a.out test.cpp)
target_link_libraries(a.out cpp-mysql-sdk)
