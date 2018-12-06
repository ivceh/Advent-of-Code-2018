#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

void polymer_react(list<char> *Lp)
{
    for (list<char>::iterator it = Lp->begin(); it!=Lp->end() && next(it)!=Lp->end();)
    {
        list<char>::iterator jt = next(it);
        if (*jt == *it+'A'-'a' || *jt == *it+'a'-'A')
        {
            list<char>::iterator kt = next(jt);
            Lp->erase(it);
            Lp->erase(jt);
            if(kt == Lp->begin())
                it = kt;
            else
                it = prev(kt);
        }
        else
            ++it;
    }
}

int main()
{
    ifstream in;
	string line, str;

	// reading input
	in.open("input.txt");
	in >> str;
    in.close();

    // solving Part One
    list<char> L(str.begin(), str.end());
    polymer_react(&L);
    cout << "Part One: " << L.size() << endl;

    // solving Part Two
    int min=L.size();
    for (char c='A'; c<='Z'; ++c)
    {
        L = list<char>(str.begin(), str.end());
        for (auto it=L.begin(); it!=L.end();)
        {
            if (*it == c || *it == c+'a'-'A')
            {
                auto jt = next(it);
                L.erase(it);
                it = jt;
            }
            else
                ++it;
        }
        polymer_react(&L);
        if(L.size() < min)
            min = L.size();
    }
    cout << "Part Two: " << min << endl;

    return 0;
}
