#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct node
{
    vector<node> children;
    vector<int> metadatas;
};

node read_tree(istream &in)
{
    node N;
    int child_nodes, metadatas, sum=0, current;
    in >> child_nodes >> metadatas;
    for(int i=0; i<child_nodes; ++i)
    {
        N.children.push_back(read_tree(in));
    }
    for(int i=0; i<metadatas; ++i)
    {
        in >> current;
        N.metadatas.push_back(current);
    }

    return N;
}

int value(node N)
{
    int sum=0;
    if (N.children.size() == 0)
    {
        for(int n : N.metadatas)
            sum += n;
        return sum;
    }
    else
    {
        for(int n : N.metadatas)
        {
            if(n<=N.children.size())
                sum += value(N.children[n-1]);
        }
        return sum;
    }
}

int main()
{
    ifstream in;
	string line, str;

	// reading input
	in.open("input.txt");
	node N = read_tree(in);
    in.close();

    cout << value(N);

    return 0;
}
