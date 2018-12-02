#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream in;

	int a,b;

	int diff=0, total=0;

	// reading input
	in.open("input.txt");
	while(in >> diff)
        total += diff;
    in.close();

	cout << total;

    return 0;
}
