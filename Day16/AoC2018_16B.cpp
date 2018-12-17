#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <set>
using namespace std;

array<set<string>, 16> possibilities;
array<string, 16> opcodes;

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

void validate_possibilties(array<int, 4> const &REG1, int opnum, int A, int B, int C, array<int, 4> &REG2)
{
    int cnt = 0;
    set<string> &Ss = possibilities[opnum];
    set<string>::iterator it = Ss.begin();
    while(it != Ss.end())
    {
        if(validate_behaviour(REG1, *it, A, B, C, REG2))
            ++it;
        else
        {
            set<string>::iterator jt = next(it);
            Ss.erase(it);
            it = jt;
        }
    }
}

void conclude_possiblities()
{
    bool something_concluded;
    do
    {
        something_concluded = false;

        /// If there is only one possible opcode for some number, this opcode is impossible for other numbers.
        for(int i=0; i<16; ++i)
            if(possibilities[i].size() == 1)
            {
                string s = *(possibilities[i].begin());
                for(int j=0; j<16; ++j)
                    if(j!=i && possibilities[j].erase(s)>0)
                        something_concluded = true;
            }

        /// If there is only one possible number for some opcode, this number is impossible for other opcodes.
        for(string s : {"addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori",
                        "setr", "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr"})
        {
            int cnt = 0, num;
            for(int i=0; i<16; ++i)
                if(possibilities[i].count(s)>0)
                {
                    ++cnt;
                    num = i;
                }
            if(cnt == 1 && possibilities[num].size() > 1)
            {
                possibilities[num] = set<string>({s});
                something_concluded = true;
            }
        }
    }
    while(something_concluded);

    for(int i=0; i<16; ++i)
    {
        if(possibilities[i].size() != 1)
            throw runtime_error("Excactly one opcode must be possible for each number!");
        opcodes[i] = *(possibilities[i].begin());
    }
}

int main()
{
    ifstream in;
	string line, str;
	int opnum, A, B, C, result=0;
	array<int, 4> REG1, REG2;

	possibilities.fill(set<string>({"addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori",
                                    "setr", "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr"}));

	// reading input
	in.open("input.txt");
	while (getline(in, line) && sscanf(line.c_str(), "Before: [%d, %d, %d, %d]", &REG1[0], &REG1[1], &REG1[2], &REG1[3]) == 4)
    {
        getline(in, line);
        sscanf(line.c_str(), "%d %d %d %d", &opnum, &A, &B, &C);
        getline(in, line);
        sscanf(line.c_str(), "After: [%d, %d, %d, %d]", &REG2[0], &REG2[1], &REG2[2], &REG2[3]);
        getline(in, line); // empty line

        validate_possibilties(REG1, opnum, A, B, C, REG2);
    }

    conclude_possiblities();

    array<int, 4> REG({0,0,0,0});

    while (getline(in, line))
    {
        if (!line.empty())
        {
            istringstream istr(line);
            istr >> opnum >> A >> B >> C;
            execute_command(REG, opcodes[opnum], A, B, C);
        }
    }
    in.close();

    cout << REG[0];

    return 0;
}
