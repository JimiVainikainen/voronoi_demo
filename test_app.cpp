#include <iostream>
#include "test_app.h"
#include "SDL2/SDL.h"
#include <cstdlib> 
#include <time.h>
#include <array>
#include <set>
#include <unordered_map>
#include "delaunator.hpp"
#include <functional>
#include <unordered_set>
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
    


    
    edges = std::vector<Edge>();
    sdl_triangles = std::vector<Triangle>();
    circumcenters = std::vector<Circle>();
    circumcenterSet = std::set<std::pair<int,int>>();
    allVertices = std::vector<Circle>();
    // int widthStep = WIDTH / 3;
    // int heightStep = HEIGHT / 3;
    // Circle c0 = Circle();
    // c0.x = 0;
    // c0.y = 0;
    // points[0] = c0;
    // Circle c1 = Circle();
    // c1.x = widthStep;
    // c1.y = 0;
    // points[1] = c1;
    // Circle c2 = Circle();
    // c2.x = widthStep * 2;
    // c2.y = 0;
    // points[2] = c2;
    // Circle c3 = Circle();
    // c3.x = widthStep * 3;
    // c3.y = 0;
    // points[3] = c3;
    
    // Circle c4 = Circle();
    // c4.x = 0;
    // c4.y = HEIGHT;
    // points[4] = c4;
    // Circle c5 = Circle();
    // c5.x = widthStep;
    // c5.y = HEIGHT;
    // points[5] = c5;
    // Circle c6 = Circle();
    // c6.x = widthStep * 2;
    // c6.y = HEIGHT;
    // points[6] = c6;
    // Circle c7 = Circle();
    // c7.x = widthStep * 3;
    // c7.y = HEIGHT;
    // points[7] = c7;

    // Circle c8 = Circle();
    // c8.x = 0;
    // c8.y = heightStep;
    // points[8] = c8;

    // Circle c9 = Circle();
    // c9.x = 0;
    // c9.y = heightStep * 2;
    // points[9] = c9;

    // Circle c10 = Circle();
    // c10.x = WIDTH;
    // c10.y = heightStep;
    // points[10] = c10;

    // Circle c11 = Circle();
    // c11.x = WIDTH;
    // c11.y = heightStep * 2;
    // points[11] = c11;

    // for(int i=0;i<CIRCLECOUNT;i++)
    // {
    //     std::cout << "x: " << points[i].x << ", y:" << points[i].y << std::endl;
    // }

    // std::cout << "initial positions:" << std::endl;
    // for(int i=0;i<CIRCLECOUNT;i++)
    // {
    //     Circle circle = Circle();
    //     circle.max_x = WIDTH;
    //     circle.max_y = HEIGHT;
    //     circle.radius = 5;
    //     circle.randomPos();
    //     circle.calculateNewTarget();
    //     std::cout << circle.x << "," << circle.y << std::endl;
    //     points[i] = circle;
    // }
    // std::cout << std::endl;

    // TEST VARIABLES (randomized first)
    Circle c0 = Circle();
    c0.x = 949;
    c0.y = 325;
    points[0] = c0;
    Circle c1 = Circle();
    c1.x = 768;
    c1.y = 432;
    points[1] = c1;
    Circle c2 = Circle();
    c2.x = 85;
    c2.y = 534;
    points[2] = c2;
    Circle c3 = Circle();
    c3.x = 752;
    c3.y = 564;
    points[3] = c3;
    Circle c4 = Circle();
    c4.x = 881;
    c4.y = 316;
    points[4] = c4;
    Circle c5 = Circle();
    c5.x = 108;
    c5.y = 706;
    points[5] = c5;
    Circle c6 = Circle();
    c6.x = 821;
    c6.y = 587;
    points[6] = c6;
    Circle c7 = Circle();
    c7.x = 531;
    c7.y = 50;
    points[7] = c7;
    Circle c8 = Circle();
    c8.x = 524;
    c8.y = 413;
    points[8] = c8;
    Circle c9 = Circle();
    c9.x = 169;
    c9.y = 591;
    points[9] = c9;

    // TEST VARIABLES AS IN THE EXAMPLE
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
    std::set<int> seenPoints = std::set<int>();
    voronoiShapes = std::vector<Polygon>();
    for(int point=4;point<CIRCLECOUNT;point++)
    {
       //points[point].move();
    }
    for(int j=0;j<CIRCLECOUNT;j++)
    {
        coords.push_back(points[j].x);
        coords.push_back(points[j].y);
    }
    
    delaunator::Delaunator d(coords);
    
    int triangleCount = d.triangles.size() / 3;
    std::vector<Point> centers = std::vector<Point>(triangleCount);
    for(int t=0;t<triangleCount;t++)
    {
        int i0 = d.triangles.at(3*t);
        int i1 = d.triangles.at(3*t+1);
        int i2 = d.triangles.at(3*t+2);
        Point a;
        Point b;
        Point c;
        a.x = coords.at(2*i0);
        a.y = coords.at(2*i0+1);
        b.x = coords.at(2*i1);
        b.y = coords.at(2*i1+1);
        c.x = coords.at(2*i2);
        c.y = coords.at(2*i2+1);
        centers.at(t) = circumcenter(a,b,c);
    }
    std::vector<Polygon> cells(coords.size()/2);
   
    int counter = 0;
    for(int i=0;i<(int)(coords.size()/2);i++)
    {
        Point polygonCenter = {coords.at(2*i),coords.at(2*i+1)};
        std::cout << std::endl;
        auto cellvertices = collectVoronoiCell(i,d,centers);
        std::vector<VoronoiVertex> finalCell;
        std::vector<VoronoiVertex> edgeVertices;
        std::vector<std::pair<VoronoiVertex,int>> edgeVerts;
        for(size_t idx = 0;idx < cellvertices.size();idx++)
        {
            
            
            if(!cellvertices.at(idx).center.has_value())
            {
                std::cout << "edge: " << cellvertices.at(idx).edge << "has not opposite: " << std::endl; 
                Point intersection = rayIntersectionPoint(cellvertices.at(idx).edge,d,coords,centers);
                VoronoiVertex vert = {intersection,0};
                // THIS ALREADY INTERCEPTS THE SIDE AND CAN BE DETECTED
                std::cout << "rayPoint: " << vert.center.value().x << "," << vert.center.value().y << std::endl;;
                int boundary = onTheBoundary(vert);
                if(boundary != -1)
                {
                    edgeVerts.push_back({vert,boundary});
                }
                finalCell.push_back(vert);
            }else
            {
                // THIS CAN BE OVER THE BOUNDARY
                std::cout << "point: " << cellvertices.at(idx).center.value().x << "," << cellvertices.at(idx).center.value().y << std::endl;
                Point direction = {cellvertices.at(idx).center.value().x - polygonCenter.x,cellvertices.at(idx).center.value().y - polygonCenter.y};
                finalCell.push_back(cellvertices.at(idx));
                if(isOutOfBounds(cellvertices.at(idx).center.value()))
                {
                    int side = computeSideBeforeClipping(polygonCenter,direction);
                    if(side != -1)
                    {
                        edgeVerts.push_back({cellvertices.at(idx),side});
                    }
                }
            }
            
        }
        if(edgeVerts.size() >= 2)
        {
            std::cout << "all the sides:" << std::endl;
            for(int i=0;i<edgeVerts.size();i++)
            {
                std::cout << edgeVerts.at(i).second << std::endl;
            }
            size_t n = edgeVerts.size();
            for(size_t i=0;i<n;i++)
            {
                // get pairs
                auto pair1 = edgeVerts.at(i);
                auto pair2 = edgeVerts.at((i+1) % n);
                int side1 = pair1.second;
                int side2 = pair2.second;
                if(side1 == side2) continue;
                // get corners between them
                int diff = (side2-side1 + 4) % 4;
                if(diff == 0) continue;
                if(diff > 2)
                {
                    std::swap(side1,side2);
                }

                auto corners = cornersBetweenSides(side1,side2);
                if(corners.empty()) continue;
                std::cout << "corners:" << std::endl;
                for(size_t corner = 0;corner < corners.size();corner++)
                {
                    std::cout << corners.at(corner).x << "," << corners.at(corner).y << std::endl;
                    finalCell.push_back({corners.at(corner),0});
                }
                // add the corners
                // go to next pair
            }


        }else
        {
            std::cout << "size: " << edgeVerts.size() << std::endl;
        }
        
        cellvertices = clipVoronoiPolygon(finalCell,0,WIDTH,0,HEIGHT);
        cellvertices = ClockWiseSorting(cellvertices,polygonCenter);
        Polygon poly;
        for (size_t idx = 0; idx < cellvertices.size(); idx++) 
        {
            const auto& v = cellvertices[idx];

            if (v.center.has_value()) 
            {
                poly.vertices.push_back(v.center.value());
            } 
        }
        poly.center = polygonCenter;
        std::cout << poly.center.x << "," << poly.center.y << std::endl;
        voronoiShapes.push_back(poly);
    }
    
    
    // calculating triangles
    for(int e=0;e<d.triangles.size();e++)
    {

        int point = static_cast<int>(d.triangles.at(nextHalfEdge(e)));
        if(seenPoints.end() == seenPoints.find(point))
        {
            seenPoints.insert(point);
            std::vector<int> voronoi_edges = edgesAroundPoint(d,e);
            std::vector<Point> verts = std::vector<Point>();
            for(int t=0;t<d.triangles.size() / 3; t++)
            {
                Triangle triangle = Triangle();
                std::array<int,3> trianglePoints = pointsOfTriangle(t,d);
                Point a = Point();
                Point b = Point();
                Point c = Point();
                a.x = coords.at(2*trianglePoints.at(0));
                a.y = coords.at(2*trianglePoints.at(0)+1);
                b.x = coords.at(2*trianglePoints.at(1));
                b.y = coords.at(2*trianglePoints.at(1)+1);
                c.x = coords.at(2*trianglePoints.at(2));
                c.y = coords.at(2*trianglePoints.at(2)+1);
                triangle.a = a;
                triangle.b = b;
                triangle.c = c;
                sdl_triangles.push_back(triangle);
            }
        }
    }
    



    // for rendering purposes
    std::set<std::pair<int,int>>::iterator itr;
    for(itr = circumcenterSet.begin(); itr != circumcenterSet.end();itr++)
    {
        Circle center = Circle();
        std::pair<int,int> value = (*itr);
        center.x = value.first;
        center.y = value.second;
        circumcenters.push_back(center);
    }

    //std::cout << voronoiShapes.size() << " cells" << std::endl;
    std::cout<< "voronoi shapes: " << voronoiShapes.size() << std::endl;
    for(int i=0;i<voronoiShapes.size();i++)
    {
        std::cout << "shape vertices: " << std::endl;
        for(int j=0;j<voronoiShapes.at(i).vertices.size();j++)
        {
            Circle c;
            c.x = voronoiShapes.at(i).vertices.at(j).x;
            c.y = voronoiShapes.at(i).vertices.at(j).y;
            c.radius = 3;
            allVertices.push_back(c);
            std::cout << voronoiShapes.at(i).vertices.at(j).x << "-" << voronoiShapes.at(i).vertices.at(j).y << std::endl; 
        }
    }
    std::cout << "rays: " << rays.size() << std::endl;
    // for(int i=0;i<rays.size();i++)
    // {
    //     std::cout << "ray " << i << std::endl;
    //     std::cout <<"a: " << rays.at(i).point_a.x << "," << rays.at(i).point_a.y << std::endl;
    //     std::cout <<"b: " << rays.at(i).point_b.x << "," << rays.at(i).point_b.y << std::endl;
    // }
    std::cout<< "triangles: " << sdl_triangles.size() << std::endl;
    std::cout<< "circumcenters: " << circumcenters.size() << std::endl;
    for(int i=0;i<circumcenters.size();i++)
    {
        std::cout << "center: " << circumcenters.at(i).x << "," << circumcenters.at(i).y << std::endl;
    }
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
    if (0 == arr[0] && 0 == arr[1] && 0 == arr[2])
    {
        std::cout << "0 triangle??" << std::endl;
    }
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

