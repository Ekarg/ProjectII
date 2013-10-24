
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "game_client.h"


void gui_run();
void gui_render_grid();
void gui_reshape(int width, int height);
void gui_keyboard(unsigned char c, int x, int y);
void gui_mouse(int button, int state, int x, int y);

std::vector<char> type_text;

void Game_Client::run_gui() {
	gui_run();
}

//GUI STUFF

int const WINDOW_WIDTH = 540;
int const WINDOW_HEIGHT = 540;
int const WINDOW_POS = 100;

int const ASCII_CTRL_C = 3;
int const ASCII_BACKSPACE = 8;
int const ASCII_ENTER = 13;
int const ASCII_ESC = 27;

int const GRID_SIZE = 8;
int const TEXT_BUFF_SIZE = 64;

bool isSplash = true;

void gui_run () {
	//ugly ass hack because we have no real argc/argv since this isn't main
	char fakeParam[] = "fake";
	char *fakeargv[] = { fakeParam, NULL };
	//don't do this
	int fakeargc = 1;
	
	glutInit( &fakeargc, fakeargv );

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowPosition(WINDOW_POS, WINDOW_POS);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("My First Shit");
	glutDisplayFunc(gui_render_grid);
	glutReshapeFunc(gui_reshape);
	glutKeyboardFunc(gui_keyboard);
	glutMouseFunc(gui_mouse);
	
	glutMainLoop();
}

void gui_render_grid() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		for (GLfloat i = -1; i <= 1; i += (2.0/GRID_SIZE)) {
			glVertex3f(i, 1, 0); glVertex3f(i, -1, 0);
			//columns going left to right
			glVertex3f(1, i, 0); glVertex3f(-1, i, 0);
			//rows going bottom to top
		}
	glEnd();
	

//START SPLASH
if (isSplash) {
	static float alpha = 0;
	glRotatef(15, 1, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(alpha, 0, 1, 0);

	// We tell we want to draw quads
	glBegin(GL_QUADS);

	// Every four calls to glVertex, a quad is drawn
	glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1); glVertex3f(-1, -1,  1);
	glColor3f(0, 1, 1); glVertex3f(-1,  1,  1);
	glColor3f(0, 1, 0); glVertex3f(-1,  1, -1);

	glColor3f(1, 0, 0); glVertex3f( 1, -1, -1);
	glColor3f(1, 0, 1); glVertex3f( 1, -1,  1);
	glColor3f(1, 1, 1); glVertex3f( 1,  1,  1);
	glColor3f(1, 1, 0); glVertex3f( 1,  1, -1);

	glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1); glVertex3f(-1, -1,  1);
	glColor3f(1, 0, 1); glVertex3f( 1, -1,  1);
	glColor3f(1, 0, 0); glVertex3f( 1, -1, -1);

	glColor3f(0, 1, 0); glVertex3f(-1,  1, -1);
	glColor3f(0, 1, 1); glVertex3f(-1,  1,  1);
	glColor3f(1, 1, 1); glVertex3f( 1,  1,  1);
	glColor3f(1, 1, 0); glVertex3f( 1,  1, -1);

	glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
	glColor3f(0, 1, 0); glVertex3f(-1,  1, -1);
	glColor3f(1, 1, 0); glVertex3f( 1,  1, -1);
	glColor3f(1, 0, 0); glVertex3f( 1, -1, -1);

	glColor3f(0, 0, 1); glVertex3f(-1, -1,  1);
	glColor3f(0, 1, 1); glVertex3f(-1,  1,  1);
	glColor3f(1, 1, 1); glVertex3f( 1,  1,  1);
	glColor3f(1, 0, 1); glVertex3f( 1, -1,  1);

	// No more quads
	glEnd();

	std::vector<std::string> splash_text;
	splash_text.push_back("Reversi Project");
	splash_text.push_back("Grace Coffman");
	splash_text.push_back("Sidian Wu");
	splash_text.push_back("Alejandro Vega");
	splash_text.push_back("Violeta Torres");
	splash_text.push_back("Wesley Tang");
	
	//glRasterPos3f(-1, -1, -1);
	for (int k = 0; k < splash_text.size(); ++k) {
		for (int i = 0; i < splash_text[k].size(); ++i) {
			glColor3f(rand()%2, rand()%2, rand()%2);
			//	 RANDOM COLORS YOOOOO!!!!
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, splash_text[k][i]);
		}
		glRotatef(alpha, 0, 1, 0);
		glRasterPos3f(-1, (1-k), -1);
	}
	// Rotate a bit more
	alpha = alpha + 5;
 }
//STOP SPLASH
	
	glRasterPos2f(-1, -0.98);
	glColor3f(1, 1, 1);
	for (int j = 0; j < type_text.size(); ++j) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, type_text[j]);
	}

	glutSwapBuffers();
	glutPostRedisplay();
}

void gui_reshape(int width, int height)
{
	// If resize, set size back to default.
	// DISALLOWS WINDOW RESIZING
	if( width != WINDOW_WIDTH || height != WINDOW_HEIGHT ) {
		glutReshapeWindow( WINDOW_WIDTH, WINDOW_HEIGHT);
	}
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
		//on first click, close splash screen
		if (isSplash) { isSplash = false; }
		//send move based on coordinates
		GLfloat scaled_x = ((float)x/WINDOW_WIDTH)* GRID_SIZE;
		GLfloat scaled_y = ((float)y/WINDOW_HEIGHT)* GRID_SIZE;
		std::cout << scaled_y <<"     " << scaled_x << '\n';
	}
}