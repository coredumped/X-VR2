# $Id$

doc_PROGRAMS = uritest

uritest_SOURCES = uritest.cpp

INCLUDES = -I$(top_srcdir) -I../../Core/xvr2 -I../../Text/xvr2 -I../xvr2 

rebuild: clean all

LDADD = ../../Core/xvr2/libxvr2core.la ../xvr2/libxvr2net.la  -lssl -lcrypto
