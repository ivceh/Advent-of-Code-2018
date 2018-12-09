#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>
using namespace std;

int main()
{
    ifstream in;
	string line, str;

	set<char> mentioned;
	set<char> used;
	set<char> candidates;
	map<char, set<char> > has_to_finish_before;
	string order;

	// reading input
	in.open("input.txt");
	while (getline(in, line))
    {
        if (!line.empty())
        {
            char c1, c2;
            sscanf(line.c_str(), "Step %c must be finished before step %c can begin.", &c1, &c2);
            has_to_finish_before[c2].insert(c1);
            mentioned.insert(c1);
            mentioned.insert(c2);
        }
    }
    in.close();

    for (char c : mentioned)
        if(has_to_finish_before.count(c)==0)
            candidates.insert(c);

    while(!candidates.empty())
    {
        char c = *(candidates.begin());
        candidates.erase(c);
        order.push_back(c);
        used.insert(c);
        for(auto &p : has_to_finish_before)
            if(used.count(p.first)==0)
            {
                p.second.erase(c);
                if(p.second.empty())
                    candidates.insert(p.first);
            }
    }

    cout << order;

    return 0;
}
