#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ifstream in;
	string line, str;
	int i, players_num, last_marble;
	list<int> L;
	list<int>::iterator it;

	// reading input
	in.open("input.txt");
	getline(in, line);
	sscanf(line.c_str(), "%d players; last marble is worth %d points", &players_num, &last_marble);
    in.close();

    vector<long long> player_score(players_num);
    L.push_back(0);
    it = L.begin();
    for(i=1; i<=100*last_marble; ++i)
    {
        if(i%23 == 0)
        {
            for(int j=0; j<7; ++j)
            {
                if(it == L.begin())
                    it = L.end();
                --it;
            }
            if(it == L.begin())
                it = L.end();
            player_score[i%players_num] += i+*(prev(it));
            L.erase(prev(it));
            ++it;
        }
        else
        {
            if(it == L.end())
                it = L.begin();
            ++it;
            L.insert(it, i);
        }

        if(i == last_marble)
            cout << "Part One: " << *(max_element(player_score.begin(), player_score.end())) << endl;
    }

    cout << "Part Two: " << *(max_element(player_score.begin(), player_score.end())) << endl;

    return 0;
}
