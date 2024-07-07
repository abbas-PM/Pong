#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "RenderWindow.hpp"
#include "Ball.hpp"

const int WIDTH = 800;
const int HEIGHT = 500; 

RenderWindow* window;
Ball* ball;

SDL_Rect paddle1, paddle2;

int score1, score2; 
int lives = 10; 

bool updateMovement[4]; 

SDL_Color black = {0, 0, 0, 255};
SDL_Color white = {255, 255, 255, 255};

TTF_Font* font32; 
TTF_Font* font64; 

bool menu = true;
bool paused = false; 
bool gameComplete = false;

int endScreen = 0; 

bool versus, joined;

int minutes = 1; 
int seconds = 0; 

void init()
{
        //If SDL_Init failed. 
        if(SDL_Init(SDL_INIT_VIDEO) > 0)
        {
            std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl; 
        }

        //If TTF_Init failed
        if(TTF_Init() < 0)
        {
            std::cout << "TTF_Init failed: " << TTF_GetError() << std::endl; 
        }

        window = new RenderWindow("PONG", WIDTH, HEIGHT); 
        ball = new Ball(400, 250, 10);

        int PaddleWidth = 10; 
        int PaddleHeight = 100; 

        int paddle1X = 0; 
        int paddle1Y = 400; 

        int paddle2X = 790; 
        int paddle2Y = 400; 

        paddle1 = {paddle1X, paddle1Y, PaddleWidth, PaddleHeight}; 
        paddle2 = {paddle2X, paddle2Y, PaddleWidth, PaddleHeight}; 

        font32 = TTF_OpenFont("res/bitFont.ttf", 32);
        font64 = TTF_OpenFont("res/bitFont.ttf", 64);
}

//Update function.
void update()
{
        ball->update(&score1, &score2, &lives, paddle1, paddle2); 

        if(updateMovement[0] && paddle1.y > 0)
        {
            paddle1.y = paddle1.y - 10; 
        }

        if(updateMovement[1] && paddle1.y < HEIGHT - 100)
        {
            paddle1.y = paddle1.y + 10;
        }

        if(updateMovement[2] && paddle2.y > 0)
        {
            paddle2.y = paddle2.y - 10; 
        }

        if(updateMovement[3] && paddle2.y < HEIGHT - 100)
        {
            paddle2.y = paddle2.y + 10;
        }

        if(((score1 == 10 || score2 == 10) && versus) || (lives == 0 && joined) || (minutes == 0 && seconds == 0 && joined))
        {
            gameComplete = true; 
            endScreen = 300;
        }
}

//Render function.
void render()
{
        SDL_SetRenderDrawColor(window->getRenderer(), white.r, white.g, white.b, white.a); 

        if(versus)
        {
            char s1[3]; 
            char s2[3];

            std::sprintf(s1, "%d", score1);
            std::sprintf(s2, "%d", score2);

            window->renderText(200, 50, s1, font64, white);
            window->renderText(600, 50, s2, font64, white);
        }

        else if(joined)
        {
            char s[3]; 
            std::sprintf(s, "%d", lives);

            char min[2];
            std::sprintf(min, "%d", minutes);

            char sec[3]; 
            if(seconds >= 10) std::sprintf(sec, "%d", seconds);  
            else if(seconds < 10) std::sprintf(sec, "%d%d", 0, seconds);  

            if(lives == 10) window->renderText(365, 50, s, font64, white);
            else window->renderText(380, 50, s, font64, white);

            window->renderText(700, 10, min, font32, white);
            window->renderText(730, 5, ":", font32, white);
            window->renderText(745, 10, sec, font32, white);
        }
        
        SDL_RenderFillRect(window->getRenderer(), &paddle1);
        SDL_RenderFillRect(window->getRenderer(), &paddle2);
        SDL_RenderDrawLine(window->getRenderer(), 400, 0, 400, 500);

        ball->render(window->getRenderer());

        if(paused)
        {
            window->renderText(WIDTH/3 + 66, HEIGHT/2 + sin(SDL_GetTicks()/100)*2, "PAUSED", font32, white);
        }

        if(gameComplete)
        {
            if(versus)
            {
                if(score1 == 10)
                {
                    window->renderText(WIDTH/4 + 38, HEIGHT/2 + sin(SDL_GetTicks()/100)*2, "PLAYER ONE WINS!", font32, white); 
                }
                else if(score2 == 10)
                {
                    window->renderText(WIDTH/4 + 30, HEIGHT/2 + sin(SDL_GetTicks()/100)*2, "PLAYER TWO WINS!", font32, white);
                }
            }
            else if(joined)
            {
                if(lives == 0)
                {
                    window->renderText(WIDTH/4 + 50, HEIGHT/2 + sin(SDL_GetTicks()/100)*2, "YOU BOTH LOSE!", font32, white); 
                }
                else
                {
                    window->renderText(WIDTH/4 + 50, HEIGHT/2 + sin(SDL_GetTicks()/100)*2, "YOU BOTH WIN!", font32, white); 
                }
            }
            
        }

        SDL_SetRenderDrawColor(window->getRenderer(), black.r, black.g, black.b, black.a);
}

