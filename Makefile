# $Id: Makefile,v 1.19 2016-08-18 15:05:42-07 - - $

MKFILE  = Makefile
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}
CPP       = g++ -g -O0 -Wall -Wextra -std=gnu++14
MKDEPS    = g++ -MM -std=gnu++14
GRIND     = valgrind --leak-check=full --show-reachable=yes

BISON = bison --defines=${PARSEHDR} --output=${PARCECPP}

HDRSRC = astree.h auxlib.h lyutils.h string_set.h
CPPSRC = astree.cpp auxlib.cpp lyutils.cpp string_set.cpp main.cpp
LSOURCES  = scanner.l
YSOURCES  = parser.y 
HYGEN     = yyparse.h 
CLGEN     = yylex.cpp
CYGEN     = yyparse.cpp 
CGENS     = ${CLGEN} ${CYGEN}
ALLGENS   = ${LEXHDR} ${HYGEN} ${CGENS}
EXECBIN   = oc
LREPORT   = yylex.output 
YREPORT   = yyparse.output 
MODULES   = astree lyutils string_set auxlib 
HDRSRC    = ${MODULES:=.h}
CPPSRC    = ${MODULES:=.cpp} main.cpp
LEXHDR    = yylex.h
ALLCSRC   = ${CPPSRC} ${CGENS}
OBJECTS   = ${ALLCSRC:.cpp=.o}
REPORTS   = ${LREPORT} ${YREPORT}
MODSRC    = ${foreach MOD, ${MODULES}, ${MOD}.h ${MOD}.cpp}
MISCSRC   = ${filter-out ${MODSRC}, ${HDRSRC} ${CPPSRC}}
ALLSRC    = README ${LSOURCES} ${YSOURCES} ${MODSRC} ${MISCSRC} Makefile
TESTINS   = ${wildcard test*.in}
EXECTEST  = ${EXECBIN} -ly
LISTSRC   = ${ALLSRC} ${DEPSFILE} ${HYGEN}

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${CPP} -o${EXECBIN} ${OBJECTS}

${OBJECTS} : ${CPPSRC} ${CGENS}
	${CPP} -c ${CPPSRC}
	${CPP} -c {CGENS}

%.o : %.cpp
	${CPP} -c $<


ci : ${ALLSRC} ${TESTINS}
	- checksource ${ALLSRC}
	- cpplint.py.perl ${CPPSRC}
	cid + ${ALLSRC} ${TESTINS} test?.inh

lis : ${LISTSRC} tests
	mkpspdf List.source.ps ${LISTSRC}
	mkpspdf List.output.ps ${REPORTS} \
		${foreach test, ${TESTINS:.in=}, \
		${patsubst %, ${test}.%, in out err log}}

clean :
	- rm ${OBJECTS} ${ALLGENS} ${REPORTS} ${DEPSFILE} core
	- rm ${foreach test, ${TESTINS:.in=}, \
		${patsubst %, ${test}.%, out err log}}

spotless : clean
	- rm ${EXECBIN} 

dep : ${ALLCSRC}
	@ echo "# ${DEPSFILE} created `date` by ${MAKE}" >${DEPSFILE}
	${MKDEPS} ${ALLCSRC} >>${DEPSFILE}

${CLGEN} : ${LSOURCES}
	flex --outfile=${CLGEN} ${LSOURCES} 2>${LREPORT}
	- grep -v '^ ' ${LREPORT}

${CYGEN} ${HYGEN} : ${YSOURCES}
	bison --defines=${HYGEN} --output=${CYGEN} ${YSOURCES}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${MAKE} --no-print-directory deps

tests : ${EXECBIN}
	touch ${TESTINS}
	make --no-print-directory ${TESTINS:.in=.out}

%.out %.err : %.in
	${GRIND} --log-file=$*.log ${EXECTEST} $< 1>$*.out 2>$*.err; \
	echo EXIT STATUS = $$? >>$*.log

again :
	gmake --no-print-directory spotless deps ci all lis
	
ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif

