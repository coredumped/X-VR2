CC=g++
DEBUG=-gstabs+

all: mempcpy

mempcpy: mempcpy.cpp
	$(CC) $(DEBUG) -o mempcpy mempcpy.cpp `pkg-config xvr2core xvr2util --cflags --libs`

clean: 
	rm -f mempcpy

rebuild: clean all
