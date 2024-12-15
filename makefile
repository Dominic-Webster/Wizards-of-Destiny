CC = g++
CFLAGS = -g -Wall -std=c++11

play: spell.h game.o spell.o
	$(CC) $(CFLAGS) game.o spell.o -o play

game.o: game.cc spell.h
	$(CC) -c $(CFLAGS) game.cc -o game.o

spell.o: spell.cc spell.h
	$(CC) -c $(CFLAGS) spell.cc -o spell.o

clean:
	rm spell.o game.o	