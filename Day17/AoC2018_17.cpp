#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

#define x first
#define y second
#define coord pair<int,int>

map<coord, char> M;
int miny, maxy;
coord spring(500,0);

coord down(coord c)
{
    return coord(c.x, c.y+1);
}

coord left(coord c)
{
    return coord(c.x-1, c.y);
}

coord right(coord c)
{
    return coord(c.x+1, c.y);
}

bool flow(coord c);

// return value answers to the question: "Is water at point c settled to the left?"
bool flow_left(coord c)
{
	c = left(c);
	while(M.count(c) == 0)
	{
		M[c] = '|';
		if(!flow(down(c)))
			return false;
		c = left(c);
	}
	return true;
}

// return value answers to the question: "Is water at point c settled to the right?"
bool flow_right(coord c)
{
	c = right(c);
	while(M.count(c) == 0)
	{
		M[c] = '|';
		if(!flow(down(c)))
			return false;
		c = right(c);
	}
	return true;
}

// return value answers to the question: "Is water at point c settled?"
bool flow(coord c)
{
	if(c.y > maxy)
		return false;
	else if(M.count(c)>0)
		return M[c] != '|';
	else
	{
		M[c] = '|';
		if(flow(down(c)))
		{
			if(flow_left(c) & flow_right(c))
			{
				coord c2;
				for(c2=c; M[c2]=='|'; c2=left(c2))
					M[c2] = '~';
				for(c2=right(c); M[c2]=='|'; c2=right(c2))
					M[c2] = '~';
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
}

int main()
{
    ifstream in;
    string line, str;
    int x1, x2, y1, y2;
    bool first_line = true;

    // reading input
    in.open("input.txt");
    while (getline(in, line))
    {
        if (!line.empty())
        {
            if(line[0]=='x')
            {
                sscanf(line.c_str(), "x=%d, y=%d..%d", &x1, &y1, &y2);
                if(first_line)
                {
                    miny = y1;
                    maxy = y2;
					first_line = false;
                }
                else
                {
                   if(y1 < miny)
                        miny = y1;
                   if(y2 > maxy)
                        maxy = y2;
                }

                for(int y=y1; y<=y2; ++y)
                    M[coord(x1,y)] = '#';
            }
            else if(line[0]=='y')
            {
                sscanf(line.c_str(), "y=%d, x=%d..%d", &y1, &x1, &x2);
                if(first_line)
				{
					miny = maxy = y1;
					first_line = false;
				}
                else
                {
                   if(y1 < miny)
                        miny = y1;
                   if(y1 > maxy)
                        maxy = y1;
                }

                for(int x=x1; x<=x2; ++x)
                    M[coord(x,y1)] = '#';
            }
        }
    }
    in.close();

    flow(spring);

    int cntA=0, cntB=0;
    for(pair<coord, char> p : M)
    {
        if((p.second=='~' || p.second=='|') && p.first.y>=miny && p.first.y<=maxy)
		{
			++cntA;
			if(p.second=='~')
				++cntB;
		}
    }

    cout << "Part One: " << cntA << endl << "Part Two: " << cntB << endl;

    return 0;
}
