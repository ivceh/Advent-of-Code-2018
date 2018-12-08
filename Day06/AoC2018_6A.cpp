#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#define x first
#define y second
#define point pair<int,int>
#define UNDEF -1
using namespace std;

struct closest
{
    int pointID, distance;

    closest(int pointID=UNDEF, int distance=1000)
    {
        this->pointID = pointID;
        this->distance = distance;
    }
};

array<point, 4> neighbours(point p)
{
    array<point, 4> A;
    A[0].x = p.x;
    A[0].y = p.y + 1;
    A[1].x = p.x;
    A[1].y = p.y - 1;
    A[2].x = p.x + 1;
    A[2].y = p.y;
    A[3].x = p.x - 1;
    A[3].y = p.y;

    return A;
}

inline bool point_is_in_rectangle(point p, int minx, int maxx, int miny, int maxy)
{
    return p.x >= minx && p.x <= maxx && p.y >= miny && p.y <= maxy;
}

int main()
{
    ifstream in;
	string line, str;
	int i, j, k, x, y, minx, maxx, miny, maxy;
	point point_to_eliminate;
	char comma;

	vector<point> V;
	map<point, closest> M;
	queue<point> Q;

	// reading input
	in.open("input.txt");
	while (getline(in, line))
    {
        if (!line.empty())
        {
            istringstream istr(line);
            istr >> x >> comma >> y;
            V.push_back(point(x, y));
        }
    }
    in.close();

    // It is enough to observe the rectangle [minx, maxx] × [miny, maxy].
    // The areas that contain the edge will "go to infinity" outside the rectangle
    minx = maxx = V[0].x;
    miny = maxy = V[0].y;
    for (i=0; i<V.size(); ++i)
    {
        if(V[i].x < minx)
            minx = V[i].x;
        if(V[i].x > maxx)
            maxx = V[i].x;
        if(V[i].y < miny)
            miny = V[i].y;
        if(V[i].y > maxy)
            maxy = V[i].y;
    }

    // BFS algorithm

    // fill initial queue
    for (int i=0; i<V.size(); ++i)
    {
        Q.push(V[i]);
        M[V[i]] = closest(i, 0);
    }
    int cnt=0;
    // execute BFS
    while(!Q.empty())
    {
        point p=Q.front();
        Q.pop();
        for (point p2 : neighbours(p))
        {
            if(M.count(p2) == 0)
            {
                if(point_is_in_rectangle(p2, minx, maxx, miny, maxy))
                {
                    Q.push(p2);
                    M[p2] = closest(M[p].pointID, M[p].distance+1);
                }
            }
            else if(M[p].pointID != M[p2].pointID && M[p2].distance == M[p].distance+1)
                M[p2].pointID = UNDEF;
        }
    }

    // if area of coordinate V[i] is infinite, infinite_area[i] should be true;
    vector<bool> infinite_area(V.size());

    // areas[i] is size of coordinate V[i] area
    vector<int> areas(V.size());
    for (i=minx; i<=maxx; ++i)
        for (j=miny; j<=maxy; ++j)
        {
            point p(i,j);
            if(M[p].pointID != UNDEF)
            {
                ++areas[M[p].pointID];
                if(i==minx || i==maxx || j==miny || j==maxy)
                    infinite_area[M[p].pointID] = true;
            }
            int n=M[p].pointID;
        }

    int maxarea=0;
    for (i=0; i<V.size(); ++i)
        if(!infinite_area[i] && areas[i]>maxarea)
            maxarea = areas[i];

    cout << maxarea;

    return 0;
}