Point Test_App::circumcenter(Point a, Point b, Point c)
{
    double ad = a.x * a.x + a.y * a.y;
    double bd = b.x * b.x + b.y * b.y;
    double cd = c.x * c.x + c.y * c.y;

    double D = 2*
        (
        a.x  * (b.y-c.y)
        +b.x * (c.y - a.y)
        +c.x * (a.y-b.y)
        );
    if(D == 0)
    {
        std::cout << "empty" << std::endl;
        Point p;
        return p;
    }
    double num_1 = (
        ad * (b.y-c.y)
        + bd * (c.y-a.y)
        + cd * (a.y - b.y)
    );

    double num_2 = (
        ad * (c.x-b.x)
        + bd * (a.x-c.x)
        + cd * (b.x - a.x)
    );

    double pair_1 = num_1 / D;
    double pair_2 = num_2 / D;
    Point returnPair;
    returnPair.x = pair_1;
    returnPair.y = pair_2;
    if(pair_1 == 0 && pair_2 == 0)
    {
        std::cout << "pairs are 0" << std::endl;
    }

    if(pair_1 > WIDTH || pair_1 < 0)
    {
        std::cout << "x is out of bounds:"  << pair_1<< std::endl;
    }
    if(pair_2 > HEIGHT || pair_2 < 0)
    {
        std::cout << "y is out of bounds " << pair_2 << std::endl;
    }

    return returnPair;
}

