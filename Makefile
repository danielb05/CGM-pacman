chess: chess.cpp
	g++ pacman.cpp -o pacman -lglut -lGLU -lGL -lm 
clean:
	rm pacman
