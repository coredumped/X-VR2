all: pgsql-query-test_old mysql-query-test_old pgsql-query-test

mysql-query-test_old: mysql-query-test_old.cpp common.o
	g++ -gstabs+ -o mysql-query-test_old mysql-query-test_old.cpp `xvr2-config.sh --cflags --libs` common.o

pgsql-query-test_old: pgsql-query-test_old.cpp common.o
	g++ -gstabs+ -o pgsql-query-test_old pgsql-query-test_old.cpp `xvr2-config.sh --cflags --libs` common.o

pgsql-query-test: pgsql-query-test_ng.cpp common_ng.o
	g++ -gstabs+ -o pgsql-query-test pgsql-query-test_ng.cpp `xvr2-config.sh --cflags --libs` common_ng.o

common.o: common.cpp common.h
	g++ -c -gstabs+ -o common.o common.cpp `xvr2-config.sh --cflags`

common_ng.o: common_ng.cpp common_ng.h
	g++ -c -gstabs+ -o common_ng.o common_ng.cpp `xvr2-config.sh --cflags`

clean:
	rm -f pgsql-query-test mysql-query-test *.o pgsql-query-test_ng

rebuild: clean all
