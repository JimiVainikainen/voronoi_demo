#ifndef STRUCTS_H
#define STRUCKS_H
#include <iostream>
#include "SDL2/SDL.h"
#include <cstdlib> 
#include <time.h>
#include <math.h>
typedef struct
{
    /* data */
    int max_x = 0;
    int max_y = 0;
    double x;
    double y;
    int radius;
    SDL_Point *points;
    int target_x = 0;
    int target_y = 0;
    double speed = 1;
    void move()
    {
        // double dist = sqrt(pow((target_x-x),2)+(pow((target_y-y),2)));
        double vx = target_x - x;
        double vy = target_y - y;
        double len = sqrt(vx * vx + vy * vy);
        if(len < 1)
        {
            // std::cout << "Calculating new target" << std::endl;
            calculateNewTarget();
            // std:: cout << "Current: " << x << " : " << y << " -> " << target_x << " : " << target_y  << std::endl;
            return;
        }
        double dx = (vx / len) * speed;
        double dy = (vy / len) * speed;
        // std::cout << "Current pos " << x << ":" << y << std::endl;
        double next_x = x + dx;
        double next_y = y + dy;
        // std::cout << "Moving... nextx:"<< next_x<< " nexty: " << next_y << "len: " << len<<std::endl;
        y = next_y;
        x = next_x;
    }
    void calculateNewTarget()
    {   
        target_x = (rand() % max_x -1 ) + 1;
        target_y = (rand() % max_y - 1) + 1;
        // std::cout << "x: " << x << std::endl;
        // std::cout << "y: " << y << std::endl;
    }
    void randomPos()
    {
        x = rand() % max_x;
        y = rand() % max_y;
    }
} Circle;

typedef struct
{
    SDL_Point point_a;
    SDL_Point point_b;
} Edge;

typedef struct
{
    SDL_Point a;
    SDL_Point b;
    SDL_Point c;
    
} Triangle;

#endif