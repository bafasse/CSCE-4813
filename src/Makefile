# define libraries
ifeq ($(shell uname),Darwin)
LIB = -DMAC -framework OPENGL -framework GLUT
else
LIB = -lGL -lGLU -lglut
endif
LIB2 = libim/libim.a jpeg/libjpeg.a

# define makefile targets
CC = g++ -Wall -Wno-deprecated-declarations
BIN = balls balls2 balls3 balls4 bitmap building building2 building3 clip cube curve disk draw draw_rectangles example flocking gasket2d gasket3d hw2 hw3 hw4 hw5 line mandelbrot mandelbrot2 model_view object object2 object3 object4 office office2 pong process render render2 rotate rotate2 shortest_path square surface surface2 surface3 surface4 table terrain texture texture2 texture3 texture4 texture5 tic_tac_toe tic_tac_toe2 tree triangle whack_a_mole

all: $(BIN)

clean: 
	/bin/rm -f $(BIN)

jpeg/libjpeg.a:
	cd jpeg;make;cd ..

libim/libim.a:
	cd libim;make;cd ..

balls: balls.cpp shading.cpp
	$(CC) -o balls balls.cpp $(LIB)

balls2: balls2.cpp shading.cpp
	$(CC) -o balls2 balls2.cpp $(LIB)

balls3: balls3.cpp shading.cpp
	$(CC) -o balls3 balls3.cpp $(LIB)

balls4: balls4.cpp shading.cpp
	$(CC) -o balls4 balls4.cpp $(LIB)

bitmap: bitmap.cpp
	$(CC) -o bitmap bitmap.cpp $(LIB)

building: building.cpp
	$(CC) -o building building.cpp $(LIB)

building2: building2.cpp
	$(CC) -o building2 building2.cpp $(LIB)

building3: building3.cpp
	$(CC) -o building3 building3.cpp $(LIB)

clip: clip.cpp
	$(CC) -o clip clip.cpp $(LIB)

cube: cube.cpp
	$(CC) -o cube cube.cpp $(LIB)

curve: curve.cpp
	$(CC) -o curve curve.cpp $(LIB)

disk: disk.cpp
	$(CC) -o disk disk.cpp $(LIB)

draw: draw.cpp timer.cpp
	$(CC) -o draw draw.cpp timer.cpp $(LIB)

draw_rectangles: draw_rectangles.cpp
	$(CC) -o draw_rectangles draw_rectangles.cpp $(LIB)

example: example.cpp 
	echo $(CC) -o example example.cpp $(LIB2)

flocking: flocking.cpp graph3.cpp heap2.cpp
	$(CC) -o flocking flocking.cpp graph3.cpp heap2.cpp $(LIB)

gasket2d: gasket2d.cpp
	$(CC) -o gasket2d gasket2d.cpp $(LIB)

gasket3d: gasket3d.cpp
	$(CC) -o gasket3d gasket3d.cpp $(LIB)

hw2: hw2.cpp 
	$(CC) -o hw2 hw2.cpp $(LIB)

hw3: hw3.cpp 
	$(CC) -o hw3 hw3.cpp $(LIB)

hw4: hw4.cpp 
	$(CC) -o hw4 hw4.cpp $(LIB)

hw5: hw5.cpp 
	$(CC) -o hw5 hw5.cpp $(LIB)

line: line.cpp
	$(CC) -o line line.cpp $(LIB)

mandelbrot: mandelbrot.cpp
	$(CC) -o mandelbrot mandelbrot.cpp $(LIB)

mandelbrot2: mandelbrot2.cpp
	$(CC) -o mandelbrot2 mandelbrot2.cpp $(LIB)

model_view: model_view.cpp
	$(CC) -o model_view model_view.cpp $(LIB)

object: object.cpp
	$(CC) -o object object.cpp $(LIB)

object2: object2.cpp
	$(CC) -o object2 object2.cpp $(LIB)

object3: object3.cpp
	$(CC) -o object3 object3.cpp $(LIB)

object4: object4.cpp shading.cpp
	$(CC) -o object4 object4.cpp $(LIB)

office: office.cpp
	$(CC) -o office office.cpp $(LIB)

office2: office2.cpp
	$(CC) -o office2 office2.cpp $(LIB)

pong: pong.cpp
	$(CC) -o pong pong.cpp $(LIB)

process: process.cpp 
	echo $(CC) -o process process.cpp $(LIB) $(LIB2)

render: render.cpp
	$(CC) -o render render.cpp $(LIB)

render2: render2.cpp
	$(CC) -o render2 render2.cpp $(LIB)

rotate: rotate.cpp
	$(CC) -o rotate rotate.cpp $(LIB)

rotate2: rotate2.cpp
	$(CC) -o rotate2 rotate2.cpp $(LIB)

shortest_path: shortest_path.cpp graph3.cpp heap2.cpp
	$(CC) -o shortest_path shortest_path.cpp graph3.cpp heap2.cpp $(LIB)

square: square.cpp
	$(CC) -o square square.cpp $(LIB)

surface: surface.cpp
	$(CC) -o surface surface.cpp $(LIB)

surface2: surface2.cpp
	$(CC) -o surface2 surface2.cpp $(LIB)

surface3: surface3.cpp shading.cpp
	$(CC) -o surface3 surface3.cpp $(LIB)

surface4: surface4.cpp shading.cpp
	$(CC) -o surface4 surface4.cpp $(LIB)

table: table.cpp
	$(CC) -o table table.cpp $(LIB)

terrain: terrain.cpp 
	echo $(CC) -o terrain terrain.cpp $(LIB) $(LIB2)

texture: texture.cpp
	$(CC) -o texture texture.cpp $(LIB)

texture2: texture2.cpp
	$(CC) -o texture2 texture2.cpp $(LIB)

texture3: texture3.cpp 
	echo $(CC) -o texture3 texture3.cpp $(LIB) $(LIB2)

texture4: texture4.cpp 
	echo $(CC) -o texture4 texture4.cpp $(LIB) $(LIB2)

texture5: texture5.cpp 
	echo $(CC) -o texture5 texture5.cpp $(LIB) $(LIB2)

tic_tac_toe: tic_tac_toe.cpp
	$(CC) -o tic_tac_toe tic_tac_toe.cpp

tic_tac_toe2: tic_tac_toe2.cpp
	$(CC) -o tic_tac_toe2 tic_tac_toe2.cpp

tree: tree.cpp
	$(CC) -o tree tree.cpp $(LIB)

triangle: triangle.cpp
	$(CC) -o triangle triangle.cpp $(LIB)

whack_a_mole: whack_a_mole.cpp timer.cpp
	$(CC) -o whack_a_mole whack_a_mole.cpp timer.cpp $(LIB)

