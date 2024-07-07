#include "Ball.hpp"

Ball::Ball(int px, int py, int pradius)
    :x(px), y(py), radius(pradius)
{
        //Randomly choose direction of the ball.
        srand(time(NULL));
        directionX = rand() % 2; 
        directionY = rand() % 2; 

        if(directionX == 0) directionX = -1; 
        if(directionY == 0) directionY = -1;
}

//To check for collision between ball and paddle.
bool Ball::intersect(SDL_Rect a)
{
        //Closest point on collision box.
        int cX, cY; 

        //Find closest x offset
        if(x < a.x)
        {
            cX = a.x;
        }

        else if(x > a.x + a.w)
        {
            cX = a.x + a.w;
        }
        else
        {
            cX = x;
        }

        //Find closest y offset
        if(y < a.y)
        {
            cY = a.y;
        }

        else if(y > a.y + a.h)
        {
            cY = a.y + a.h;
        }

        else
        {
            cY = y;
        }

        //Calculate the distance squared between the closest point on the box and the center of the circle.
        int deltaX = cX - x; 
        int deltaY = cY - y; 
        int distanceSquared = deltaX*deltaX + deltaY*deltaY; 

        //If the distance squared is less than the circle's radius squared, then there is a collision.
        if(distanceSquared < radius * radius)
        {
            return true;
        }

        return false;
}

//Update the ball's movements.
void Ball::update(int* score1, int* score2, int* lives, SDL_Rect paddle1, SDL_Rect paddle2)
{
        if(x <= 0)
        {
            directionX = 1;
            *score2 = *score2 + 1;
            *lives = *lives - 1;
        }
        
        if(x > 790)
        {
            directionX = -1;
            *score1 = *score1 + 1; 
            *lives = *lives - 1;
        }

        if(y <= 0)
        {
            directionY = 1;
        }
    
        if(y >= 490)
        {
            directionY = -1;
        }

        if(intersect(paddle1))
        {
            directionX = 1; 
        }

        if(intersect(paddle2))
        {
            directionX = -1;
        }

        x += 10 * directionX; 
        y += 10 * directionY; 
}

//Render the ball.
void Ball::render(SDL_Renderer* renderer)
{
        int offsetX, offsetY, d; 

        offsetX = 0; 
        offsetY = radius; 
        d = radius - 1; 
        
        while(offsetY >= offsetX)
        {
            SDL_RenderDrawLine(renderer, x - offsetY, y + offsetX, x + offsetY, y + offsetX);
            SDL_RenderDrawLine(renderer, x - offsetX, y + offsetY, x + offsetX, y + offsetY);
            SDL_RenderDrawLine(renderer, x - offsetX, y - offsetY, x + offsetX, y - offsetY);
            SDL_RenderDrawLine(renderer, x - offsetY, y - offsetX, x + offsetY, y - offsetX);
        
            if(d >= offsetX * 2)
            {
                d -= offsetX*2 + 1; 
                offsetX += 1; 
            }
            else if(d < (radius - offsetY) * 2)
            {
                d += 2 * offsetY - 1; 
                offsetY -= 1; 
            }
            else
            {
                d += 2 * (offsetY - offsetX - 1); 
                offsetY -= 1; 
                offsetX += 1;
            }
        }
}

//Called when restarting a game.
void Ball::reset()
{
        x = 400;
        y = 250; 

        srand(time(NULL));
        int directionX = rand() % 2; 
        int directionY = rand() % 2; 

        if(directionX == 0) directionX = -1; 
        if(directionY == 0) directionY = -1;
}