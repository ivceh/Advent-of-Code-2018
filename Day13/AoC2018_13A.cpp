#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <map>
using namespace std;

#define x first
#define y second
#define coord pair<int,int>

vector<string> grid;

char& grid_value(const coord &c)
{
    return grid[c.y][c.x];
}

coord operator +(const coord& x, const coord& y)
{
    return make_pair(x.first + y.first, x.second + y.second);
}

enum direction
{
    leftdir=0,
    updir=1,
    rightdir=2,
    downdir=3
};

array<coord, 4> direction_vector({coord(-1,0), coord(0,-1), coord(1,0), coord(0,1)});
array<char, 4> direction_arrow({'<','^','>','v'});

direction left_direction(direction d)
{
    return (direction)((d+3)%4);
}

direction right_direction(direction d)
{
    return (direction)((d+1)%4);
}

direction arrow_direction(char c)
{
    switch(c)
    {
        case '<':
            return leftdir;
        case'^':
            return updir;
        case '>':
            return rightdir;
        case 'v':
            return downdir;
        default:
            throw invalid_argument("Character is not an arrow!");
    }
}

direction change_direction_in_corner(direction d, char c)
{
    if(c=='/')
        return (direction)(3-d);
    else if(c=='\\')
        return (direction)(d^1);
    else
        throw invalid_argument("Second argument is not the corner sign!");
}

enum state
{
    next_left = 0,
    next_straight = 1,
    next_right = 2
};

state next_state(state s)
{
    return (state)((s+1)%3);
}

struct map_value
{
    direction d;
    state s;

    map_value(direction d=leftdir, state s=next_left)
    {
        this->d = d;
        this->s = s;
    }

    void move_cart(char c)
    {
        switch(c)
        {
            case '-':
            case '|':
                break;
            case '/':
            case '\\':
                d = change_direction_in_corner(d, c);
                break;
            case '+':
                if (s==next_left)
                    d = left_direction(d);
                else if (s==next_right)
                    d = right_direction(d);
                s = next_state(s);
                break;
            default:
                throw invalid_argument(string("Not allowed character ") + c);
        }
    }
};

vector<coord> map_keys(map<coord, map_value> const &M)
{
    vector<coord> V;
    for (auto const& p : M)
        V.push_back(p.first);
    return V;
}

int main()
{
    ifstream in;
	string line, str;
	map<coord, map_value> M;

	// reading input
	in.open("input.txt");
	while (getline(in, line))
    {
        if (!line.empty())
            grid.push_back(line);
    }
    in.close();

    for(int j=0; j<grid.size(); ++j)
        for(int i=0; i<grid[i].size(); ++i)
            for(int k=0; k<4; ++k)
                if(grid_value(coord(i,j))==direction_arrow[k])
                {
                    M[coord(i,j)] = map_value((direction)k, next_left);
                    grid_value(coord(i,j)) = k%2==0 ? '-' : '|';
                }

    while(true)
    {
        for(coord c : map_keys(M))
        {
            map_value v = M[c];
            coord c2 = c + direction_vector[v.d];
            if(M.count(c2)>0)
            {
                cout << c2.x << ',' << c2.y;
                return 0;
            }
            v.move_cart(grid_value(c2));
            M.erase(c);
            M[c2] = v;
        }
    }

    return 0;
}
