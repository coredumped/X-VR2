all: pgsql-query-test mysql-query-test

mysql-query-test: mysql-query-test.cpp common.o
	c++ -g -o mysql-query-test mysql-query-test.cpp `xvr2-config.sh --cflags --libs` common.o

pgsql-query-test: pgsql-query-test.cpp common.o
	c++ -g -o pgsql-query-test pgsql-query-test.cpp `xvr2-config.sh --cflags --libs` common.o

common.o: common.cpp common.h
	c++ -c -g -o common.o common.cpp `xvr2-config.sh --cflags`

clean:
	rm -f pgsql-query-test mysql-query-test

rebuild: clean all
