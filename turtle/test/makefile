CFLAGS = `pkg-config sdl2 --cflags` -O2 -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm
INCS = interp.h 
LIBS =  `pkg-config sdl2 --libs`
CC = gcc


all: test testerror testexit1 testexit2 testdrawline

test: neillsdl2.c interp.c test.c $(INCS)
	$(CC) neillsdl2.c interp.c test.c -o test $(CFLAGS) $(LIBS)

testerror: neillsdl2.c interp.c testerror.c $(INCS)
	$(CC) neillsdl2.c interp.c testerror.c -o testerror $(CFLAGS) $(LIBS)

testexit1: neillsdl2.c interp.c testexit1.c $(INCS)
	$(CC) neillsdl2.c interp.c testexit1.c -o testexit1 $(CFLAGS) $(LIBS)

testexit2: neillsdl2.c interp.c testexit2.c $(INCS)
	$(CC) neillsdl2.c interp.c testexit2.c -o testexit2 $(CFLAGS) $(LIBS)

testdrawline: neillsdl2.c interp.c testdrawline.c $(INCS)
	$(CC) neillsdl2.c interp.c testdrawline.c -o testdrawline $(CFLAGS) $(LIBS)


clean:
	rm -f all

run: all
	./test 
	./testerror 
	./testexit1
	./testexit2
	./testdrawline


