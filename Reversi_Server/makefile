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
#	gsetest - runs unit tests for Gamestate_Engine class
#	gserv_test - runs unit tests for Game_Server class
#	gai_test - runs unit tests for AI class
#
#	I WILL ADD MORE SHIT TO THE MAKEFILE AS WE GO -WES
#

CC=g++

all: gse_test gai_test gserv_test

game_state_engine.o: game_state_engine.h game_state_engine.cpp
	$(CC) -c -g game_state_engine.cpp
	
gse_test: gse_test.cpp game_state_engine.o
	$(CC) -o gse_test gse_test.cpp game_state_engine.o
	
ai.o: ai.h ai.cpp
	$(CC) -c -g ai.cpp
	
gai_test: gai_test.cpp ai.o
	$(CC) -o gai_test gai_test.cpp ai.o	
	
game_server.o: game_server.h game_server.cpp
	$(CC) -c -g game_server.cpp

gserv_test: gserv_test.cpp game_server.o ai.o game_state_engine.o
	$(CC) -o gserv_test gserv_test.cpp game_server.o ai.o game_state_engine.o

clean:
	/bin/rm -rf *.o gse_test
	/bin/rm -rf *.o gserv_test
	/bin/rm -rf *.o gai_test
	
	