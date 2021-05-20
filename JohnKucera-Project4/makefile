compile: scanner.o parser.o listing.o types.o
	g++ -o compile scanner.o parser.o listing.o types.o

scanner.o: scanner.c types.h listing.h tokens.h
	g++ -c scanner.c

scanner.c: scanner.l
	flex scanner.l
	cp lex.yy.c scanner.c

parser.o: parser.c types.h listing.h symbols.h
	g++ -c parser.c

parser.c tokens.h: parser.y
	bison -d -v parser.y
	cp parser.tab.c parser.c
	cp parser.tab.h tokens.h

listing.o: listing.cc listing.h
	g++ -c listing.cc

types.o: types.cc types.h
	g++ -c types.cc
