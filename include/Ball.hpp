#pragma once 
#include <iostream>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Ball
{
    public:
        Ball(int px, int py, int pradius);
        bool intersect(SDL_Rect a);
        void update(int* score1, int* score2, int* lives, SDL_Rect paddle1, SDL_Rect paddle2);
        void render(SDL_Renderer* renderer);
        void reset();

    private: 
        int x, y; 
        int radius; 
        int directionX, directionY;
};