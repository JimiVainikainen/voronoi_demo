#include <iostream>
#include "app.h"
#include "SDL2/SDL.h"
#include <cstdlib> 
#include <time.h>
#include <array>
#include "delaunator.hpp"
App::App()
{
    isRunning = true;
}

int App::OnExecute()
{
    if(OnInit() == false)
    {
        std::cout<<"Could not open window" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Event event;
    while(isRunning)
    {
        while(SDL_PollEvent(&event))
        {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
        SDL_Delay(32);
    }
    OnCleanup();

    return 0;
}

bool App::OnInit()
{
    SDL_Init( SDL_INIT_EVERYTHING );
    window = SDL_CreateWindow(APPNAME,
    SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if(NULL == window)
    {
        return false;
    }
    renderer = SDL_CreateRenderer(window,-1,0);
    points = new Circle[CIRCLECOUNT];
    srand(time(0));
    Circle corner_1;
    Circle corner_2;
    Circle corner_3;
    Circle corner_4;
    corner_1.x = 0;
    corner_1.y = 0;
    corner_1.radius = 0;

    corner_2.x = 0;
    corner_2.y = HEIGHT;
    corner_2.radius = 0;

    corner_3.x = WIDTH;
    corner_3.y = 0;
    corner_3.radius = 0;

    corner_4.x = WIDTH;
    corner_4.y = HEIGHT;
    corner_4.radius = 0;
    points[0] = corner_1;
    points[1] = corner_2;
    points[2] = corner_3;
    points[3] = corner_4;
    for(int i=4;i<CIRCLECOUNT;i++)
    {
        points[i].max_x = WIDTH;
        points[i].max_y = HEIGHT;
        points[i].randomPos();
        points[i].calculateNewTarget();
        points[i].radius = 5;
    }
    triangles = std::vector<Triangle>();
    triangleCoords = std::vector<double>();
    for(int j=0;j<CIRCLECOUNT;j++)
    {
        triangleCoords.push_back(points[j].x);
        triangleCoords.push_back(points[j].y);
    }
    delaunator::Delaunator d(triangleCoords);
    circumcenters = std::vector<std::pair<double,double>>();
    circumCenterCircles = std::vector<Circle>();
    voronoiEdges = std::vector<Edge>();
    for(std::size_t i = 0;i<d.triangles.size();i+=3)
    {
        int a = 2* d.triangles[i];
        int b = 2* d.triangles[i+1];
        int c = 2* d.triangles[i+2];
        Triangle tri;
        tri.a.x = d.coords[a];
        tri.a.y = d.coords[a + 1];
        
        tri.b.x = d.coords[b];
        tri.b.y = d.coords[b+1];
        
        tri.c.x = d.coords[c];
        tri.c.y = d.coords[c+1];
        triangles.push_back(tri);
        std::pair<double,double> p = delaunator::circumcenter(tri.a.x,tri.a.y,tri.b.x,tri.b.y,tri.c.x,tri.c.y);
        circumcenters.push_back(p);
        // tri index and p index should be same
        Circle cir;
        cir.x = p.first;
        cir.y = p.second;
        cir.radius = 5;
        circumCenterCircles.push_back(cir);
    }
    for(size_t i=0;i<triangles.size();i++)
    {
        // INDECES OF ADJACENT TRIANGLES
        std::vector<size_t> adjacentTriangles = AdjacentTriangles(d,i);
        for(size_t index = 0;index < adjacentTriangles.size();index++)
        {
            
            if(adjacentTriangles.at(index) < circumcenters.size() && i < circumcenters.size())
            {
                // draw line from epicenter of triangle(i) to triangle(index)
                Edge line;
                line.point_a.x = circumcenters.at(i).first;
                line.point_a.y = circumcenters.at(i).second;

                line.point_b.x = circumcenters.at(adjacentTriangles.at(index)).first;
                line.point_b.y = circumcenters.at(adjacentTriangles.at(index)).second;
                voronoiEdges.push_back(line);
                
                
            }
        }
    }

    return true;
}

void App::OnEvent(SDL_Event* event)
{
    if(SDL_QUIT == event->type)
    {
        isRunning = false;
    }
    
}

void App::OnLoop()
{    
    for(int i=4;i<CIRCLECOUNT;i++)
    {
        points[i].move();
    }
    
    triangles = std::vector<Triangle>();
    triangleCoords = std::vector<double>();
    for(int j=0;j<CIRCLECOUNT;j++)
    {
        triangleCoords.push_back(points[j].x);
        triangleCoords.push_back(points[j].y);
    }

    delaunator::Delaunator d(triangleCoords);
    circumcenters = std::vector<std::pair<double,double>>();
    circumCenterCircles = std::vector<Circle>();
    voronoiEdges = std::vector<Edge>();
    
    for(std::size_t i = 0;i<d.triangles.size();i+=3)
    {
        int a = 2* d.triangles[i];
        int b = 2* d.triangles[i+1];
        int c = 2* d.triangles[i+2];
        Triangle tri;
        tri.a.x = d.coords[a];
        tri.a.y = d.coords[a + 1];
        
        tri.b.x = d.coords[b];
        tri.b.y = d.coords[b+1];
        
        tri.c.x = d.coords[c];
        tri.c.y = d.coords[c+1];
        triangles.push_back(tri);
        std::pair<double,double> p = delaunator::circumcenter(tri.a.x,tri.a.y,tri.b.x,tri.b.y,tri.c.x,tri.c.y);
        circumcenters.push_back(p);
        // tri index and p index should be same
        Circle cir;
        cir.x = p.first;
        cir.y = p.second;
        cir.radius = 5;
        circumCenterCircles.push_back(cir);
    }
    for(size_t i=0;i<triangles.size();i++)
    {
        // INDECES OF ADJACENT TRIANGLES
        std::vector<size_t> adjacentTriangles = AdjacentTriangles(d,i);
        for(size_t index = 0;index < adjacentTriangles.size();index++)
        {
            
            if(adjacentTriangles.at(index) < circumcenters.size() && i < circumcenters.size())
            {
                // draw line from epicenter of triangle(i) to triangle(index)
                Edge line;
                line.point_a.x = circumcenters.at(i).first;
                line.point_a.y = circumcenters.at(i).second;

                line.point_b.x = circumcenters.at(adjacentTriangles.at(index)).first;
                line.point_b.y = circumcenters.at(adjacentTriangles.at(index)).second;
                voronoiEdges.push_back(line);
                
                
            }
        }
    }
}

void App::OnRender()
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer,255,255,255,255);


    for(std::size_t i=0;i<voronoiEdges.size();i++)
    {
        SDL_DrawEdge(renderer,voronoiEdges.at(i));
    }

    // Uncomment if you want to draw circles at circumcenters
    // for(std::size_t i=0;i<circmuCenterCircles.size();i++)
    // {
    //     SDL_DrawCircle(renderer,circmuCenterCircles.at(i));
    // }
    // RENDER CIRCLES
    for (int i=0;i<CIRCLECOUNT;i++)
    {
        SDL_DrawCircle(renderer,points[i]);
    }
    SDL_RenderPresent(renderer);
    
}

void App::SDL_DrawEdge(SDL_Renderer* renderer,Edge edge)
{
    SDL_RenderDrawLine(renderer,edge.point_a.x,edge.point_a.y,edge.point_b.x,edge.point_b.y);
}

void App::SDL_DrawTriangle(SDL_Renderer* renderer,Triangle triangle)
{
    SDL_RenderDrawLine(renderer,triangle.a.x,triangle.a.y,triangle.b.x,triangle.b.y);
    SDL_RenderDrawLine(renderer,triangle.b.x,triangle.b.y,triangle.c.x,triangle.c.y);
    SDL_RenderDrawLine(renderer,triangle.c.x,triangle.c.y,triangle.a.x,triangle.a.y);
}

void App::SDL_DrawCircle(SDL_Renderer* renderer, Circle circle)
{
    int diameter = 2* circle.radius;
    int x = (circle.radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);
    while (x >= y)
    {
        // Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, circle.x + x, circle.y - y);
        SDL_RenderDrawPoint(renderer, circle.x + x, circle.y  + y);
        SDL_RenderDrawPoint(renderer, circle.x - x, circle.y  - y);
        SDL_RenderDrawPoint(renderer, circle.x - x, circle.y  + y);
        SDL_RenderDrawPoint(renderer, circle.x + y, circle.y  - x);
        SDL_RenderDrawPoint(renderer, circle.x + y, circle.y  + x);
        SDL_RenderDrawPoint(renderer, circle.x - y, circle.y  - x);
        SDL_RenderDrawPoint(renderer, circle.x - y, circle.y  + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void App::OnCleanup()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    delete(points);
    points = NULL;
}

// This should return indeces of adjacent triangles
std::vector<size_t> App::AdjacentTriangles(delaunator::Delaunator d, size_t triangleIndex)
{
    size_t first = 3 * triangleIndex;
    size_t second = (3*triangleIndex) + 1;
    size_t third = (3*triangleIndex) +2;
    size_t edges[] = {first,second,third};
    std::vector<size_t> arr = std::vector<size_t>();
    arr.clear();
    for(size_t edge = 0; edge < 3;edge++)
    {
        size_t opposite = d.halfedges.at(edges[edge]); // opposite edge of 
        if(opposite >= 0 && opposite < d.halfedges.size())
        {
            arr.push_back(TriangleOfEdge(opposite));
        }
    }
    return arr;
}


int main(int argc, char* argv[])
{
    App app;
    return app.OnExecute();
}
