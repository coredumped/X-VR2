all: pgsql-query-test mysql-query-test

mysql-query-test: mysql-query-test.cpp
	c++ -g -o mysql-query-test mysql-query-test.cpp `xvr2-config.sh --cflags --libs`

pgsql-query-test: pgsql-query-test.cpp
	c++ -g -o pgsql-query-test pgsql-query-test.cpp `xvr2-config.sh --cflags --libs`

clean:
	rm -f pgsql-query-test mysql-query-test

rebuild: clean all
