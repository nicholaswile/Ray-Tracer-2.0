CXX := g++
CXX_FLAGS := -std=c++14 -Wall
SDL2_INC := C:\libraries\SDL2-devel-2.30.4-mingw\SDL2-2.30.4\i686-w64-mingw32\include
SDL2_LIB := C:\libraries\SDL2-devel-2.30.4-mingw\SDL2-2.30.4\i686-w64-mingw32\lib
LIBS := -lmingw32 -lSDL2main -lSDL2
SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

all:
	$(CXX) $(CXX_FLAGS) -I $(SDL2_INC) -L $(SDL2_LIB) -o main $(SRCS) $(LIBS)