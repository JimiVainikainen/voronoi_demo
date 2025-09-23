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

    for(int i=0;i<CIRCLECOUNT;i++)
    {
        Circle circle = Circle();
        circle.max_x = WIDTH;
        circle.max_y = HEIGHT;
        circle.radius = 5;
        circle.randomPos();
        circle.calculateNewTarget();
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
    /*
    // CLIPPING TESTING
    std::vector<int> bounding_box = {0,WIDTH,0,HEIGHT};
    std::vector<Point> testPoly = {{-10, 10}, {5, 20}, {50, 10}, {5, -10}};
    auto clipped = clipPolygon(testPoly, 0, 40, 0, 30);
    for(int i=0;i<clipped.size();i++)
    {
        std::cout<< clipped.at(i).x << "|" << clipped.at(i).y << std::endl;
    }*/
    

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

    for(int i=0;i<(int)(coords.size()/2);i++)
    {
        auto cellvertices = collectVoronoiCell(i,d,centers);
        

        for(size_t idx = 0;idx < cellvertices.size();idx++)
        {
            if(!cellvertices.at(idx).center.has_value())
            {
                int edge = cellvertices.at(idx).edge;
                int e0 = d.triangles.at(edge);
                int e1 = d.triangles.at(nextHalfEdge(edge));

                Point p0 = {coords.at(2*e0),coords.at(2*e0+1)};
                Point p1 = {coords.at(2*e1),coords.at(2*e1+1)};

                Point midp = midpoint(p0,p1);
                Point dir = {p1.y - p0.y,p0.x-p1.x};
                Point intersection = rayIntersectionPoint(edge,d,coords,centers);

                
                
                if(intersection.x != -1 && intersection.y != -1)
                {
                    cellvertices.at(idx).center = intersection;
                }else
                {
                    std::cout << "no intersection?" << std::endl;
                }
                int point = d.triangles.at(nextHalfEdge(edge));  // Not nextHalfEdge(edge)!
                std::cout << "edge: " << edge << " -> point: " << point << std::endl;
                int edgeIndexOfOtherBoundary = finalBoundaryEdgeAroundPoint(point,d);
                if(edgeIndexOfOtherBoundary != -1)
                {
                    // found
                    std::cout << "found the other vertex, it is: " << edgeIndexOfOtherBoundary << std::endl;
                    Point otherIntersection = rayIntersectionPoint(edgeIndexOfOtherBoundary,d,coords,centers);
                    std::cout << "intersection point: " << otherIntersection.x << "," << otherIntersection.y << std::endl;
                    // also get the center for that edge
                    int triangle = TriangleOfEdge(edgeIndexOfOtherBoundary);
                    Point neighbourCenter = triangleCenter(coords,d,triangle);
                    VoronoiVertex neighbourVert;
                    neighbourVert.center = neighbourCenter;
                    cellvertices.push_back(neighbourVert);
                    if(otherIntersection.x != -1 && otherIntersection.y != -1)
                    {
                        VoronoiVertex vert;
                        vert.center = otherIntersection;
                        vert.edge = edgeIndexOfOtherBoundary;
                        cellvertices.push_back(vert);
                        
                        std::vector<Point> corners = getEdgesOfPoints(intersection,otherIntersection);
                        std::cout << "p1: " << intersection.x << "," << intersection.y << std::endl;
                        std::cout << "p2: " << otherIntersection.x << "," << otherIntersection.y << std::endl;

                        for(int c=0;c<corners.size();c++)
                        {
                            std::cout << "corner: " << corners.at(c).x << "," << corners.at(c).y << std::endl;
                        }

                        for(int j=0;j<corners.size();j++)
                        {
                            VoronoiVertex vert1;
                            vert1.center = corners.at(j);
                            cellvertices.push_back(vert1);
                        }
                    }
                }
                // calculate the same intersection for this edge as well and insert that 
                // finally calculate if any corners need to be added as well
            }
            cellvertices = clipVoronoiPolygon(cellvertices,0,WIDTH,0,HEIGHT);
        }
        Polygon poly;
        for (size_t idx = 0; idx < cellvertices.size(); idx++) {
            const auto& v = cellvertices[idx];

            if (v.center.has_value()) {
                poly.vertices.push_back(v.center.value());
            } else {
                // This edge goes to infinity — compute intersection
                // int edge = v.edge;
                // Point intersection = rayIntersectionPoint(edge, d, coords, centers);

                // if (intersection.valid()) {
                //     poly.vertices.push_back(intersection);
                // } else {
                //     std::cout << "No intersection for unbounded edge.\n";
                // }
            }
        }
        // Polygon poly;
        // for(const auto& v : cellvertices)
        // {
        //     if(v.center.has_value())
        //     {
        //         poly.vertices.push_back(v.center.value());
        //     }
        // }
        voronoiShapes.push_back(poly);
    }

   
    
    /* CLOSING OFF IMPLEMENTATION
    std::unordered_map<int, int> pointToEdge;
    for (int e = 0; e < d.triangles.size(); e++) 
    {
        int endpoint = d.triangles[nextHalfEdge(e)];
        // Insert if not exists OR if this edge is boundary (halfedges[e] == -1)
        if (pointToEdge.find(endpoint) == pointToEdge.end() || d.halfedges[e] == -1) {
            pointToEdge[endpoint] = e;
        }
    }
    
    int numPoints = coords.size() / 2;
    for (int p = 0; p < numPoints; p++) 
    {
        // Skip if no cell for this point
        if (pointToEdge.find(p) == pointToEdge.end()) continue;

        int incoming = pointToEdge[p];
        std::vector<int> voronoi_edges = edgesAroundPoint(d, incoming);

        // Then compute triangles and vertices as before
        std::vector<int> triangles;
        for (int edge : voronoi_edges) {
            triangles.push_back(TriangleOfEdge(edge));
        }

        std::vector<Point> vertices;
        for (int tri : triangles) {
            vertices.push_back(triangleCenter(coords, d, tri));
        }

        // Now you can process or render the Voronoi cell for point p
        // e.g. callback(p, vertices);
        std::vector<Point> new_verts = clipPolygon(vertices,0,WIDTH,0,HEIGHT);
        Polygon voronoiCell = Polygon();
        for(int v=0;v<new_verts.size();v++)
            {
                Edge edge = Edge();
                if(new_verts.at(v).x == 0 && new_verts.at(v).y == 0)
                {
                    std::cout << "!" << v << "goes to 0" << std::endl;
                }
                if(v == new_verts.size() -1)
                {
                    edge.point_a.x = new_verts.at(v).x;
                    edge.point_a.y = new_verts.at(v).y;

                    edge.point_b.x = new_verts.at(0).x;
                    edge.point_b.y = new_verts.at(0).y;
                }else
                {
                    edge.point_a.x = new_verts.at(v).x;
                    edge.point_a.y = new_verts.at(v).y;

                    edge.point_b.x = new_verts.at(v+1).x;
                    edge.point_b.y = new_verts.at(v+1).y;
                }
                voronoiCell.edges.push_back(edge);
            }
            //std::cout << "edge count: " << voronoiCell.edges.size() << std::endl;
            voronoiCell.vertices = new_verts;
            voronoiShapes.push_back(voronoiCell);
    }
    */
    
    
    //NORMAL HALF WORKING IMPLEMENTATION
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
            /*
            for(int i=0;i<voronoi_edges.size();i++)
            {
                int edge = voronoi_edges.at(i);
                if(d.halfedges.at(edge) == -1)
                {
                    std::cout<<"boundry edge v2" << std::endl;
                }
                int triangle = TriangleOfEdge(edge);
                Point center = triangleCenter(coords,d,triangle);
                std::pair<double,double> pair = std::make_pair<double,double>(static_cast<double>(center.x),static_cast<double>(center.y));
                circumcenterSet.insert(pair);
                verts.push_back(center);


            }
            double site_x = coords.at(2 * point);
            double site_y = coords.at(2 * point + 1);
            std::sort(verts.begin(), verts.end(), [&](const Point& a, const Point& b) {
                double angleA = atan2(a.y - site_y, a.x - site_x);
                double angleB = atan2(b.y - site_y, b.x - site_x);
                return angleA < angleB;
            });
            std::vector<Point> new_verts = clipPolygon(verts,0,WIDTH,0,HEIGHT);
            Polygon voronoiCell = Polygon();
            for(int v=0;v<new_verts.size();v++)
            {
                Edge edge = Edge();
                if(new_verts.at(v).x == 0 && new_verts.at(v).y == 0)
                {
                    std::cout << "!" << v << "goes to 0" << std::endl;
                }
                if(v == new_verts.size() -1)
                {
                    edge.point_a.x = new_verts.at(v).x;
                    edge.point_a.y = new_verts.at(v).y;

                    edge.point_b.x = new_verts.at(0).x;
                    edge.point_b.y = new_verts.at(0).y;
                }else
                {
                    edge.point_a.x = new_verts.at(v).x;
                    edge.point_a.y = new_verts.at(v).y;

                    edge.point_b.x = new_verts.at(v+1).x;
                    edge.point_b.y = new_verts.at(v+1).y;
                }
                voronoiCell.edges.push_back(edge);
            }
            //std::cout << "edge count: " << voronoiCell.edges.size() << std::endl;
            voronoiCell.vertices = new_verts;
            voronoiShapes.push_back(voronoiCell);
            */
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
    for(int i=0;i<rays.size();i++)
    {
        std::cout << "ray " << i << std::endl;
        std::cout <<"a: " << rays.at(i).point_a.x << "," << rays.at(i).point_a.y << std::endl;
        std::cout <<"b: " << rays.at(i).point_b.x << "," << rays.at(i).point_b.y << std::endl;
    }
    std::cout<< "triangles: " << sdl_triangles.size() << std::endl;
    std::cout<< "circumcenters: " << circumcenters.size() << std::endl;
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
/*
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
}*/

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
    
    // Forward traversal
    
    int e = firstEdge;
    visited.insert(e);
    /*
    while (true) {
        int t = TriangleOfEdge(e);
        const Point& center = triangleCenters.at(t);
        cellVertices.push_back({center, e});

        int nextE = nextHalfEdge(e);
        int opposite = halfedges.at(nextE);
        if (opposite == -1) {
            std::cout << "boundary forward!" << std::endl;
            cellVertices.push_back({std::nullopt, nextE});
            break;
        }
        if (visited.count(opposite) > 0) break;

        visited.insert(opposite);
        e = opposite;
    }*/

    // Backward traversal
    e = firstEdge;
    while (true) {
        int t = TriangleOfEdge(e);
        const Point& center = triangleCenters.at(t);
        cellVertices.insert(cellVertices.begin(), {center, e}); // prepend for correct ordering

        int prevE = prevHalfEdge(e);
        int opposite = halfedges.at(prevE);
        if (opposite == -1) {
            std::cout << "boundary backward!" << std::endl;
            cellVertices.insert(cellVertices.begin(), {std::nullopt, prevE});
            break;
        }
        if (visited.count(opposite) > 0) break;

        visited.insert(opposite);
        e = opposite;
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

std::vector<Point> Test_App::getEdgesOfPoints(Point &a, Point &b)
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

    std::cout << "A is on the edge: " << EdgeA << std::endl;
    std::cout << "B is on the edge: " << EdgeB << std::endl;

    int currentCorner = (EdgeB + 1 ) % 4;
    int stepCounter = 0;
    while(currentCorner != EdgeB)
    {
        //result.push_back(boxCorners.at(currentCorner));
        currentCorner = (currentCorner + 1 ) % 4;
        stepCounter++;
    }
    std::cout << "stepcount: " << stepCounter << std::endl;
    int i=0;
    int start = EdgeB;
    while(start != EdgeA)
    {
        start = (start + 1) % 4;
        i++;
    }
    std::cout << i << " amount of steps from b to a" << std::endl;
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
    return -1; // Not on a corner

}

int Test_App::finalBoundaryEdgeAroundPoint(int pointIndex, delaunator::Delaunator &d)
{
    int finalBoundaryEdge = -1;
    std::cout << "going to point: " << pointIndex << std::endl;

    for (int e = 0; e < d.triangles.size(); e++) {
        if (d.triangles.at(nextHalfEdge(e)) != pointIndex) continue;

        // This is an edge incoming to pointIndex
        std::cout << "edge: " << e << std::endl;
        int startEdge = e;
        int current = startEdge;
        do
        {
            int next = nextHalfEdge(current);
            int opposite = static_cast<int>(d.halfedges.at(next));
            if(opposite == -1)
            {
                std::cout << "found it, next has no opposite, next: " << next <<  std::endl;
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

    double dx = b.x - a.x;
    double dy = b.y - a.y;
    Point perpendicularV = {-dy,dx};
    double len = std::sqrt(perpendicularV.x*perpendicularV.x + perpendicularV.y * perpendicularV.y);
    Point direction = {perpendicularV.x / len, perpendicularV.y / len};

    Point origin = centers.at(t);

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
    SDL_SetRenderDrawColor(renderer,40,40,40,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    
    for(int i=0;i<voronoiShapes.size();i++)
    {
        SDL_DrawPolygon(renderer,voronoiShapes.at(i),i);
    }
    
    for (int point = 0;point < CIRCLECOUNT;point++)
    {
        SDL_DrawCircle(renderer,points[point]);
    }
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
    //SDL_DrawTriangle(renderer,sdl_triangles.at(0),0);
    for(int tri = 0; tri < sdl_triangles.size();tri++)
    {
        SDL_DrawTriangle(renderer,sdl_triangles.at(tri),tri);
    }
    SDL_SetRenderDrawColor(renderer,0,255,0,255);
    for(int i=0;i<rays.size();i++)
    {
        SDL_DrawEdge(renderer,rays.at(i));
    }
    for(int i=0;i<allVertices.size();i++)
    {
        SDL_DrawCircle(renderer,allVertices.at(i));
    }
    SDL_RenderPresent(renderer);
    
}

void Test_App::SDL_DrawEdge(SDL_Renderer* renderer,const Edge& edge)
{
    SDL_RenderDrawLine(renderer,edge.point_a.x,edge.point_a.y,edge.point_b.x,edge.point_b.y);
}

void Test_App::SDL_DrawTriangle(SDL_Renderer* renderer,const Triangle& triangle,int color)
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

void Test_App::SDL_DrawPolygon(SDL_Renderer* renderer,const Polygon& polygon, int count)
{

    if (polygon.vertices.size() >= 3) {
    SDL_Color color = {10*count, 0, 0, 255};

    std::vector<SDL_Vertex> verts;

    Point center = polygon.vertices[0];

        for (int i = 1; i < polygon.vertices.size() - 1; ++i) {
            verts =
            {
                {
                    SDL_FPoint{static_cast<float>(polygon.vertices[0].x), static_cast<float>(polygon.vertices[0].y)},
                    color, SDL_FPoint{0, 0}
                },
                {
                    SDL_FPoint{static_cast<float>(polygon.vertices[i].x), static_cast<float>(polygon.vertices[i].y)},
                    color, SDL_FPoint{0, 0}
                },
                {
                    SDL_FPoint{static_cast<float>(polygon.vertices[i+1].x), static_cast<float>(polygon.vertices[i+1].y)},
                    color, SDL_FPoint{0, 0}
                }
            };

            SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
        }
    }
    for (int i = 0; i < polygon.vertices.size(); i++) {
        const Point& a = polygon.vertices[i];
        const Point& b = polygon.vertices[(i + 1) % polygon.vertices.size()];
        Edge edge = Edge();
        edge.point_a = a;
        edge.point_b = b;
        SDL_DrawEdge(renderer, edge); // Replace with your draw function
    }
    // return;
    if(polygon.edges.size() >= 3)
    {
        int start = 0;
        int second = 1;
        int last = 2;
        SDL_Color color = {100,100,100,255};
        while(last > 0 && second > 0)
        {
            std::vector<SDL_Vertex> verts;
            verts = 
            {
                {SDL_FPoint{static_cast<float>(polygon.edges.at(start).point_a.x),static_cast<float>(polygon.edges.at(start).point_a.y)},color,SDL_FPoint{0},},
                {SDL_FPoint{static_cast<float>(polygon.edges.at(second).point_a.x),static_cast<float>(polygon.edges.at(second).point_a.y)},color,SDL_FPoint{0},},
                {SDL_FPoint{static_cast<float>(polygon.edges.at(last).point_a.x),static_cast<float>(polygon.edges.at(last).point_a.y)},color,SDL_FPoint{0},}
            };
            SDL_RenderGeometry(renderer,nullptr,verts.data(),verts.size(),nullptr,0);
            last++;
            second++;
            if(last >= polygon.edges.size())
            {
                //std::cout << "end " << std::endl;
                last = 0;
            }
        }
    }

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
