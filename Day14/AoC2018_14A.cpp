#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
using namespace std;

int main()
{
    ifstream in;
	int i, n, pos1=0, pos2=1;
	stack<int> St;

	// list of scores
	vector<int> V({3,7});

	// reading input
	in.open("input.txt");
	in >> n;
    in.close();

    for(i=0; i<n; ++i)
    {
        int s=V[pos1]+V[pos2];
        if(s<10)
            V.push_back(s);
        else
        {
            V.push_back(s/10);
            V.push_back(s%10);
        }
        pos1+=1+V[pos1];
        pos1%=V.size();
        pos2+=1+V[pos2];
        pos2%=V.size();
    }

    for(i=n; i<n+10; ++i)
        cout << V[i%V.size()];

    return 0;
}
