all: simple xvr2grep

simple: simple.cpp 
	c++ -g -o simple simple.cpp `xvr2-config.sh --cflags --libs`

xvr2grep: xvr2grep.cpp 
	c++ -g -o xvr2grep xvr2grep.cpp `xvr2-config.sh --cflags --libs`

clean:
	rm -f xvr2grep simple

rebuild: clean all
