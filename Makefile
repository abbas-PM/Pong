all:
	g++ -I include -L lib -o bin/main src/main.cpp src/renderwindow.cpp src/ball.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf 