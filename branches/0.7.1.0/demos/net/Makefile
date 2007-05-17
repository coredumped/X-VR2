CC=g++
DEBUG=-gstabs+

all: resolver simple_udpreceiver simple_udpsender udpclient udpserver

resolver: resolver.cpp
	$(CC) $(DEBUG) -o resolver resolver.cpp `pkg-config xvr2net --cflags --libs`

simple_udpreceiver: simple_udpreceiver.cpp
	$(CC) $(DEBUG) -o simple_udpreceiver simple_udpreceiver.cpp `pkg-config xvr2net --cflags --libs`

simple_udpsender: simple_udpsender.cpp
	$(CC) $(DEBUG) -o simple_udpsender simple_udpsender.cpp `pkg-config xvr2net --cflags --libs`

udpclient: udpclient.cpp
	$(CC) $(DEBUG) -o udpclient udpclient.cpp `pkg-config xvr2net --cflags --libs`

udpserver: udpserver.cpp
	$(CC) $(DEBUG) -o udpserver udpserver.cpp `pkg-config xvr2net --cflags --libs`

clean: 
	rm -f resolver simple_udpreceiver simple_udpsender udpclient udpserver

rebuild: clean all
