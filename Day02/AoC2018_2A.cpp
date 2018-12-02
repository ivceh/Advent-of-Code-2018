#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int main()
{
    ifstream in;
	string str;
	char c;
	int twos=0, threes=0, n;
	bool two, three;

	// reading input
	in.open("input.txt");
	while (in >> str)
    {
        if (!str.empty())
        {
            two = three = false;
            for (c='a'; c<='z'; ++c)
            {
                n = count(str.begin(), str.end(), c);
                if (n==2)
                    two = true;
                else if (n==3)
                    three = true;
            }
            if (two)
                ++twos;
            if(three)
                ++threes;
        }
    }
    in.close();

    cout << twos * threes;

    return 0;
}
