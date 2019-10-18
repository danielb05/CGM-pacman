main: main.cpp
	g++ main.cpp ghost.cpp map.cpp next_direction.cpp pacman.cpp texture.cpp -o pacman -lglut -lGLU -lGL -lm -ljpeg
clean:
	rm pacman
