#include <iostream>
#include "test_app.h"
#include "SDL2/SDL.h"
#include <cstdlib> 
#include <time.h>
#include <array>
#include <set>
#include "delaunator.hpp"
Test_App::Test_App()
{
    isRunning = true;
}

int Test_App::OnExecute()
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

bool Test_App::OnInit()
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
    Circle c0 = Circle();
    c0.x = 0;
    c0.y = 0;
    points[0] = c0;
    Circle c1 = Circle();
    c1.x = 0;
    c1.y = HEIGHT;
    points[1] = c1;
    Circle c2 = Circle();
    c2.x = WIDTH;
    c2.y = 0;
    points[2] = c2;
    Circle c3 = Circle();
    c3.x = WIDTH;
    c3.y = HEIGHT;
    points[3] = c3;
    for(int i=4;i<CIRCLECOUNT;i++)
    {
        Circle circle = Circle();
        circle.max_x = WIDTH;
        circle.max_y = HEIGHT;
        circle.radius = 5;
        circle.randomPos();
        points[i] = circle;
    }
    // Circle c0 = Circle();
    // c0.x = 377;
    // c0.y = 479;
    // points[0] = c0;
    // Circle c1 = Circle();
    // c1.x = 453;
    // c1.y = 434;
    // points[1] = c1;
    // Circle c2 = Circle();
    // c2.x = 326;
    // c2.y = 387;
    // points[2] = c2;
    // Circle c3 = Circle();
    // c3.x = 444;
    // c3.y = 359;
    // points[3] = c3;
    // Circle c4 = Circle();
    // c4.x = 511;
    // c4.y = 389;
    // points[4] = c4;
    // Circle c5 = Circle();
    // c5.x = 586;
    // c5.y = 429;
    // points[5] = c5;
    // Circle c6 = Circle();
    // c6.x = 470;
    // c6.y = 315;
    // points[6] = c6;
    // Circle c7 = Circle();
    // c7.x = 622;
    // c7.y = 493;
    // points[7] = c7;
    // Circle c8 = Circle();
    // c8.x = 627;
    // c8.y = 367;
    // points[8] = c8;
    // Circle c9 = Circle();
    // c9.x = 570;
    // c9.y = 314;
    // points[9] = c9;

    coords = std::vector<double>();
    edges = std::vector<Edge>();
    sdl_triangles = std::vector<Triangle>();
    circumcenters = std::vector<Circle>();
    circumcenterSet = std::set<std::pair<int,int>>();
    for(int j=0;j<CIRCLECOUNT;j++)
    {
        coords.push_back(points[j].x);
        coords.push_back(points[j].y);
    }
    delaunator::Delaunator d(coords);
    

    std::set<int> seenPoints = std::set<int>();
    for(int e=0;e<d.triangles.size();e++)
    {

        // MAKING EDGES
        // if(d.halfedges.at(e) > d.halfedges.size())
        // {
        //     std::cout << "oops no half edge!" << e<< std::endl;
        // }
        // std::cout << d.triangles.at(e)<< std::endl;
        // std::cout << d.triangles.at(nextHalfEdge(e))<< std::endl;
        // std::cout << "-"<< std::endl;
        // Edge edge = Edge();
        // edge.point_a.x = coords.at(2*d.triangles.at(e));
        // edge.point_a.y = coords.at(2*d.triangles.at(e)+1);

        // edge.point_b.x = coords.at(2*d.triangles.at(nextHalfEdge(e)));
        // edge.point_b.y = coords.at(2*d.triangles.at(nextHalfEdge(e))+1);
        // edges.push_back(edge);
        // if(d.halfedges.at(e) <= d.halfedges.size())
        // {
        //     // checks if there is no other half edge
        // }

        // MAKING TRIANGLES
        // for(int t=0;t<d.triangles.size() / 3; t++)
        // {
        //     Triangle triangle = Triangle();
        //     std::array<int,3> trianglePoints = pointsOfTriangle(t,d);
        //     SDL_Point a = SDL_Point();
        //     SDL_Point b = SDL_Point();
        //     SDL_Point c = SDL_Point();
        //     a.x = coords.at(2*trianglePoints.at(0));
        //     a.y = coords.at(2*trianglePoints.at(0)+1);
        //     b.x = coords.at(2*trianglePoints.at(1));
        //     b.y = coords.at(2*trianglePoints.at(1)+1);
        //     c.x = coords.at(2*trianglePoints.at(2));
        //     c.y = coords.at(2*trianglePoints.at(2)+1);
        //     triangle.a = a;
        //     triangle.b = b;
        //     triangle.c = c;
        //     sdl_triangles.push_back(triangle);
        // }

        // MAKING VORONOI EDGES
        // int opposite = static_cast<int>(d.halfedges.at(e));
        // if(opposite == -1)
        // {
        //     std::cout <<  "-1!!!" << std::endl;
        //     continue;
        // }
        // if(e < d.halfedges.at(e))
        // {
        //     std::pair<int,int> point_a = triangleCenter(coords,d,TriangleOfEdge(e));
        //     std::pair<int,int> point_b = triangleCenter(coords,d,TriangleOfEdge(d.halfedges.at(e)));
        //     Circle center = Circle();
        //     center.x = point_a.first;
        //     center.y = point_a.second;
        //     circumcenterSet.insert(point_a);
        //     circumcenterSet.insert(point_b);
            
           
        //     Edge edge = Edge();
        //     edge.point_a.x = point_a.first;
        //     edge.point_a.y = point_a.second;
        //     edge.point_b.x = point_b.first;
        //     edge.point_b.y = point_b.second;
        //     std::cout << TriangleOfEdge(e) << "->";
        //     std::cout << TriangleOfEdge(d.halfedges.at(e));
        //     // std::cout << point_a.first << "|" << point_a.second << " ->";
        //     // std::cout << point_b.first << "|" << point_b.second << std::endl;
        //     std::cout << "--" << std::endl;
        //     edges.push_back(edge);
        // }

        int point = d.triangles.at(nextHalfEdge(e));
        if(seenPoints.end() == seenPoints.find(point))
        {
            seenPoints.insert(point);
            std::vector<int> voronoi_edges = edgesAroundPoint(d,e);
            std::vector<int> tris  = std::vector<int>();
            for(int i=0;i<voronoi_edges.size();i++)
            {
                tris.push_back(TriangleOfEdge(voronoi_edges.at(i)));
            }
            std::vector<std::pair<int,int>> verts = std::vector<std::pair<int,int>>();
            std::cout<<tris.size() <<  " triangles" << std::endl;
            for(int i=0;i<tris.size();i++)
            {
                verts.push_back(triangleCenter(coords,d,tris.at(i)));
            }
            int v = 0;
            Polygon voronoiCell = Polygon();
            std::cout<<verts.size() <<  " verts" << std::endl;
            for(v=0;v<verts.size();v++)
            {
                Edge edge = Edge();
                if(v == verts.size() -1)
                {
                    edge.point_a.x = verts.at(v).first;
                    edge.point_a.y = verts.at(v).second;

                    edge.point_b.x = verts.at(0).first;
                    edge.point_b.y = verts.at(0).second;
                }else
                {
                    edge.point_a.x = verts.at(v).first;
                    edge.point_a.y = verts.at(v).second;

                    edge.point_b.x = verts.at(v+1).first;
                    edge.point_b.y = verts.at(v+1).second;
                }
                voronoiCell.edges.push_back(edge);
            }
            std::cout << "edge count: " << voronoiCell.edges.size() << std::endl;
            voronoiShapes.push_back(voronoiCell);
        }
    }
    std::cout << circumcenterSet.size() << "d" << std::endl;
    std::set<std::pair<int,int>>::iterator itr;
    for(itr = circumcenterSet.begin(); itr != circumcenterSet.end();itr++)
    {
        Circle center = Circle();
        std::pair<int,int> value = (*itr);
        center.x = value.first;
        center.y = value.second;
        circumcenters.push_back(center);
    }

    std::cout << voronoiShapes.size() << " cells" << std::endl;
    return true;
}


