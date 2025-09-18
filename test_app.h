#ifndef TEST_APP_H
#define TEST_APP_H
#include "SDL2/SDL.h"
#include <vector>
#include "structs.h"
#include "delaunator.hpp"
#include <math.h>
#include <array>
#include <set>
class Test_App
{

    public:
        const int WIDTH = 1080;
        const int HEIGHT = 720;
        const int CIRCLECOUNT = 50;
        const char* APPNAME = "Voronoi demo";
        SDL_Window *window;
        SDL_Renderer *renderer;
        Circle* points;
        std::vector<double> coords;
        std::vector<Edge> edges;
        std::vector<Triangle> sdl_triangles;
        std::vector<Circle> circumcenters;
        std::set<std::pair<int,int>> circumcenterSet;
        std::vector<Polygon> voronoiShapes;
    public:
        Test_App();
        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event* event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
        void SDL_DrawCircle(SDL_Renderer* renderer, Circle circle);
        void SDL_DrawTriangle(SDL_Renderer* renderer, Triangle triangle,int color);
        void SDL_DrawEdge(SDL_Renderer* renderer, Edge);
        void SDL_DrawPolygon(SDL_Renderer* renderer,Polygon polygon);
    private:
        bool isRunning;
        std::array<int,3> EdgesOfTriangle(int t); // return indeces of edges of triangle
        int TriangleOfEdge(int e); // return indeces of triangle
        int nextHalfEdge(int e); // return index of next edge
        int prevHalfEdge(int e); // return index of prev edge
        std::vector<Edge> forEachTriangleEdge(std::vector<double> coords,delaunator::Delaunator delaunay);
        std::array<int,3> pointsOfTriangle(int t,delaunator::Delaunator delaunay);
        std::vector<int> trianglesAdjacentToTriangle(delaunator::Delaunator delaunay, int t); 
        std::pair<int,int> circumcenter(SDL_Point a, SDL_Point b, SDL_Point c);
        std::pair<int,int> triangleCenter(std::vector<double> coords, delaunator::Delaunator d,int t);
        std::vector<int> edgesAroundPoint(delaunator::Delaunator d,int start);
        

};
#endif

