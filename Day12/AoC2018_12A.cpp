#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

map<string, bool> M;

set<int> get_initial_set (string str)
{
    set<int> S;
    for (int i=0; i<str.size(); ++i)
        if(str[i] == '#')
            S.insert(i);
    return S;
}

set<int> get_next_set (set<int> S)
{
    set<int> S2;

    //insert all positions to look in S2;
    for(auto i : S)
    {
        for(int j=i-2; j<=i+2; ++j)
            S2.insert(j);
    }

    set<int>::iterator it=S2.begin();
    while(it!=S2.end())
    {
        string str=".....";
        for(int j=*it-2; j<=*it+2; ++j)
            if(S.count(j)>0)
                str[j-*it+2] = '#';
        if(M[str])
            ++it;
        else
        {
            set<int>::iterator jt=next(it);
            S2.erase(it);
            it = jt;
        }
    }
    return S2;
}

int main()
{
    ifstream in;
	string line, str;
	set<int> S;

	// reading input
	in.open("input.txt");
	getline(in, line);
	string pots = line.substr(15);
	while (getline(in, line))
    {
        if (!line.empty())
        {
            string around, arrow, result;
            istringstream istr(line);
            istr >> around >> arrow >> result;
            M[around] = (result == "#");
        }
    }
    in.close();

    S = get_initial_set(pots);
    for(int i=0; i<20; ++i)
        S = get_next_set(S);

    cout << accumulate(S.begin(), S.end(), 0);

    return 0;
}
