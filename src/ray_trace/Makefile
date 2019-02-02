# define libraries
ifeq ($(shell uname),Darwin)
LIB = -DMAC -framework OPENGL -framework GLUT
else
LIB = -lGL -lGLU -lglut
endif

# define makefile targets
CC = g++ -Wall -O3
BIN = ray_trace render
SRC = Camera.cpp Light.cpp Matrix3.cpp Matrix4.cpp Object.cpp Point3.cpp Scene.cpp ScreenPoint.cpp ScreenVector.cpp Shape.cpp Trans.cpp Vector3.cpp Vector4.cpp

all: $(BIN)

ray_trace: $(SRC) ray_trace.cpp
	$(CC) -o ray_trace ray_trace.cpp $(SRC) $(LIB)

render: $(SRC) render.cpp
	$(CC) -o render render.cpp $(SRC) $(LIB)

test:
	./ray_trace scenes/all*sc

clean:
	/bin/rm -f $(BIN)
