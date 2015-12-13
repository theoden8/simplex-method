OBJECTS   = main.cpp Matrix.cpp Window.cpp
LIBRARIES = Matrix.hpp Window.hpp
BIN       = _matrix
CXX       = g++ -std=c++0x -Wno-deprecated
CXXFLAGS  = -std=c++0x -O3 -Wno-deprecated -o "$(BIN)" -framework OpenGL -framework GLUT

all : $(OBJECTS) $(LIBRARIES)
	$(CXX) $(CXXFLAGS) $(OBJECTS)

run :
	./"$(BIN)"

