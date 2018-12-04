#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <vector>
#include <array>
using namespace std;

struct rectangle
{
    int x, y, width, height;

    rectangle(int x, int y, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this -> height = height;
    }
};

// should be global because of the limited stack size
int A[1001][1001] = {{0}};

int main()
{
    ifstream in;
	string line, str;
	int x, y, width, height, n=0;
	vector <rectangle> V;

	// reading input
	in.open("input.txt");
	while (getline(in, line))
    {
        if (!line.empty())
        {
            sscanf(line.c_str(), "#%*d @ %d,%d: %dx%d", &x, &y, &width, &height);
            V.push_back(rectangle(x, y, width, height));
        }
    }
    in.close();

    // resolving Part One
    for (rectangle r : V)
        for (int i=r.x; i<r.x+r.width; ++i)
            for (int j=r.y; j<r.y+r.height; ++j)
                ++A[i][j];

    for (int i=1; i<=1000; ++i)
        for (int j=1; j<=1000; ++j)
            if (A[i][j] > 1)
                ++n;

    cout << "Part One: " << n << endl;

    // resolving Part Two
    n=0;
    cout << "Part Two: ";

    for (int i=0; i<V.size(); ++i)
    {
        bool overlaps = false;

        for (int j=0; j<V.size(); ++j)
            if(i != j && (V[i].x < V[j].x + V[j].width && V[j].x < V[i].x + V[i].width) &&
               (V[i].y < V[j].y + V[j].height && V[j].y < V[i].y + V[i].height))
            {
                overlaps = true;
                break;
            }
        if (!overlaps)
            cout << i+1 << " ";
    }

    return 0;
}
