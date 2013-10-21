# 			MAKEFILE 
#		  CSCE 315-503
#		REVERSI Project
#		   Fall 2013
#		  --Authors--
#		 Grace Coffman
#	   	 Alejandro Vega
#	 	   Sidian Wu
#		  Wesley Tang

#
#	I WILL ADD MORE SHIT TO THE MAKEFILE AS WE GO -WES
#

CC=g++

all: client_main

game_client.o: game_client.h game_client.cpp
	$(CC) -c -g game_client.cpp -lGL -lglut -lX11 -lXext

client_main: main.cpp game_client.o
	$(CC) -o main main.cpp game_client.o -lGL -lglut -lX11 -lXext
	
clean:
	/bin/rm -rf *.o client_main	
	
	