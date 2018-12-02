#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    ifstream in;
	string str;
	vector<string> V;

	// reading input
	in.open("input.txt");
	while (in >> str)
    {
        V.push_back(str);
    }
    in.close();

    for (int i=0; i<V.size(); ++i)
        for (int j=i+1; j<V.size(); ++j)
            if (V[i].size() == V[j].size())
            {
                int diff=0;
                for (int k=0; k<V[i].size(); ++k)
                    if(V[i][k] != V[j][k])
                        ++diff;
                if(diff == 1)
                {
                    for (int k=0; k<V[i].size(); ++k)
                        if(V[i][k] == V[j][k])
                            cout << V[i][k];
                    cout << endl;
                }
            }

    return 0;
}
