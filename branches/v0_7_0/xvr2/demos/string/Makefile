CC=g++
DEBUG=-gstabs+

all: basic comparisons

basic: basic.cpp
	$(CC) $(DEBUG) -o basic basic.cpp `xvr2-config.sh --cflags --libs`

comparisons: comparisons.cpp
	$(CC) $(DEBUG) -o comparisons comparisons.cpp `xvr2-config.sh --cflags --libs`

clean: 
	rm -f basic comparisons

rebuild: clean all