Point Test_App::triangleCenter(std::vector<double> coords, delaunator::Delaunator d,int t)
{
    std::array<int,3>  triangle = pointsOfTriangle(t,d);
    Point a = Point();
    Point b = Point();
    Point c = Point();
    a.x = coords.at(2*triangle.at(0));
    a.y = coords.at(2*triangle.at(0)+1);

    b.x = coords.at(2*triangle.at(1));
    b.y = coords.at(2*triangle.at(1)+1);

    c.x = coords.at(2*triangle.at(2));
    c.y = coords.at(2*triangle.at(2)+1);

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
        int outgoing = static_cast<int>(nextHalfEdge(incoming));
        incoming = static_cast<int>(d.halfedges.at(outgoing));
    }while(incoming != -1 && incoming != start);

    return result;
}




std::vector<Point> Test_App::clipPolygon(const std::vector<Point> &polygon, double minx, double maxx, double miny, double maxy)
{
    std::vector<Point> output = polygon;

    // Clip against left edge
    output = clipEdge(output, 0, minx);
    // Clip against right edge
    output = clipEdge(output, 1, maxx);
    // Clip against bottom edge
    output = clipEdge(output, 2, miny);
    // Clip against top edge
    output = clipEdge(output, 3, maxy);

    return output;
}

