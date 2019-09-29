main: main.cpp
	g++ main.cpp map.cpp -o pacman -lglut -lGLU -lGL -lm 
clean:
	rm pacman



g++ main.cpp ghost.cpp map.cpp next_direction.cpp pacman.cpp -o pacman -lopengl32 -lglew32 -lfreeglut -lglu32