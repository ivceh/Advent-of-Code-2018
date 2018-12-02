#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

int main()
{
    ifstream in;
    bool over = false;

	int diff=0, total=0;

	set<int> S;
	S.insert(0);

	while(!over)
    {
        // reading input
        in.open("input.txt");
        while(in >> diff)
        {
            total += diff;

            if(S.count(total)!=0)
            {
                cout << total;
                over = true;
                break;
            }

            S.insert(total);
        }
        in.close();
    }

    return 0;
}
