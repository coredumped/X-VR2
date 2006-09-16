CC=g++
DEBUG=-gstabs+

all: config

config: config.cpp
	$(CC) $(DEBUG) -o config config.cpp `pkg-config xvr2core xvr2util --cflags --libs`

clean: 
	rm -f config

rebuild: clean all
