# $Id$

doc_PROGRAMS = vector-test string-basics pipeline-test

vector_test_SOURCES = vector-test.cpp

string_basics_SOURCES = string-basics.cpp

pipeline_test_SOURCES = pipeline-test.cpp

INCLUDES = -I$(top_srcdir) -I../../Core/xvr2 -I../xvr2 

rebuild: clean all

LDADD = ../../Core/xvr2/libxvr2core.la
