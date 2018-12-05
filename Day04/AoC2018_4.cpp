#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int stoi(string s)
{
    return atoi(s.c_str());
}

int main()
{
    ifstream in;
	string line, str;
	vector<string> lines;

	map<int,array<int, 60> > sleep_by_minute;
	map<int, int> total_sleep;
	int currguard, startsleep=-1, endsleep, beginshift;

	// reading input
	in.open("input.txt");
	while (getline(in, line))
    {
        if (!line.empty())
        {
            lines.push_back(line);
        }

    }
    in.close();

    // sorting in chronological order
    sort(lines.begin(), lines.end());

    // getting statistics for guards
    for (string line : lines)
    {
        string what = line.substr(19, 5);
            if (what == "Guard")
            {
                currguard = stoi(line.substr(26, string::npos));
                if(line.substr(12,2)=="00")
                    beginshift = stoi(line.substr(15, 2));
                else
                    beginshift = 0;
            }
            else if (what == "falls")
            {
                startsleep = stoi(line.substr(15, 2));
            }
            else if (what == "wakes")
            {
                endsleep = stoi(line.substr(15, 2));
                for (int i=startsleep; i<endsleep; ++i)
                    ++sleep_by_minute[currguard][i];
                total_sleep[currguard] += endsleep-startsleep;
                startsleep = -1;
            }
            else
                cout << "?";
    }

    // solving Part One
    int maxsleep = -1, maxguard = -1;
    for (auto p : total_sleep)
        if (p.second > maxsleep)
        {
            maxsleep = p.second;
            maxguard = p.first;
        }

    maxsleep = -1;
    int maxmin = -1;
    for (int i=0; i<60; ++i)
        if (sleep_by_minute[maxguard][i] > maxsleep)
        {
            maxsleep = sleep_by_minute[maxguard][i];
            maxmin = i;
        }

    cout << "Part One: guard " << maxguard << ", minute " << maxmin << ", solution " << maxguard * maxmin << endl;

    // solving Part Two
    maxguard = maxmin = maxsleep = -1;
    for (auto p : sleep_by_minute)
        for (int i=0; i<60; ++i)
        {
            if (p.second[i] > maxsleep)
            {
                maxsleep = p.second[i];
                maxguard = p.first;
                maxmin = i;
            }
        }

    cout << "Part Two: guard " << maxguard << ", minute " << maxmin << ", solution " << maxguard * maxmin << endl;

    return 0;
}
