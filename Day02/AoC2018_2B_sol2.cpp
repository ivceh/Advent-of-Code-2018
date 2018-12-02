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
	vector<set<string> > V;

	// reading input
	in.open("input.txt");
	while (in >> str)
        if(!str.empty())
            for (int i=0; i<str.size(); ++i)
            {
                if(V.size() < i+1)
                    V.push_back(set<string>());
                string without_one_letter = str.substr(0, i);
                if(i+1<str.size())
                    without_one_letter += str.substr(i+1, string::npos);

                if(V[i].count(without_one_letter) > 0)
                    cout << without_one_letter << endl;

                V[i].insert(without_one_letter);
            }
    in.close();

    return 0;
}