int Test_App::nextHalfEdge(int e)
{
    if(e % 3 == 2)
    {
        return e - 2;
    }else
    {
        return e + 1;
    }
}

int Test_App::prevHalfEdge(int e)
{
    if(e % 3 == 0)
    {
        return e+2;
    }else
    {
        return e-1;
    }
}

std::array<int,3> Test_App::EdgesOfTriangle(int t)
{
    std::array<int,3> arr = {3*t,3*t+1,3*t+2};
    return arr; 
}

int Test_App::TriangleOfEdge(int e)
{
    return e/3;
}

std::array<int,3> Test_App::pointsOfTriangle(int t,delaunator::Delaunator delaunay)
{
    std::array<int,3> arr {};
    arr[0] = delaunay.triangles.at(3*t);
    arr[1] = delaunay.triangles.at(3*t+1);
    arr[2] = delaunay.triangles.at(3*t+2);
    return arr;
}

std::vector<Edge> Test_App::forEachTriangleEdge(std::vector<double> coords, delaunator::Delaunator delaunay)
{
    std::vector<Edge> edges = std::vector<Edge>();
    for(std::size_t e = 0;e<delaunay.triangles.size();e++)
    {
        if(e > delaunay.halfedges[e])
        {
            std::cout << "adding an edge" << std::endl;
            Edge edge;
            edge.point_a.x = coords[delaunay.triangles[2*e]];
            edge.point_a.y = coords[delaunay.triangles[(2*e)+1]];

            edge.point_b.x = coords[delaunay.triangles[nextHalfEdge(2*e)]];
            edge.point_b.y = coords[delaunay.triangles[nextHalfEdge((2*e)+1)]];
            edges.push_back(edge);
        }
    }
    return edges;
}

