#include <GLUT/glut.h>

#include <cmath>
#include <string>
#include <iostream>

#include "Window.hpp"

Window::Window			(const float WIDTH, const float HEIGHT) :
	WIDTH_(WIDTH), HEIGHT_(HEIGHT),
	SIZE_X_(800), SIZE_Y_(800),
	NAME_("MATRIX"),
	selection_(std::make_pair(0, std::make_pair(0, 0))),
	edit(false)
{
	glutInitWindowSize(SIZE_X_, SIZE_Y_);
	glutCreateWindow(NAME_);
}

void	Window::Type		(const float x, const float y, const char *str) const {
	glRasterPos2f(x, y);
	for (const char *c = str; *c != '\0'; ++c) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void	Window::Highlight(const float x, const float y) const {
	const float BOLD = 12;
	glPushMatrix();
	glTranslatef(x + BOLD * 0.55, y + BOLD * 0.60, 0);
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
		glVertex3f( +3.0 * BOLD, +BOLD, 0.0);
		glVertex3f( +3.0 * BOLD, -BOLD, 0.0);
		glVertex3f( -BOLD, -BOLD, 0.0);
		glVertex3f( -BOLD, +BOLD, 0.0);
	glEnd();
	glPopMatrix();
	glColor3f(0.0f,0.0f,0.0f);
}

void	Window::AddMatrix	(const Matrix &new_matrix) {
//	Matrix	lines	= new_matrix,
//		columns	= new_matrix,
//		transp	= new_matrix.Transpose();
//	lines.Swap_Lines(0, 1);
//	columns.Swap_Columns(0, 1);
	matrices_.push_back(new_matrix);
//	matrices_.push_back(lines);
//	matrices_.push_back(columns);
//	matrices_.push_back(transp);
}

void	Window::Write(const std::string &message) {
	std::cerr << "\x1b[033;96m[\t\x1b[033;93m" << message << "\x1b[033;0m" << std::endl;
}

void	Window::Display		() {
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, WIDTH_, 0, HEIGHT_, 1, -1);

	const size_t D = 80;
	size_t maxwidth = 0;
	float corner_x = 20;
	float corner_y = HEIGHT_ - 30 + 2 * D;
	size_t select_M(0), select_y, select_x;
	for(auto &matr : matrices_) {
		size_t
			width	= matr.GetGrid().front().size(),
			height	= matr.GetGrid().size();

		maxwidth = std::max(maxwidth, width);
		if (corner_y - height * D <= 0) {
			corner_x += (2 + maxwidth) * D;
			corner_y = HEIGHT_ - 30;
		} else
			corner_y -= 2.0 * D;

		if(corner_x + width * D >= WIDTH_)
			break;

		select_y = 0;
		for(auto matr_y : matr.GetGrid()) {
			float new_corner_x = corner_x;
			select_x = 0;
			for(auto matr_xy : matr_y) {
				glColor3f(0.0f,1.0f,0.0f);
				if(
					select_M == selection_.first		&&
					select_y == selection_.second.first	&&
					select_x == selection_.second.second
				)
					Highlight(corner_x, corner_y);
				std::string number = std::to_string(matr_xy);
				number.erase(number.find_last_not_of('0') + 2, std::string::npos);
				Type(corner_x, corner_y, number.c_str());
				corner_x += D;
				++select_x;
			}
			corner_x = new_corner_x;
			corner_y -= D;
			++select_y;
		}
		++select_M;
	}
	glColor3f(1.0f,1.0f,0.0f);
	Type(corner_x, corner_y, ". . .");
	glColor3f(0.2f,1.0f,1.0f);
	if(edit)
		Type(WIDTH_ - 100, HEIGHT_ - 50, std::string("EDIT").c_str());

	glutSwapBuffers();
}

void	Window::Reshape		(int NEW_SIZE_X, int NEW_SIZE_Y) {
	WIDTH_	*= double(NEW_SIZE_X) / SIZE_X_;
	HEIGHT_ *= double(NEW_SIZE_Y) / SIZE_Y_;
	SIZE_X_ = NEW_SIZE_X;
	SIZE_Y_ = NEW_SIZE_Y;

	glViewport(0, 0, SIZE_X_, SIZE_Y_);
	glutPostRedisplay();
}

void	Window::Keyboard	(unsigned char key, int x, int y) {
	Matrix::val_t *selected = &matrices_[selection_.first][selection_.second.first][selection_.second.second];
	switch(key) {
		case 27:
		case 'Q':
			exit(0);
			break;
		case 'q':
			if(edit)
				edit = !edit;
			else
				exit(0);
			break;
		case 'g':
			matrices_.front() = matrices_.front().Gauss();
			break;
		case 'i':
			AddMatrix(matrices_.front().Invert());
			std::cout << "\n\x1b[033;41m\x1b[033;1m\x1b[033;97m[     FLAG     ]\x1b[033;0m\n\n";
			break;
		case 'p':
			if(matrices_.size())
				matrices_.pop_back();
			break;
		case '*':
			if(matrices_.size() >= 2)
				AddMatrix(matrices_[0] * matrices_[1]);
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if(edit)
				*selected = 10 * *selected + key - '0';
			else
				AddMatrix(Matrix(key - '0'));
			break;
		case '0':
			if(edit)
				*selected *= 10;
			else {
				Write("\x1b[033;1m\x1b[033;91mType here the wanted size of matrix, little brat: ");
				int size;
				scanf("%d", &size);
				AddMatrix(size);
			}
			break;
		case '\t':
			++selection_.first %= matrices_.size();
			break;
		case 'c':
			edit = !edit;
			break;
		case 'x':
			if(edit)
				*selected = 0;
			break;
		case 127:
			if(edit)
				*selected = long(*selected) / 10;
			break;
		case '=':
			if(edit)
				++*selected;
			break;
		case '-':
			if(edit)
				--*selected;
			else
				matrices_.pop_back();
			break;
	}
	Display();
}

void	Window::Special		(int key, int x, int y)	{
	size_t height	= matrices_[selection_.first].GetGrid().size();
	size_t width	= matrices_[selection_.first].GetGrid().front().size();
	switch(key) {
		case 100 :
//			Keyboard('a', x, y);
			selection_.second.second	= (selection_.second.second) ?	selection_.second.second % width  - 1	:	width - 1;
			break;
		case 101 :
//			Keyboard('w', x, y);
			selection_.second.first		= (selection_.second.first) ?	selection_.second.first  % height - 1	:	height - 1;
			break;
		case 102 :
//			Keyboard('d', x, y);
			++selection_.second.second	%= width;
			break;
		case 103 :
//			Keyboard('s', x, y);
			++selection_.second.first	%= height;
			break;
	}
	Display();
}