std::vector<Point> Test_App::clipEdge(const std::vector<Point> &input, int edge, double boundary)
{
    std::vector<Point> output;
    if(input.empty()) return output;

    Point S = input.back();
    for(const Point& E : input) {
        bool E_inside = inside(E, edge, boundary);
        bool S_inside = inside(S, edge, boundary);

        if(E_inside) {
            if(!S_inside) {
                output.push_back(intersection(S, E, edge, boundary));
            }
            output.push_back(E);
        } else if(S_inside) {
            output.push_back(intersection(S, E, edge, boundary));
        }
        S = E;
    }
    return output;
}
Point Test_App::intersection(const Point &prev_point, const Point &current_point, const int &edge,double boundary)
{
    double x, y;
    double dx = current_point.x - prev_point.x;
    double dy = current_point.y - prev_point.y;
    
    if(edge == 0 || edge == 1) {
        // vertical edge x = boundary
        x = boundary;
        y = prev_point.y + dy * (boundary - prev_point.x) / dx;
    } else {
        // horizontal edge y = boundary
        y = boundary;
        x = prev_point.x + dx * (boundary - prev_point.y) / dy;
    }
    return {x, y};
}

bool Test_App::inside(const Point &p, int edge, double boundary)
{
    switch (edge)
    {
    case 0:
        return p.x >= boundary;
    case 1:
        return p.x <= boundary;
    case 2:
        return p.y >= boundary;
    case 3:
        return p.y <= boundary;
    }

    return false;
}
std::vector<VoronoiVertex> Test_App::clipEdgeVoronoi(const std::vector<VoronoiVertex> &input, int edge, double boundary)
{
    std::vector<VoronoiVertex> output;
    if (input.empty()) return output;

    VoronoiVertex S = input.back();
    for (const VoronoiVertex& E : input) {
        if (!E.center.has_value() || !S.center.has_value()) continue;

        Point Sp = S.center.value();
        Point Ep = E.center.value();

        bool E_inside = inside(Ep, edge, boundary);
        bool S_inside = inside(Sp, edge, boundary);

        if (E_inside) {
            if (!S_inside) {
                Point inter = intersection(Sp, Ep, edge, boundary);
                output.push_back({inter, -1});
            }
            output.push_back(E);
        } else if (S_inside) {
            Point inter = intersection(Sp, Ep, edge, boundary);
            output.push_back({inter, -1});
        }

        S = E;
    }

    return output;
}

std::vector<VoronoiVertex> Test_App::clipVoronoiPolygon(const std::vector<VoronoiVertex> &polygon, double minx, double maxx, double miny, double maxy)
{
    std::vector<VoronoiVertex> output = polygon;
    output = clipEdgeVoronoi(output, 0, minx);  // Left
    output = clipEdgeVoronoi(output, 1, maxx);  // Right
    output = clipEdgeVoronoi(output, 2, miny);  // Bottom
    output = clipEdgeVoronoi(output, 3, maxy);  // Top
    return output;
}

