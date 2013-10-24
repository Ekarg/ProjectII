
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

game_client.o: game_client.h game_client.cpp
	$(CC) -c -g game_client.cpp

client_main: main.cpp game_client.o
	$(CC) -o main main.cpp game_client.o -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm
	
clean:
	/bin/rm -rf *.o client_main
	
	