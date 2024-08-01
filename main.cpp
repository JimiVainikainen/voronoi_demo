#include <iostream>
#include <SDL2/SDL.h>
#include "delaunator.hpp"
// COMPILE COMMAND: mingw32-make.exe 
const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[])
{

    std::vector<double> coords = {-1, 1, 1, 1, 1, -1, -1, -1};

    //triangulation happens here
    delaunator::Delaunator d(coords);

    for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
        int a = 2* d.triangles[i];
        int b = 2* d.triangles[i+1];
        int c = 2* d.triangles[i+2];
        printf(
            "Triangle points: [[%f, %f], [%f, %f], [%f, %f]]\n",
            d.coords[a],        //tx0
            d.coords[a + 1],    //ty0
            d.coords[b],    //tx1
            d.coords[b + 1],//ty1
            d.coords[c],    //tx2
            d.coords[c + 1] //ty2
        );
    }
    system("pause");
    return 0;
    /*
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window *window = SDL_CreateWindow("Demo app",
    SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if( NULL == window)
    {
        std::cout<<"Could not open window" << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);
    
   
    size_t value = 0;
    SDL_Event windowEvent;
    while( true )
    {
        if(SDL_PollEvent( &windowEvent))
        {
            if(SDL_QUIT == windowEvent.type)
            { break; }
        }
        SDL_Rect r;
        r.h = 50;
        r.w = 50;
        r.x = value;
        r.y = 100;
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderFillRect(renderer, &r);
        SDL_RenderPresent(renderer);
        value++;
        if(value > WIDTH)
        {
            value = 0;
        }
        
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    system("pause");

    return EXIT_SUCCESS;*/
}