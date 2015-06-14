#include <GLUT/glut.h>

#include <cstdlib>
#include <iostream>

#include "Window.hpp"

//Window *black_screen;
//
//void Display	()					{ black_screen->Display	();			 }
//void Reshape	(int NEW_WIDTH, int NEW_HEIGHT)		{ black_screen->Reshape	(NEW_WIDTH, NEW_HEIGHT); }
//void Keyboard	(unsigned char key, int x, int y)	{ black_screen->Keyboard(key, x, y);		 }
//void Special	(int key, int x, int y)			{ black_screen->Special	(key, x, y);		 }

int main(int argc, char **argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//
//	black_screen = new Window(800, 800);
//
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	glutDisplayFunc		(	Display		);
//	glutReshapeFunc		(	Reshape		);
//	glutKeyboardFunc	(	Keyboard	);
//	glutSpecialFunc		(	Special		);
//	black_screen->AddMatrix(Matrix({
//		{1, 0, 0, 0, 0},
//		{2, 0, 0, 0, 0},
//		{3, 0, 0, 0, 0},
//		{4, 0, 0, 0, 0},
//		{5, 0, 0, 0, 0},
//	}));

	Matrix A({
		{ 5,  8,  1, 20, 15},
		{ 4,  0,  2, 3,  8},
		{ 8,  9,  3, 13,  6},
	});
	Matrix::line_t C =
		{ -9, -1,  5, 0, };
	A.GetOptimizedMinimum(C);
//	black_screen->Display(A);
//	black_screen->Display(A.GetOptimizedMinimum(C));

//	Display();

//	glutMainLoop();
}
