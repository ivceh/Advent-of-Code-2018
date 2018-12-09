#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int sum_of_metadatas(istream &in)
{
    int child_nodes, metadatas, sum=0, current;
    in >> child_nodes >> metadatas;
    for(int i=0; i<child_nodes; ++i)
        sum += sum_of_metadatas(in);

    for(int i=0; i<metadatas; ++i)
    {
        in >> current;
        sum += current;
    }

    return sum;
}

int main()
{
    ifstream in;
	string line, str;
	int sum=0;

	// reading input
	in.open("input.txt");
	sum = sum_of_metadatas(in);
    in.close();

    cout << sum;

    return 0;
}
