PROJECT II - REVERSI
CSCE 315-503
FALL 2013
	-BY-
Grace Coffman
Sid Wu
Alejandro Vega
Wesley Tang

Simple Interface Between Client and Server
- Client 1 sends command to server
- Server processes command and updates boardstate accordingly
- Process Client 2 or AI
- Server sends boardstate to Client 1
- Client 1 updates GUI
- Rinse -> repeat.

AI
	-AI receives boardstate
	-Tree structure is created
	-AI search algorithm with applied difficulty mod
	-AI returns selected move

Client 2
	-Server waits for selected move
	-Timeout if no move is selected reasonably quick

GUI
	-I would suggest OpenGL.
	- Anything but FLTK, really. 
	

Supplement
	
/tree.hh
- Third party STL-style tree class
- http://tree.phi-sci.com/

/Client_server_example/*
- Contains server-client communication example based on online chat system
- I pretty much tracked down a grad student and made him explain server 
  client communication to me until I understood and these are the files 
  he explained from. -Wes

/Beej_Guide_To_Sockets.pdf
- Self help guide to basic socket programming
- Damned helpful

