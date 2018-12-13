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

int A[302][302]={{0}};

int main()
{
    ifstream in;
	string line, str;
	int i,j,k;

	// reading input
	in.open("input.txt");
	in >> grid_serial_number;
    in.close();

    int maxs=-20, maxx=-1, maxy=-1, maxdim=-1;

    for(i=0; i<302; ++i)
        A[0][i] = 0;
    for(i=0; i<302; ++i)
        A[i][0] = 0;
    for(i=1; i<302; ++i)
        for(j=1; j<302; ++j)
            A[i][j] = A[i-1][j]+A[i][j-1]-A[i-1][j-1]+power(i,j);

    for(k=1; k<301; ++k)
        for(i=1; i<302-k; ++i)
            for(j=1; j<302-k; ++j)
            {
                int s=A[i+k-1][j+k-1]-A[i-1][j+k-1]-A[i+k-1][j-1]+A[i-1][j-1];
                if(s>maxs)
                {
                    maxs = s;
                    maxx = i;
                    maxy = j;
                    maxdim = k;
                }
            }

    cout << maxx << "," << maxy << "," << maxdim;

    return 0;
}
