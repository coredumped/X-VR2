CC=g++
DEBUG=-gstabs+

all: context

context: context.cpp
	$(CC) $(DEBUG) -o context context.cpp `pkg-config xvr2net --cflags --libs`

clean: 
	rm -f context

rebuild: clean all
