CC=g++
DEBUG=-gstabs+

all: array list

array: array.cpp
	$(CC) $(DEBUG) -o array array.cpp `pkg-config xvr2core xvr2util --cflags --libs`

list: list.cpp
	$(CC) $(DEBUG) -o list list.cpp `pkg-config xvr2core xvr2util --cflags --libs`

clean: 
	rm -f array list

rebuild: clean all