std::vector<VoronoiVertex> Test_App::ClockWiseSorting(const std::vector<VoronoiVertex> &polygon, const Point& centerPoint)
{
    std::vector<VoronoiVertex> rValue;
    double cx = 0, cy = 0;
    int n = polygon.size();
    for(int i=0;i<n;i++)
    {
        cx += polygon.at(i).center.value().x;
        cy += polygon.at(i).center.value().y;
    }
    cx /= n;
    cy /= n;

    std::vector<std::pair<VoronoiVertex,double>> vertexAngles;
    for(int i=0;i<n;i++)
    {
        double dx = polygon.at(i).center.value().x - cx;
        double dy = polygon.at(i).center.value().y - cy;
        double angle = atan2(dy,dx);
        vertexAngles.push_back({polygon.at(i),angle});
    }

    int minIdx = 0;
    for(int i=0;i<n-1;i++)
    {
        minIdx = i;
        for(int j=i+1;j<n;j++)
        {
            if(vertexAngles.at(j).second < vertexAngles.at(minIdx).second)
            {
                minIdx = j;
            }
        }
        std::pair<VoronoiVertex,double> temp = vertexAngles.at(i);
        vertexAngles.at(i) = vertexAngles.at(minIdx);
        vertexAngles.at(minIdx) = temp;
    }
    for(int i=0;i<vertexAngles.size();i++)
    {
        rValue.push_back(vertexAngles.at(i).first);
    }
    return rValue;
}

int Test_App::onTheBoundary(const VoronoiVertex &vertex)
{
    if(!vertex.center.has_value())
    {
        return -1;
    }
    // values
    // -1 wrong value
    // 1 top side
    // 2 right side
    // 3 bottom side
    // 4 left side
    // 5 corner
    std::vector<int> sideCount;
    int returnvalue = -1;
    if(vertex.center.value().y == 0)
    {
        return 1;
    }else if(vertex.center.value().x == WIDTH)
    {
        return 2;
    }else if(vertex.center.value().y == HEIGHT)
    {
        return 3;
    }else if(vertex.center.value().x == 0)
    {
        return 0;
    }
    return -1;
}

int Test_App::computeSideBeforeClipping(const Point &origin, const Point &direction)
{
    double tMin = std::numeric_limits<double>::infinity();
    int side = -1;

    // Left
    if (direction.x != 0) {
        double t = (0 - origin.x) / direction.x;
        double y = origin.y + t * direction.y;
        if (t > 0 && y >= 0 && y <= HEIGHT && t < tMin) {
            tMin = t;
            side = 0;
        }
    }
    // Right
    if (direction.x != 0) {
        double t = (WIDTH - origin.x) / direction.x;
        double y = origin.y + t * direction.y;
        if (t > 0 && y >= 0 && y <= HEIGHT && t < tMin) {
            tMin = t;
            side = 2;
        }
    }
    // Top
    if (direction.y != 0) {
        double t = (0 - origin.y) / direction.y;
        double x = origin.x + t * direction.x;
        if (t > 0 && x >= 0 && x <= WIDTH && t < tMin) {
            tMin = t;
            side = 1;
        }
    }
    // Bottom
    if (direction.y != 0) {
        double t = (HEIGHT - origin.y) / direction.y;
        double x = origin.x + t * direction.x;
        if (t > 0 && x >= 0 && x <= WIDTH && t < tMin) {
            tMin = t;
            side = 3;
        }
    }

    return side;
}

bool Test_App::isOutOfBounds(const Point &p)
{
    return p.x > WIDTH ||p.x < 0 || p.y > HEIGHT ||p.y < 0;
}

std::vector<Point> Test_App::cornersBetweenSides(int sideA, int sideB)
{
    std::vector<Point> corners;

    // Clockwise side traversal
    int s = sideA;
    while (s != sideB) {
        switch (s) {
            case 0: corners.push_back({0, 0}); break;                 // top-left
            case 1: corners.push_back({double(WIDTH), 0}); break;             // top-right
            case 2: corners.push_back({double(WIDTH), double(HEIGHT)}); break;        // bottom-right
            case 3: corners.push_back({0, double(HEIGHT)}); break;            // bottom-left
        }
        s = (s + 1) % 4;

        // Break loop if somehow invalid (infinite protection)
        if (corners.size() > 4) break;
    }

    return corners;
}

