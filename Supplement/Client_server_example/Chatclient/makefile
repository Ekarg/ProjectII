# --- macros
#CC=gcc
#CFLAGS=  -O3 -I /usr/local/lib/sprng/include -I /usr/local/lib/pgplot -g
OBJECTS= client.o master.o sbcp.o
#LIBS = -L/usr/local/lib/sprng/lib -llcg -L/usr/local/lib/pgplot -lcpgplot -lpgplot -lX11 -lftn -lm


# --- targets
all:    client

#chat: list.o
#	gcc list.o -o chat 
#list.o: list.c
#	gcc -c list.c
client:   master.o client.o sbcp.o
	gcc client.o master.o sbcp.o -o client

master.o: master.h master.c
	gcc -c master.c master.h
client.o: master.h client.c
	gcc -c client.c master.h
sbcp.o: master.h sbcp.c
	gcc -c sbcp.c master.h
 

# --- remove binary and executable files
clean:
	rm -f client $(OBJECTS)

