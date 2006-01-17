#!/bin/sh
# $Id$
# This scripts reports the names of every class contained in this source distribution
#


egrep 'class.*{' *.h | cut -f2 -d: | tr -d '\t' | sed 's/class //' | tr -d '{' | sort -u
