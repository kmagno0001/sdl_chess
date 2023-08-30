all:
	g++ -std=c++17 main.cpp -I src/include_sdl -I src/include_img -L src/lib_sdl -L src/lib_img -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o main