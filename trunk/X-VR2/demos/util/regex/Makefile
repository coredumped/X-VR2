CC=g++
DEBUG=-gstabs+

all: simple xvr2grep

simple: simple.cpp
	$(CC) $(DEBUG) -o simple simple.cpp `pkg-config xvr2core xvr2util --cflags --libs`

xvr2grep: xvr2grep.cpp
	$(CC) $(DEBUG) -o xvr2grep xvr2grep.cpp `pkg-config xvr2core xvr2util --cflags --libs`

clean: 
	rm -f simple xvr2grep

rebuild: clean all
