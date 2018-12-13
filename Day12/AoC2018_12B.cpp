#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

map<string, bool> M;
set<int> S;

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

set<int> translate_to_0(set<int> S)
{
    set<int> S2;
    int Sstart = *(S.begin());
    for (int i:S)
        S2.insert(i-Sstart);
    return S2;
}

int main()
{
    ifstream in;
	string line, str;
	// states until now translated to 0 and moment when they happened
	map<set<int>, int> states_seen;
	vector<int> position_sums;

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

    int i = 0;
    S = get_initial_set(pots);
    while(true)
    {
        position_sums.push_back(accumulate(S.begin(), S.end(), 0));
        set<int> S_translated = translate_to_0(S);
        if(states_seen.count(S_translated)>0)
        {
            int prev_i=states_seen[S_translated];
            cout << position_sums[prev_i+(50000000000LL-prev_i)%(i-prev_i)] +
                    (50000000000LL-prev_i)/(i-prev_i)*(position_sums[i]-position_sums[prev_i]);
            break;
        }
        else
            states_seen[S_translated] = i;
        S = get_next_set(S);
        ++i;
    }

    return 0;
}