std::vector<int> Test_App::trianglesAdjacentToTriangle(delaunator::Delaunator delaunay, int t)
{
    std::vector<int> adjacentTriangels = {};
    std::array<int,3> edges = EdgesOfTriangle(t);
    for(int edge = 0;edge < edges.size();edge++)
    {
        int opposite = delaunay.halfedges.at(edge);
        if(opposite < delaunay.triangles.size())
        {
            adjacentTriangels.push_back(TriangleOfEdge(opposite));
        }
    }
    return adjacentTriangels;
}

std::pair<int,int> Test_App::circumcenter(SDL_Point a, SDL_Point b, SDL_Point c)
{
    int ad = a.x * a.x + a.y * a.y;
    int bd = b.x * b.x + b.y * b.y;
    int cd = c.x * c.x + c.y * c.y;

    int D = 2*
        (
        a.x  * (b.y-c.y)
        +b.x * (c.y - a.y)
        +c.x * (a.y-b.y)
        );
    if(D == 0)
    {
        return std::make_pair(0,0);
    }
    int num_1 = (
        ad * (b.y-c.y)
        + bd * (c.y-a.y)
        + cd * (a.y - b.y)
    );

    int num_2 = (
        ad * (c.x-b.x)
        + bd * (a.x-c.x)
        + cd * (b.x - a.x)
    );

    int pair_1 = num_1 / D;
    int pair_2 = num_2 / D;
    std::pair<int,int> returnPair = std::pair<int,int>(pair_1,pair_2);
    return returnPair;
}

std::pair<int,int> Test_App::triangleCenter(std::vector<double> coords, delaunator::Delaunator d,int t)
{
    std::array<int,3>  triangle = pointsOfTriangle(t,d);
    SDL_Point a = SDL_Point();
    SDL_Point b = SDL_Point();
    SDL_Point c = SDL_Point();
    a.x = coords.at(2*triangle.at(0));
    a.y = coords.at(2*triangle.at(0)+1);

    b.x = coords.at(2*triangle.at(1));
    b.y = coords.at(2*triangle.at(1)+1);

    c.x = coords.at(2*triangle.at(2));
    c.y = coords.at(2*triangle.at(2)+1);

    // a.x = coords.at(2*trianglePoints.at(0));
    // a.y = coords.at(2*trianglePoints.at(0)+1);
    // b.x = coords.at(2*trianglePoints.at(1));
    // b.y = coords.at(2*trianglePoints.at(1)+1);
    // c.x = coords.at(2*trianglePoints.at(2));
    // c.y = coords.at(2*trianglePoints.at(2)+1);
    return circumcenter(a,b,c);
}