//Called when restarting a game.
void reset()
{
    menu = true;
    paused = false;
    gameComplete = false; 

    versus = false;
    joined = false;
    
    paddle1.x = 0;
    paddle1.y = 400; 

    paddle2.x = 790;
    paddle2.y = 400; 

    score1 = 0;
    score2 = 0;

    lives = 10;

    minutes = 1; 
    seconds = 0;

    ball->reset();
}

//Main game loop.
void gameLoop()
{
        bool running = true; 

        const int FPS = 60; 
        const int frameDelay = 1000 / FPS;

        Uint32 frameStart; 
        int frameTime; 

        int frameCounter = 0;

        while(running)
        {
            frameStart = SDL_GetTicks(); 

            SDL_Event event; 

            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                {
                    running = false;
                }

                else if(event.type == SDL_MOUSEBUTTONDOWN && menu)
                {
                    menu = false;
                    versus = true;
                }

                else if(event.type == SDL_KEYUP && menu)
                {
                    menu = false;
                    joined = true;
                }

                else if(event.type == SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_q:
                            updateMovement[0] = true;
                            break;  
                        
                        case SDLK_z: 
                            updateMovement[1] = true;
                            break;

                        case SDLK_UP:
                            updateMovement[2] = true;
                            break; 

                        case SDLK_DOWN:
                            updateMovement[3] = true;
                            break;
                    }
                }

                else if(event.type == SDL_KEYUP && !menu)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_q:
                            updateMovement[0] = false;
                            break;  
                        
                        case SDLK_z:
                            updateMovement[1] = false;
                            break;

                        case SDLK_UP:
                            updateMovement[2] = false;
                            break; 

                        case SDLK_DOWN:
                            updateMovement[3] = false;
                            break;
                        
                        case SDLK_SPACE:
                            if(!gameComplete) 
                            {
                                paused = !paused; 
                            }
                            break;
                    }
                }
            }

            if(menu)
            {
                window->clear(); 

                window->renderText(WIDTH/3 + 45, 50, "PONG", font64, white);

                window->renderText(WIDTH/3 - 120, 200 + sin(SDL_GetTicks()/100)*2, "Click to Play Versus Mode", font32, white);

                window->renderText(WIDTH/8 - 30, 300 + sin(SDL_GetTicks()/100)*2, "Press any Key to Play Joined Mode", font32, white);

                window->display();
            }
            else if(!menu)
            {
                window->clear();

                if(!paused && !gameComplete) 
                {
                    update();
                    frameCounter++;
                }

                render(); 

                if(endScreen > 0)
                {
                    endScreen -= 1;
                } 

                if(frameCounter % 60 == 0)
                {
                    seconds -= 1; 
                }

                if(seconds == -1)
                {
                    minutes -= 1;
                    seconds = 59;
                }

                if(gameComplete && endScreen == 0)
                {
                    reset();
                    frameCounter = 0; 
                }

                window->display();
            }

            frameTime = SDL_GetTicks() - frameStart;

            if(frameDelay > frameTime)
            {
                SDL_Delay(frameDelay - frameTime);
            }
        }

        TTF_CloseFont(font32);
        TTF_CloseFont(font64);

        window->cleanUp();

        delete window;
        delete ball;
}

int main(int argc, char* argv[])
{
        init();
        gameLoop();

        return 0; 
}