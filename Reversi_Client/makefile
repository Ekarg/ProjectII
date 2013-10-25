
# 			MAKEFILE 
#		  CSCE 315-503
#		REVERSI Project
#		   Fall 2013
#		  --Authors--
#		 Grace Coffman
#	   	 Alejandro Vega
#	 	   Sidian Wu
#		 Violeta Torres
#		  Wesley Tang



CC=g++

all: client_main

game_state_engine.o: game_state_engine.h Position.h game_state_engine.cpp
	$(CC) -c -g game_state_engine.cpp
	
game_client.o: game_client.h game_client.cpp game_state_engine.o
	$(CC) -c -g game_client.cpp game_state_engine.o

client_main: main.cpp game_client.o game_state_engine.o
	$(CC) -o main main.cpp game_client.o game_state_engine.o -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm -lsocket -lnsl
	
clean:
	/bin/rm -rf *.o client_main
	
	