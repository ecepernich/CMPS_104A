# $Id: Makefile,v 1.2 2016-10-10 22:37:15-07 - - $
# Elizabeth Cepernich
# eceperni/1316976

GPP      = g++ -std=gnu++14 -g -O0 -Wall -Wextra
MKDEP    = g++ -std=gnu++14 -MM

MKFILE   = Makefile
DEPFILE  = Makefile.dep
SOURCES  = string_set.cpp main.cpp auxlib.cpp
HEADERS  = string_set.h auxlib.h
OBJECTS  = ${SOURCES:.cpp=.o}
EXECBIN  = oc
SRCFILES = ${HEADERS} ${SOURCES} ${MKFILE}

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GPP} ${OBJECTS} -o ${EXECBIN}

%.o : %.cpp
	${GPP} -c $<

ci :
	cid + ${SRCFILES}

clean :
	-rm ${OBJECTS} ${DEPFILE}

spotless : clean
	- rm ${EXECBIN}

${DEPFILE} :
	${MKDEP} ${SOURCES} >${DEPFILE}

deps :
	- rm ${DEPFILE}
	${MAKE} --no-print-directory ${DEPFILE}

include ${DEPFILE}

test : ${EXECBIN}
	${EXECBIN} * * * >test.out 2>&1

lis : test
	mkpspdf Listing.ps ${SRCFILES} ${DEPFILE} test.out

again : ${SRCFILES}