std::vector<int> Test_App::edgesAroundPoint(delaunator::Delaunator d,int start)
{
    std::vector<int> result = {};
    int incoming = static_cast<int>(start);
    do
    {
        // loop back to start, do while to ensue we do it at least once and begin the loop
        result.push_back(incoming);
        int outgoing = nextHalfEdge(incoming);
        incoming = d.halfedges.at(outgoing);
    }while(incoming != -1 && incoming != start);
    return result;
}

void Test_App::OnEvent(SDL_Event* event)
{
    if(SDL_QUIT == event->type)
    {
        isRunning = false;
    }
    
}

void Test_App::OnLoop()
{    
    
}

void Test_App::OnRender()
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    // for (int point = 0;point < CIRCLECOUNT;point++)
    // {
    //     SDL_DrawCircle(renderer,points[point]);
    // }
    SDL_SetRenderDrawColor(renderer,0,255,255,255);
    for(int c = 0;c < circumcenters.size();c++)
    {
        SDL_DrawCircle(renderer,circumcenters.at(c));
    }
    SDL_SetRenderDrawColor(renderer,10,255,255,255);
   
    for(size_t edge = 0; edge < edges.size();edge++)
    {
        SDL_DrawEdge(renderer,edges.at(edge));
    }
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    //SDL_DrawTriangle(renderer,sdl_triangles.at(0),0);
    for(int tri = 0; tri < sdl_triangles.size();tri++)
    {
        SDL_DrawTriangle(renderer,sdl_triangles.at(tri),tri);
    }
    //SDL_DrawPolygon(renderer,voronoiShapes.at(0));
    for(int i=0;i<voronoiShapes.size();i++)
    {
        SDL_DrawPolygon(renderer,voronoiShapes.at(i));
    }
    SDL_RenderPresent(renderer);
    
}

void Test_App::SDL_DrawEdge(SDL_Renderer* renderer,Edge edge)
{
    SDL_RenderDrawLine(renderer,edge.point_a.x,edge.point_a.y,edge.point_b.x,edge.point_b.y);
}

void Test_App::SDL_DrawTriangle(SDL_Renderer* renderer,Triangle triangle,int color)
{
    // std::vector<SDL_Vertex> verts = 
    // {
    //     {SDL_FPoint {triangle.a.x,triangle.a.y},SDL_Color{10*color,10*color,10*color,255},SDL_FPoint{0},},
    //     {SDL_FPoint {triangle.b.x,triangle.b.y},SDL_Color{10*color,10*color,10*color,255},SDL_FPoint{0},},
    //     {SDL_FPoint {triangle.c.x,triangle.c.y},SDL_Color{10*color,10*color,10*color,255},SDL_FPoint{0},},
    // };
    // SDL_RenderGeometry(renderer,nullptr,verts.data(),verts.size(),nullptr,0);

    SDL_RenderDrawLine(renderer,triangle.a.x,triangle.a.y,triangle.b.x,triangle.b.y);
    SDL_RenderDrawLine(renderer,triangle.b.x,triangle.b.y,triangle.c.x,triangle.c.y);
    SDL_RenderDrawLine(renderer,triangle.c.x,triangle.c.y,triangle.a.x,triangle.a.y);
}

void Test_App::SDL_DrawCircle(SDL_Renderer* renderer, Circle circle)
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

void Test_App::SDL_DrawPolygon(SDL_Renderer* renderer,Polygon polygon)
{
    
    for(int i=0;i<polygon.edges.size();i++)
    {
        SDL_DrawEdge(renderer,polygon.edges.at(i));
    }
}

void Test_App::OnCleanup()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    delete(points);
    points = NULL;
}

int main(int argc, char* argv[])
{
    Test_App app;
    return app.OnExecute();
}
