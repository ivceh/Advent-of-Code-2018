#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
using namespace std;

void execute_command(array<int, 4> &REG, string s, int A, int B, int C)
{
    if (C >= 4)
        throw invalid_argument("Register index too high!");

    if (s == "addr")
    {
        if (A>=4 || B>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = REG[A] + REG[B];
    }
    else if (s == "addi")
    {
        if (A>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = REG[A] + B;
    }
    else if (s == "mulr")
    {
        if (A>=4 || B>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = REG[A] * REG[B];
    }
    else if (s == "muli")
    {
        if (A>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = REG[A] * B;
    }
    else if (s == "banr")
    {
        if (A>=4 || B>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = REG[A] & REG[B];
    }
    else if (s == "bani")
    {
        if (A>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = REG[A] & B;
    }
    else if (s == "borr")
    {
        if (A>=4 || B>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = REG[A] | REG[B];
    }
    else if (s == "bori")
    {
        if (A>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = REG[A] | B;
    }
    else if (s == "setr")
    {
        if (A>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = REG[A];
    }
    else if (s == "seti")
    {
        REG[C] = A;
    }
    else if (s == "gtir")
    {
        if (B>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = (A > REG[B]) ? 1 : 0;
    }
    else if (s == "gtri")
    {
        if (A>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = (REG[A] > B) ? 1 : 0;
    }
    else if (s == "gtrr")
    {
        if (A>=4 || B>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = (REG[A] > REG[B]) ? 1 : 0;
    }
    else if (s == "eqir")
    {
        if (B>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = (A == REG[B]) ? 1 : 0;
    }
    else if (s == "eqri")
    {
        if (A>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = (REG[A] == B) ? 1 : 0;
    }
    else if (s == "eqrr")
    {
        if (A>=4 || B>=4)
            throw invalid_argument("Register index too high!");
        REG[C] = (REG[A] == REG[B]) ? 1 : 0;
    }
    else
        throw invalid_argument("Unknown command string \"" + s + "\"!");
}

bool validate_behaviour(array<int, 4> REG1, string s, int A, int B, int C, array<int, 4> const &REG2)
{
    try
    {
        execute_command(REG1, s, A, B, C);
        return REG1 == REG2;
    }
    catch(const invalid_argument &ex)
    {
        return false;
    }
}

int count_possible_opcodes(array<int, 4> const &REG1, int A, int B, int C, array<int, 4> const &REG2)
{
    int cnt = 0;
    for(string s : {"addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori",
                    "setr", "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr"})
    {
        if (validate_behaviour(REG1, s, A, B, C, REG2))
            ++cnt;
    }
    return cnt;
}

int main()
{
    ifstream in;
	string line, str;
	int opnum, A, B, C, result=0;
	array<int, 4> REG1, REG2;

	// reading input
	in.open("input.txt");
	while (getline(in, line) && sscanf(line.c_str(), "Before: [%d, %d, %d, %d]", &REG1[0], &REG1[1], &REG1[2], &REG1[3]) == 4)
    {
        getline(in, line);
        sscanf(line.c_str(), "%d %d %d %d", &opnum, &A, &B, &C);
        getline(in, line);
        sscanf(line.c_str(), "After: [%d, %d, %d, %d]", &REG2[0], &REG2[1], &REG2[2], &REG2[3]);
        getline(in, line); // empty line

        if(count_possible_opcodes(REG1, A, B, C, REG2) > 3)
            ++result;
    }
    in.close();

    cout << result;

    return 0;
}
