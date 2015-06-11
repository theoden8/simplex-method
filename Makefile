SHELL     = /bin/bash
CPP       = g++ -std=c++0x -Wno-deprecated
CPPFLAGS  = -framework OpenGL -framework GLUT
BIN       = _matrix
OBJECTS   = main.cpp Matrix.cpp Window.cpp
LIBRARIES = Matrix.hpp Window.hpp

all : $(OBJECTS) $(LIBRARIES)
	$(CPP) $(OBJECTS) -o "$(BIN)" $(CPPFLAGS)

compile :
	$(CPP) -std=c++0x -Wno-deprecated "main.cpp" -o "$(BIN)" $(CPPFLAGS)

run :
	./"$(BIN)"

remake :
	cd "/Users/Admin/apps/_src/Perl/LargeProjects/makegen"&& \
	perl "_make_gen.pl" "/Users/Admin/apps/_src/C++/SmallProjects/_Graphics/matrix" "main.cpp" "_matrix"&& \
	cd --

open :
	vim -p *.hpp

highlight :
	bash "/Users/Admin/apps/_src/Perl/LargeProjects/makegen/plugins/highlight/highlight.sh" "/Users/Admin/apps/_src/Perl/LargeProjects/makegen/plugins/highlight"
