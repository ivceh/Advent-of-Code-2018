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
	map<int, set<char> > seconds_and_letters_to_be_finished;
	int free_workers_num = 5, current_second = 0;

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

    while(!candidates.empty() || !seconds_and_letters_to_be_finished.empty())
    {
        if(!candidates.empty() && free_workers_num>0)
        {
            --free_workers_num;
            char c = *(candidates.begin());
            candidates.erase(c);
            used.insert(c);
            cout << c << " started \n";
            seconds_and_letters_to_be_finished[current_second+61+c-'A'].insert(c);
        }
        else // !seconds_and_letters_to_be_finished.empty()
        {
            pair<int, set<char> > p = *(seconds_and_letters_to_be_finished.begin());
            current_second = p.first;
            for (char c : p.second)
            {
                ++free_workers_num;
                for(auto &p2 : has_to_finish_before)
                {
                    if(used.count(p2.first)==0)
                    {
                        p2.second.erase(c);
                        if(p2.second.empty())
                        {
                            candidates.insert(p2.first);
                        }
                    }
                }
            }
            seconds_and_letters_to_be_finished.erase(current_second);
        }
    }

    cout << current_second;

    return 0;
}