std::vector<VoronoiVertex> Test_App::collectVoronoiCell(int i, delaunator::Delaunator &d, std::vector<Point> triangleCenters)
{
    std::vector<std::size_t> triangles = d.triangles;
    std::vector<std::size_t> halfedges = d.halfedges;
    std::vector<VoronoiVertex> cellVertices;

    int firstEdge = -1;
    for (int e = 0; e < (int)triangles.size(); e++) {
        if (triangles.at(e) == i) {
            firstEdge = e;
            break;
        }
    }
    if (firstEdge == -1) return cellVertices;

    std::unordered_set<int> visited;    
    int e = firstEdge;
    
    bool boundary = false;

    // Backward traversal
    while (true) {

        int t = TriangleOfEdge(e);
        const Point& center = triangleCenters.at(t);
        
        //circumcenterSet.insert(std::make_pair<int,int>(center.x,center.y));
        int currOpposite = static_cast<int>(d.halfedges.at(e));
        int prevE = prevHalfEdge(e);
        if(currOpposite != -1)
        {
            visited.insert(e);
            cellVertices.insert(cellVertices.begin(), {center, e}); // prepend for correct ordering
        }else
        {
            if(center.x < 0 || center.x > WIDTH || center.y < 0 ||center.y > HEIGHT)
            {
                std::cout << "uh oh its over the bounds, skip this one:" << center.x << "," << center.y << std::endl;
            }else
            {
                std::cout << "withing bounding box, add this one" << std::endl;
                Point p;
                p.x = double(center.x);
                p.y = double(center.y);
                visited.insert(e);
                cellVertices.insert(cellVertices.begin(), {std::nullopt, e}); 
            }
            //cellVertices.insert(cellVertices.begin(), {p,e});
        }
        int opposite = static_cast<int>(halfedges.at(prevE));
        if (opposite == -1) {
            boundary = true;
            if(center.x < 0 || center.x > WIDTH || center.y < 0 ||center.y > HEIGHT)
            {
                std::cout << "uh oh its over the bounds, skip this one:" << center.x << "," << center.y << std::endl;
            }else
            {

                cellVertices.insert(cellVertices.begin(), {std::nullopt, prevE});
            }
            break;
        }
        if (visited.count(opposite) > 0) break;
        visited.insert(opposite);
        e = opposite;
    }
    if(boundary)
    {
        // forward traversal
        // if bt started at edge say 13, we start at opposite and go other way around
        e = static_cast<int>(d.halfedges.at(firstEdge));
        int t1 = TriangleOfEdge(e);
        const Point& center1 = triangleCenters.at(t1);
        if(e == -1)
        {
            if(visited.count(firstEdge) > 0 )
            {
                // found e already
                return cellVertices;
            }else
            {
                if(center1.x < 0 || center1.x > WIDTH || center1.y < 0 ||center1.y > HEIGHT)
                {
                    std::cout << "uh oh its over the bounds, skip this one:" << center1.x << "," << center1.y << std::endl;
                }else
                {
                    std::cout << "this ones good" << std::endl;
                    cellVertices.insert(cellVertices.end(),{std::nullopt,firstEdge});
                }
                return cellVertices;
            }
        }
        while(true)
        {

            int t = TriangleOfEdge(e);
            const Point& center = triangleCenters.at(t);
            cellVertices.insert(cellVertices.end(), {center, e});
            int nextE = nextHalfEdge(e);
            int opposite = static_cast<int>(d.halfedges.at(nextE));
            if(opposite == -1)
            {
                if(center1.x < 0 || center1.x > WIDTH || center1.y < 0 ||center1.y > HEIGHT)
                {
                    std::cout << "uh oh its over the bounds, skip this one:" << center1.x << "," << center1.y << std::endl;
                }else
                {
                    std::cout << "this ones good" << std::endl;
                    cellVertices.insert(cellVertices.end(),{std::nullopt,nextE});
                }
                break;
            }
            if(visited.count(opposite) > 0) break;
            e = opposite;
        }
    }
    return cellVertices;
}

