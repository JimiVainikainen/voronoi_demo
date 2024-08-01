#ifndef APP_H
#define APP_H
#include "SDL2/SDL.h"
#include <vector>
#include "structs.h"
#include "delaunator.hpp"
#include <math.h>
#include <array>
class App
{

    public:
        const int WIDTH = 1080;
        const int HEIGHT = 720;
        const int CIRCLECOUNT = 100;
        const char* APPNAME = "Voronoi demo";
        SDL_Window *window;
        SDL_Renderer *renderer;
        Circle* points;
        std::vector<double> triangleCoords;
        Triangle triangle;
        std::vector<Triangle> triangles;

        std::vector<std::pair<double,double>> circumcenters;
        std::vector<Circle> circumCenterCircles;
        std::vector<Edge> voronoiEdges;

        int triangleCount;
    public:
        App();
        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event* event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
        void SDL_DrawCircle(SDL_Renderer* renderer, Circle circle);
        void SDL_DrawTriangle(SDL_Renderer* renderer, Triangle triangle);
        void SDL_DrawEdge(SDL_Renderer* renderer, Edge);
    private:
        bool isRunning;
        std::array<size_t,3> EdgesOfTriangle(std::size_t t)
        {
            std::array<size_t,3> arr = {3*t,3*t+1,3*t+2};
            return arr; 
        }; // return indeces of edges of triangle
        std::vector<std::size_t> AdjacentTriangles(delaunator::Delaunator delaunay,size_t triangleIndex);
        std::size_t TriangleOfEdge(std::size_t e)
        {
            return floor((e/3));
        }; // return indeces of triangle
        std::size_t nextHalfEdge(std::size_t e)
        {
            return (e % 3 == 0 ?  e -2 : e +1);
        }; // return index of next edge
        std::size_t prevHalfEdge(std::size_t e)
        {
            return (e % 3 == 0 ? e+2 : e-1);
        }; // return index of prev edge
        
};
#endif

