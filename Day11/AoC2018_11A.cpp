#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int grid_serial_number;

int power(int x, int y)
{
    int p=x+10;
    p*=y;
    p+=grid_serial_number;
    p*=x+10;
    p%=1000;
    p/=100;
    p-=5;
    return p;
}

int main()
{
    ifstream in;
	string line, str;

	// reading input
	in.open("input.txt");
	in >> grid_serial_number;
    in.close();

    int maxs=-20, maxx=-1, maxy=-1;

    for(int i=1; i<299; ++i)
        for(int j=1; j<299; ++j)
        {
            int s = power(i,j)+power(i+1,j)+power(i+2,j)
                    +power(i,j+1)+power(i+1,j+1)+power(i+2,j+1)
                    +power(i,j+2)+power(i+1,j+2)+power(i+2,j+2);
            if(s>maxs)
            {
                maxs=s;
                maxx=i;
                maxy=j;
            }
        }

    cout << maxx << "," << maxy;

    return 0;
}