Point Test_App::segmentBoxIntersection(Point &p1, Point &p2)
{
    double x0 = p1.x;
    double y0 = p1.y;

    double x1 = p2.x;
    double y1 = p2.y;

    double dx = x1-x0;
    double dy = y1-y0;

    double t0 = 0;
    double t1 = 1;

    for(int i=0;i<4;i++)
    {
        // 0 = left, 1 = right, 2 = bottom, 3 = up
        double p,q;
        switch (i)
        {
        case 0:
            p = -dx;
            q = x0-0; // 0 = x min
            break;
        case 1:
            p = dx;
            q = WIDTH - x0; // WIDTH = xMAX
            break;
        case 2:
            p = -dy;
            q = y0 - 0; // 0 = yMin
            break;
        case 3:
            p = dy;
            q = HEIGHT -y0; // HEIGHT = yMax
            break;
        };

        if(p == 0)
        {
            if(q < 0)
            {
                // line is outside
                return {-1,-1};
            }
        }else
        {
            double r = q/p;
            if(p < 0)
            {
                if(t0 < r)
                {
                    t0 = r;
                }
            }else
            {
                if(t1 > r)
                {
                    t1 = r;
                }
            }
        }
        if(t0 > t1)
        {
            // no intersection
           return {-1,-1};
        }
    }   

    double intersectionX = x0 + dx*t1;
    double intersectionY = y0 + dy * t1;
    Point p;
    p.x = intersectionX;
    p.y = intersectionY;
    return p;
}

Point Test_App::intersectEdge(Point &a, Point &b, char axis, double value)
{
    if(axis == 'x')
    {
        double t = (value - a.x) / (b.x - a.x);
        double y = a.y + (b.y - a.y) * t;
        return {value,y};
    }else if(axis == 'y')
    {
        double t = (value - a.y) / (b.y - a.y);
        double x = a.x + (b.x - a.x) * t;
        return {x,value};
    }else
    {
        std::cout << "wrong axis entered, only x or y allowed" << std::endl;
    }

    return Point();
}

std::vector<Point> Test_App::getCornersBetweenPoints(Point &a, Point &b)
{
    std::vector<Point> boxCorners = {{0,0},{WIDTH,0},{WIDTH,HEIGHT},{0,HEIGHT}};
    std::vector<Point> result;
    int EdgeA = edgeCornerIndex(a);
    int EdgeB = edgeCornerIndex(b);
    if(EdgeA == -1 || EdgeB == -1)
    {
        std::cout << "invalid!" << std::endl;
        return result;
    }

    int currentCorner = (EdgeB + 1 ) % 4;
    int stepCounter = 0;
    while(currentCorner != EdgeB)
    {
        //result.push_back(boxCorners.at(currentCorner));
        currentCorner = (currentCorner + 1 ) % 4;
        stepCounter++;
    }
    int i=0;
    int start = EdgeB;
    while(start != EdgeA)
    {
        start = (start + 1) % 4;
        i++;
    }
    for(int c=0;c<i;c++)
    {
        int index = (EdgeA + c) % 4;
        result.push_back(boxCorners.at(index));
    }
    return result;
}

int Test_App::edgeCornerIndex(const Point &p)
{
    constexpr double EPS = 1e-3;
    if(std::abs(p.y - 0 ) < EPS) return 0;
    if(std::abs(p.x - WIDTH) < EPS) return 1;
    if(std::abs(p.y - HEIGHT) < EPS) return 2;
    if(std::abs(p.x - 0 ) < EPS ) return 3;
    std::cout << "point not on edge " << p.x <<"," << p.y << std::endl;
    return -1; 
}

int Test_App::finalBoundaryEdgeAroundPoint(int pointIndex, delaunator::Delaunator &d)
{
    int finalBoundaryEdge = -1;

    for (int e = 0; e < d.triangles.size(); e++) {
        if (d.triangles.at(nextHalfEdge(e)) != pointIndex) continue;

        int startEdge = e;
        int current = startEdge;
        do
        {
            int next = nextHalfEdge(current);
            int opposite = static_cast<int>(d.halfedges.at(next));
            if(opposite == -1)
            {
                finalBoundaryEdge = next; 
                return finalBoundaryEdge;
            }
            current = opposite;
        } while (startEdge != current && current != -1);
    }  
    return finalBoundaryEdge;  // Could be -1 if none are on boundary
}

std::pair<double,double> Test_App::perpendicular_direction(const Point& p1, const Point& p2)
{
    return std::pair<double,double>();
}

Point Test_App::midpoint(const Point &p0, const Point &p1)
{
    Point returnPoint = Point();
    returnPoint.x = (p0.x + p1.x) / 2;
    returnPoint.y = (p0.y + p1.y) / 2;
    return returnPoint;
}

