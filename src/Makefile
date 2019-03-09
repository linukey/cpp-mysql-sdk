all : db_manager test
.PHONY : all

db_manager : db_manager.cpp parameter.cpp
	g++ -c db_manager.cpp parameter.cpp -std=c++11 -Wall -W
	ar -crv libdb_manager.a db_manager.o parameter.o

test : test.cpp
	g++ test.cpp -L . -ldb_manager -lmysqlcppconn -o test -std=c++11 -Wall -W

clean :
	rm -rf libdb_manager.a db_manager.o parameter.o test
