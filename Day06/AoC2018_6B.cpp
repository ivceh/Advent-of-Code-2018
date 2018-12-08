#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#define x first
#define y second
#define point pair<int,int>
#include <vector>
#include <map>
using namespace std;

inline int abs(int a)
{
    return a>0 ? a : -a;
}

inline int Manh_dist(point A, point B)
{
    return abs(A.x - B.x) + abs(A.y - B.y);
}

vector<point> V;
map<int, int> points_in_row, points_in_column;

int total_distance(point p)
{
    int sum = 0;
    for (point p2 : V)
        sum += Manh_dist(p, p2);
    return sum;
}

void move_right(int *total_dist, int x, int *left_points, int *right_points)
{
    int points_in_current_column;
    *total_dist += *left_points;
    *total_dist -= *right_points;
    if(points_in_column.count(x+1) == 0)
        points_in_current_column = 0;
    else
        points_in_current_column = points_in_column[x+1];
    *left_points += points_in_current_column;
    *right_points -= points_in_current_column;
}

void move_down(int *total_dist, int y, int *above_points, int *below_points)
{
    int points_in_current_row;
    *total_dist += *above_points;
    *total_dist -= *below_points;
    if(points_in_row.count(y+1) == 0)
        points_in_current_row = 0;
    else
        points_in_current_row = points_in_row[y+1];
    *above_points += points_in_current_row;
    *below_points -= points_in_current_row;
}

int main()
{
    ifstream in;
	string line, str;
	int i, j, k, x, y, minx, maxx, miny, maxy, total1, total2, cnt=0;
	char comma;

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

    for(point p : V)
    {
        ++points_in_column[p.x];
        ++points_in_row[p.y];
    }
    minx = points_in_column.begin()->first;
    maxx = prev(points_in_column.end())->first;
    miny = points_in_row.begin()->first;
    maxy = prev(points_in_row.end())->first;

    // We suppose all points we need are in the rectangle [minx-1, maxx+1]×[miny-1, maxy+1]
    total1=total_distance(point(minx-1,miny-1));
    int left_points=0, right_points=V.size();
    for(i=minx-1; i<=maxx+1; ++i)
    {
        int above_points=0, below_points=V.size();
        total2 = total1;
        for(j=miny-1; j<=maxy+1; ++j)
        {
            if(total2<10000)
                ++cnt;
            move_down(&total2, j, &above_points, &below_points);
        }
        move_right(&total1, i, &left_points, &right_points);
    }

    cout << cnt;

    return 0;
}
