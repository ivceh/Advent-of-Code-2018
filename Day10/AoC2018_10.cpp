#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

#define x first
#define y second
#define vec2dim pair<int,int>

vector<vec2dim> coordinates, velocities;

inline vec2dim position_in_time(int i, int t)
{
    return vec2dim(coordinates[i].x+t*velocities[i].x, coordinates[i].y+t*velocities[i].y);
}

inline int y_coord_in_time(int i, int t)
{
    return coordinates[i].y+t*velocities[i].y;
}

int greatest_minus_lowest_y(int t)
{
    int miny, maxy, y;
    miny = maxy = y_coord_in_time(0, t);
    for(int i=1; i<coordinates.size(); ++i)
    {
        y = y_coord_in_time(i, t);
        if(y < miny)
            miny = y;
        if(y > maxy)
            maxy = y;
    }
    return maxy - miny;
}

int ternary_search(int lower, int higher)
{
    if(higher-lower<10)
    {
        int mindiff=greatest_minus_lowest_y(lower), mint=lower;
        for(int i=lower+1; i<=higher; ++i)
        {
            int diff = greatest_minus_lowest_y(i);
            if(diff < mindiff)
            {
                mindiff = diff;
                mint = i;
            }
        }
        return mint;
    }
    else
    {
        int t1=(lower*2+higher)/3;
        int t2=(lower+higher*2)/3;
        if(greatest_minus_lowest_y(t1) < greatest_minus_lowest_y(t2))
            return ternary_search(lower, t2);
        else
            return ternary_search(t1, higher);
    }
}

// Find the moment when maxy-miny is the lowest
int find_the_best_moment()
{
    int pow;
    for(pow=1; greatest_minus_lowest_y(2*pow)<greatest_minus_lowest_y(pow); pow*=2);
    pow *= 2;
    return ternary_search(0, pow);
}

int main()
{
    ifstream in;
	string line, str;

	int x1,y1,x2,y2,t,i,j;
	vec2dim coord;

	// reading input
	in.open("input.txt");
	while (getline(in, line))
    {
        if (!line.empty())
        {
            istringstream istr(line);
            sscanf(line.c_str(), "position=<%d, %d> velocity=<%d, %d>", &x1, &y1, &x2, &y2);
            coordinates.push_back(vec2dim(x1,y1));
            velocities.push_back(vec2dim(x2,y2));
        }
    }
    in.close();

    t = find_the_best_moment();

    int minx, maxx, miny, maxy;
    coord = position_in_time(0, t);
    minx=maxx=coord.x;
    miny=maxy=coord.y;
    set<vec2dim> S;
    for(i=0; i<coordinates.size(); ++i)
    {
        coord = position_in_time(i, t);
        S.insert(coord);
        if(coord.x > maxx)
            maxx = coord.x;
        if(coord.x < minx)
            minx = coord.x;
        if(coord.y > maxy)
            maxy = coord.y;
        if(coord.y < miny)
            miny = coord.y;
    }

    cout << "Part One:" << endl << endl;
    for(i=miny; i<=maxy; ++i)
    {
        for(j=minx; j<=maxx; ++j)
        {
            if(S.count(vec2dim(j,i))>0)
                cout << '#';
            else
                cout << '.';
        }
        cout << endl;
    }
    cout << endl;

    cout << "Part Two: " << t << endl;

    return 0;
}
