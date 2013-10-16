# --- macros
#CC=gcc
#CFLAGS=  -O3 -I /usr/local/lib/sprng/include -I /usr/local/lib/pgplot -g
OBJECTS= server.o master.o sbcp.o list.o
#LIBS = -L/usr/local/lib/sprng/lib -llcg -L/usr/local/lib/pgplot -lcpgplot -lpgplot -lX11 -lftn -lm


# --- targets
all:    server

server:   master.o server.o sbcp.o list.o
	gcc master.o server.o sbcp.o list.o -o server

master.o: master.h master.c 
	gcc -c master.h master.c 
sbcp.o: master.h sbcp.c
	gcc -c master.h sbcp.c
server.o: master.h server.c
	gcc -c master.h server.c
list.o: master.h list.c
	gcc -c master.h list.c

# --- remove binary and executable files
clean:
	rm -f server $(OBJECTS)

