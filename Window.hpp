#pragma once

#include <vector>

#include "Matrix.hpp"

class Window {
	std::vector <Matrix> matrices_;
	float WIDTH_, HEIGHT_,
	      SIZE_X_, SIZE_Y_;
	const char *NAME_;
	std::pair <int, std::pair <size_t, size_t> > selection_;
	bool edit;
public:
	Window		(const float WIDTH, const float HEIGHT);
private:
	void Type	(const float x, const float y, const char *string) const;
	void Highlight	(const float x, const float y) const;
public:
	void AddMatrix	(const Matrix &A);
	void Display	(const Matrix &A);
	void Display	();
	void Reshape	(int NEW_WIDTH, int NEW_HEIGHT);
	void Keyboard	(unsigned char key, int x, int y);
	void Special	(int key, int x, int y);
};