Point Test_App::rayIntersectionPoint(int edge, delaunator::Delaunator &d, std::vector<double> coords, std::vector<Point> centers)
{
    std::vector<size_t> triangles = d.triangles;
    int t = TriangleOfEdge(edge);
    Point a = {coords.at(2*triangles.at(edge)),coords.at(2*triangles.at(edge)+1)};
    Point b = {coords.at(2*triangles.at(nextHalfEdge(edge))),coords.at(2*triangles.at(nextHalfEdge(edge))+1)};

    Point Midpoint = midpoint(a,b);
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    Point perpendicularV = {-dy,dx};

    double len = std::sqrt(perpendicularV.x*perpendicularV.x + perpendicularV.y * perpendicularV.y);
    Point direction = {perpendicularV.x / len, perpendicularV.y / len};
    Point origin = Midpoint;

    Point far = {origin.x + direction.x * 10000,origin.y + direction.y * 10000};
    Point value = segmentBoxIntersection(origin,far);
    if(value.x == -1 && value.y == -1)
    {
        std::cout << "danger" << std::endl;
    }else if (value.x != -1 && value.y != -1)
    {

        Edge ray;
        ray.point_a = origin;
        ray.point_b = value;
        rays.push_back(ray);
    }
    return value;
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
    SDL_SetRenderDrawColor(renderer,102,102,102,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    
    for(int i=0;i<voronoiShapes.size();i++)
    {
        SDL_DrawPolygon(renderer,voronoiShapes.at(i),i);
    }

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
    SDL_SetRenderDrawColor(renderer,255,0,0,255);

    // drawing the voronoi triangles
    // SDL_DrawTriangle(renderer,sdl_triangles.at(0),0);
    // for(int tri = 0; tri < sdl_triangles.size();tri++)
    // {
    //     SDL_DrawTriangle(renderer,sdl_triangles.at(tri),tri);
    // }
    SDL_SetRenderDrawColor(renderer,0,255,0,255);
    // Drawing boundary edge rays
    // for(int i=0;i<rays.size();i++)
    // {
    //     SDL_DrawEdge(renderer,rays.at(i));
    // }
    // for(int i=0;i<allVertices.size();i++)
    // {
    //     SDL_DrawCircle(renderer,allVertices.at(i));
    // }
    SDL_RenderPresent(renderer);
    
}

void Test_App::SDL_DrawEdge(SDL_Renderer* renderer,const Edge& edge)
{
    SDL_RenderDrawLine(renderer,edge.point_a.x,edge.point_a.y,edge.point_b.x,edge.point_b.y);
}

void Test_App::SDL_DrawTriangle(SDL_Renderer* renderer,const Triangle& triangle,int color)
{
    SDL_RenderDrawLine(renderer,triangle.a.x,triangle.a.y,triangle.b.x,triangle.b.y);
    SDL_RenderDrawLine(renderer,triangle.b.x,triangle.b.y,triangle.c.x,triangle.c.y);
    SDL_RenderDrawLine(renderer,triangle.c.x,triangle.c.y,triangle.a.x,triangle.a.y);
}

void Test_App::SDL_DrawCircle(SDL_Renderer* renderer, const Circle& circle)
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

void Test_App::SDL_DrawPolygon(SDL_Renderer* renderer,const Polygon& polygon, int c)
{
    SDL_Color color;
    double y = polygon.center.y;
    uint8_t r = 10 * c;
    uint8_t g = 0;
    uint8_t b = 0;
    color = {r,g,b,255};

    if (polygon.vertices.size() >= 3) 
    {
        //SDL_Color color = {static_cast<Uint8>(10), 0, 0, 255};

        for (int i = 1; i < static_cast<int>(polygon.vertices.size()) - 1; ++i) {
            std::array<SDL_Vertex, 3> triangle = {
                SDL_Vertex{
                    SDL_FPoint{static_cast<float>(polygon.vertices[0].x), static_cast<float>(polygon.vertices[0].y)},
                    color, SDL_FPoint{0, 0}
                },
                SDL_Vertex{
                    SDL_FPoint{static_cast<float>(polygon.vertices[i].x), static_cast<float>(polygon.vertices[i].y)},
                    color, SDL_FPoint{0, 0}
                },
                SDL_Vertex{
                    SDL_FPoint{static_cast<float>(polygon.vertices[i + 1].x), static_cast<float>(polygon.vertices[i + 1].y)},
                    color, SDL_FPoint{0, 0}
                }
            };
            SDL_RenderGeometry(renderer, nullptr, triangle.data(), triangle.size(), nullptr, 0);
        }
    }
    for (int i = 0; i < polygon.vertices.size(); i++) 
    {
        const Point& a = polygon.vertices[i];
        const Point& b = polygon.vertices[(i + 1) % polygon.vertices.size()];
        Edge edge = Edge();
        edge.point_a = a;
        edge.point_b = b;
        SDL_DrawEdge(renderer, edge);
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
