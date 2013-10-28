#include "Game_Client.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

#define WINDOW_WIDTH 540
#define WINDOW_HEIGHT  540
#define WINDOW_POS  100

#define ASCII_CTRL_C  3
#define ASCII_BACKSPACE  540
#define ASCII_ENTER  13
#define ASCII_ESC  27

#define TEXT_BUFF_SIZE 64

std::vector<char> type_text;


Game_Client gc;

//drawing functions
void gui_init();
void gui_render_grid();
void gui_reshape(int width, int height);
void gui_keyboard(unsigned char c, int x, int y);
void gui_mouse(int button, int state, int x, int y);
void gui_move(int x, int y);

//auxiliary functions
std::string convert(int x, int y);
void drawGrid(int x, int y, bool is_hovered);
void drawSurface(int x, int y, bool is_hovered);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	gc = Game_Client();

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowPosition(WINDOW_POS, WINDOW_POS);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("My First Shit");
	gui_init();
	glutDisplayFunc(gui_render_grid);
	glutReshapeFunc(gui_reshape);
	glutKeyboardFunc(gui_keyboard);
	glutMouseFunc(gui_mouse);
	glutPassiveMotionFunc(gui_move);


	glutMainLoop();
}

 void gui_init()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);	
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


}

void gui_render_grid() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(-4.0f,-3.0f,-20.0f);

	//drawing grids
	vector<vector<Piece>> p = gc.getBoard();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);

	for(int i = 0; i < p.size(); i ++)
	{
		for(int j = 0; j < p.at(i).size(); j ++)
		{
			if(p.at(i).at(j).my_state == EMPTY || 
				p.at(i).at(j).my_state == LEGAL_YELLOW ||
				p.at(i).at(j).my_state == LEGAL_BLACK ||
				p.at(i).at(j).my_state == LEGAL_BOTH)
				continue;

			if(p.at(i).at(j).my_state == YELLOW)
				glColor3f(1.0, 1.0, 0.2);
			else	
				glColor3f(0.0, 0.0, 0.0);

			drawSurface(p.at(i).at(j).pos.x, p.at(i).at(j).pos.y, p.at(i).at(j).is_hovered);
		}
	}

	glEnd();

	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_QUADS);

	for(int i = 0; i < p.size(); i ++)
		for(int j = 0; j < p.at(i).size(); j ++)
		{
// 			if(p.at(i).at(j).my_state == (State)(gc.getColor() + 2)) // potential move
// 				glColor3f(1.0, 0.4, 1.0);
// 			else
// 				glColor3f(1, 0, 0);

			glColor3f(1.0, 0.4, 1.0);

			drawGrid(p.at(i).at(j).pos.x, p.at(i).at(j).pos.y, p.at(i).at(j).is_hovered);

			
		}

	glEnd();

	
	glutSwapBuffers();
	glutPostRedisplay();

}

void gui_reshape(int width, int height)
{
	// If resize, set size back to default.
	// DISALLOWS WINDOW RESIZING
	if (height==0)					
	{
		height=1;						
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();							


	gluPerspective(35.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);						
	glLoadIdentity();	
}
 
 
 void gui_keyboard(unsigned char key, int x, int y) {
 	switch (key) {
 	case ASCII_CTRL_C:
 	case ASCII_ESC:
 		exit(0);
 		break;
 	case ASCII_BACKSPACE:
 		if (!type_text.empty()) {
 			type_text.pop_back();
 		}
 		break;
 	case ASCII_ENTER:
 		//SEND COMMAND TO BACKEND
 		type_text.clear();
 		break;
 	case '~':
//  		if (isSplash) {
//  			isSplash = false;
//  		}
//  		else {
//  			isSplash = true;
//  		}
 		break;
 	default:
 		if (type_text.size() > TEXT_BUFF_SIZE) {
 			return;
 		}
 		if (isalpha(key) || isdigit(key) || ispunct(key) || isspace(key)) {
 			type_text.push_back(key);
 		}
 		break;
 	}
 }
 
 void gui_mouse(int button, int state, int x, int y) {
 	if (button == GLUT_RIGHT_BUTTON) {
 		exit(0);
 	}
 	if (button == GLUT_LEFT_BUTTON) {
		if(x > 100 && x < 440 && y > 55 && y < 395)
		{
			x -= 100; y -= 55;
			x /= 42.5; y /= 42.5;
		}
			gc.update(x, 7 - y);
 
 	}
 }
 
 void gui_move(int x, int y)
 {
	 for(int i = 0; i < GRID_SIZE; i ++)
	 {
		 for(int j = 0; j < GRID_SIZE; j ++)
		 {
			 gc.myboard.at(i).at(j).is_hovered = false;
		 }
	 }

 	if(x > 100 && x < 440 && y > 55 && y < 395)
	{
		x -= 100; y -= 55;
		x /= 42.5; y /= 42.5;

		gc.myboard.at(x).at(7 - y).is_hovered = true;

	}
 }
 
std::string convert(int x, int y)
{
	std::string s = ""; 
	std::stringstream ss;
	ss << y;
	ss >> s;
	s += (char)(x+97);
	char a = s[0];
	s[0] = s[1];
	s[1] = a;
	//Quick and dirty: Never ever ever ever do this.
	//Quick and dirty: Never ever ever ever do this.
	return s;
}

void drawGrid(int x, int y, bool is_hovered)
{
	float z;

	if(is_hovered)
		z = - 0.5f;
	else
		z = 0.0f;
	glVertex3f(x, y, z);
	glVertex3f(x, y + GRID_WIDTH, z);
	glVertex3f(x  + GRID_LENGTH, y + GRID_WIDTH, z);
	glVertex3f(x + GRID_LENGTH, y, z);
}

void drawSurface(int x, int y, bool is_hovered)
{
	float z;

	if(is_hovered)
		z = - 0.5f;
	else
		z = 0.0f;
	

	glVertex3f(x , y + 0.01, 0);
	glVertex3f(x, y + GRID_WIDTH, 0);
	glVertex3f(x  + GRID_LENGTH, y + GRID_WIDTH, 0);
	glVertex3f(x + GRID_LENGTH , y , 0);
}
