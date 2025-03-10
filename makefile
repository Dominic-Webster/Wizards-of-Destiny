CC = g++
CFLAGS = -g -Wall -std=c++11

play: spell.h item.h game.o spell.o item.o
	$(CC) $(CFLAGS) game.o spell.o item.o -o play

game.o: game.cc spell.h
	$(CC) -c $(CFLAGS) game.cc -o game.o

spell.o: spell.cc spell.h
	$(CC) -c $(CFLAGS) spell.cc -o spell.o

item.o: item.cc item.h
	$(CC) -c $(CFLAGS) item.cc -o item.o

clean:
	rm spell.o game.o item.o	