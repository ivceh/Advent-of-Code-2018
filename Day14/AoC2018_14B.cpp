#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
using namespace std;

int main()
{
    ifstream in;
	int n, pos1=0, pos2=1, i=0;
	bool match;

	// list of digits of number n;
	list<int> L;

	// list of scores
	vector<int> V({3,7});

	// reading input
	in.open("input.txt");
	in >> n;
    in.close();

    while(n>0)
    {
        L.push_front(n % 10);
        n /= 10;
    }

    while(!match)
    {
        ++i;

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

        match = true;
        int j=i;
        for(list<int>::iterator it=L.begin(); it!=L.end(); ++it,++j)
        {
            j %= V.size();
            if(V[j] != *it)
            {
                match = false;
                break;
            }
        }
    }

    cout << i;

    return 0;
}
