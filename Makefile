CXX := g++
CXX_FLAGS := -std=c++17 -Wall
SDL2_INC := C:\libraries\SDL2-devel-2.30.4-mingw\SDL2-2.30.4\i686-w64-mingw32\include\SDL2
SDL2_LIB := C:\libraries\SDL2-devel-2.30.4-mingw\SDL2-2.30.4\i686-w64-mingw32\lib
SDL2_IMG_INC := C:\libraries\SDL2_image-devel-2.8.2-mingw\SDL2_image-2.8.2\i686-w64-mingw32\include\SDL2
SDL2_IMG_LIB := C:\libraries\SDL2_image-devel-2.8.2-mingw\SDL2_image-2.8.2\i686-w64-mingw32\lib
I := -I $(SDL2_INC) -I $(SDL2_IMG_INC)
L := -L $(SDL2_LIB) -L $(SDL2_IMG_LIB)
LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

all:
	$(CXX) $(CXX_FLAGS) $(I) $(L) -o main $(SRCS) $(LIBS)