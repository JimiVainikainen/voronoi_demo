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
        const int CIRCLECOUNT = 10;
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
        std::vector<Circle> allVertices;
        std::vector<Edge> rays;
        
    public:
        Test_App();
        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event* event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
        void SDL_DrawCircle(SDL_Renderer* renderer, const Circle& circle);
        void SDL_DrawTriangle(SDL_Renderer* renderer, const Triangle& triangle,int color);
        void SDL_DrawEdge(SDL_Renderer* renderer, const Edge&);
        void SDL_DrawPolygon(SDL_Renderer* renderer,const Polygon& polygon, int c);
    private:
        bool isRunning;
        std::array<int,3> EdgesOfTriangle(int t); // return indeces of edges of triangle
        int TriangleOfEdge(int e); // return indeces of triangle
        int nextHalfEdge(int e); // return index of next edge
        int prevHalfEdge(int e); // return index of prev edge
        std::vector<Edge> forEachTriangleEdge(std::vector<double> coords,delaunator::Delaunator delaunay);
        std::array<int,3> pointsOfTriangle(int t,delaunator::Delaunator delaunay);
        std::vector<int> trianglesAdjacentToTriangle(delaunator::Delaunator delaunay, int t); 
        Point circumcenter(Point a, Point b, Point c);
        Point triangleCenter(std::vector<double> coords, delaunator::Delaunator d,int t);
        std::vector<int> edgesAroundPoint(delaunator::Delaunator d,int start);
        
        bool inside(const Point& p,int edge, double boundary);
        
        
        Point midpoint(const Point& p0,const Point& p1);
        Point rayIntersectionPoint(int edge, delaunator::Delaunator& d, std::vector<double> coords, std::vector<Point> centers);
        Point intersection(const Point& prev_point, const Point& current_point, const int& edge,double boundary);
        std::pair<double,double> perpendicular_direction(const Point& p1, const Point& p2);
        std::vector<Point> clipPolygon(const std::vector<Point>& polygon, double minx, double maxx, double miny, double maxy);
        std::vector<Point> clipEdge(const std::vector<Point>& input,int edge, double boundary);
        std::vector<VoronoiVertex> collectVoronoiCell(int i, delaunator::Delaunator& d,std::vector<Point> triangleCenters);
        Point segmentBoxIntersection(Point& p1, Point& p2);
        Point intersectEdge(Point& a, Point& b,char axis,double value);
        std::vector<Point> clipPolygonToBox(std::vector<Point>& polygon);
        std::vector<Point> getCornersBetweenPoints(Point& a, Point& b);
        int edgeCornerIndex(const Point& p);
        int finalBoundaryEdgeAroundPoint(int pointIndex, delaunator::Delaunator& d);
        std::vector<VoronoiVertex> clipEdgeVoronoi(const std::vector<VoronoiVertex> &input, int edge, double boundary);
        std::vector<VoronoiVertex> clipVoronoiPolygon(const std::vector<VoronoiVertex> &polygon, double minx, double maxx, double miny, double maxy);
        std::vector<VoronoiVertex> ClockWiseSorting(const std::vector<VoronoiVertex>& polygon, const Point& centerPoint);
        int onTheBoundary(const VoronoiVertex& vertex);
        int computeSideBeforeClipping(const Point& origin, const Point& direction);
        bool isOutOfBounds(const Point& p);
        std::vector<Point> cornersBetweenSides(int sideA,int sideB);
    };
#endif

