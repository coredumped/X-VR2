# $Id:Makefile.am 544 2007-08-27 18:14:47Z mindstorm2600 $

doc_PROGRAMS = embedded-sql rdbms

embedded_sql_SOURCES = embedded-sql.cpp

rdbms_SOURCES = rdbms.cpp

INCLUDES = -I$(top_srcdir) -I../../Core/xvr2 -I../../Text/xvr2 -I../xvr2 

rebuild: clean all

LDADD = ../../Core/xvr2/libxvr2core.la ../xvr2/libxvr2sql.la
