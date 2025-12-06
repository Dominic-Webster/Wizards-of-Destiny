CC = g++
CFLAGS = -g -Wall -std=c++11

play: game.o spell.o player.o item.o
	$(CC) $(CFLAGS) game.o spell.o player.o item.o -o play

game.o: game.cc player.h item.h
	$(CC) -c $(CFLAGS) game.cc -o game.o

spell.o: spell.cc spell.h
	$(CC) -c $(CFLAGS) spell.cc -o spell.o

item.o: item.cc item.h
	$(CC) -c $(CFLAGS) item.cc -o item.o

player.o: player.cc player.h spell.h
	$(CC) -c $(CFLAGS) player.cc -o player.o

clean:
	rm -f *.o play	