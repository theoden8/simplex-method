OBJECTS		= main.cpp Window.cpp Matrix.cpp
LIBRARIES	= Window.hpp Matrix.hpp

all :  $(OBJECTS) $(LIBRARIES)
	g++ -std=c++11 -Wno-deprecated $(OBJECTS) -o "_matrix" -framework OpenGL -framework GLUT

v :  $(OBJECTS) $(LIBRARIES)
	g++ -v -std=c++11 $(OBJECTS) -o "_matrix" -framework OpenGL -framework GLUT

compile :
	g++ -std=c++11 "main.cpp" -o "_matrix" -framework OpenGL -framework GLUT

run :
	./_matrix

remake :
	cd "_MakeGen"; perl "_make_gen.pl" ".." "main.cpp" "_matrix"; cd ".."

open :
	vim -p *hpp*
