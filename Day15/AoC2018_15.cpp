#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <queue>
using namespace std;

#define x first
#define y second
#define coord pair<int,int>

array<coord, 4> adjacent_cells(coord c)
{
    return array<coord, 4>({coord(c.x-1,c.y), coord(c.x, c.y-1), coord(c.x,c.y+1), coord(c.x+1, c.y)});
}

bool adjacent(coord c1, coord c2)
{
    if(c1.x == c2.x)
        return c1.y == c2.y - 1 || c1.y == c2.y + 1;
    else if(c1.x == c2.x - 1 || c1.x == c2.x + 1)
        return c1.y == c2.y;
    else
        return false;
}

class battle
{
    vector<string> grid;
    int current_round = 0, game_over_full_rounds, elf_attack_power=3, goblin_attack_power=3;
    bool game_over = false;

public:
    map<coord, int> elves, goblins;

    battle(int elf_attack_power, int goblin_attack_power)
    {
        this->elf_attack_power = elf_attack_power;
        this->goblin_attack_power = goblin_attack_power;
    }

    char& grid_value(const coord &c)
    {
        return grid[c.x][c.y];
    }

    void read_input(istream &in)
    {
        string line;
        while (getline(in, line))
        {
            if (!line.empty())
                grid.push_back(line);
        }
    }

    void start_battle()
    {
        for(int i=0; i<grid.size(); ++i)
            for(int j=0; j<grid[i].size(); ++j)
            {
                switch(grid[i][j])
                {
                case 'E':
                    elves[coord(i,j)] = 200;
                    break;
                case 'G':
                    goblins[coord(i,j)] = 200;
                }
            }

        current_round = 0;
        game_over = false;
    }

    vector<coord> free_adjacent_cells(coord c)
    {
        vector<coord> V;
        for(coord c2: adjacent_cells(c))
            if(grid_value(c2)=='.')
                V.push_back(c2);
        return V;
    }

    struct shortest_path
    {
        int distance;
        coord previous;

        shortest_path(int distance=0, coord previous=coord(-1,-1))
        {
            this->distance = distance;
            this->previous = previous;
        }
    };
    map<coord, shortest_path> breadth_first_search(coord c)
    {
        queue<coord> Q({c});
        map<coord, shortest_path> M;
        M[c] = shortest_path(0, coord(-1,-1));

        while(!Q.empty())
        {
            coord c2 = Q.front();
            Q.pop();
            for (coord c3 : free_adjacent_cells(c2))
                if(M.count(c3) == 0)
                {
                    Q.push(c3);
                    M[c3] = shortest_path(M[c2].distance+1, c2);
                }
        }

        return M;
    }

    coord next_position(coord c, set<coord> goals)
    {
        map<coord, shortest_path> M = breadth_first_search(c);

        int shortest_dist = -1;
        coord goal(-1,-1);

        for (coord c2 : goals)
        {
            if(M.count(c2)>0 && (shortest_dist==-1 || M[c2].distance<shortest_dist))
            {
                shortest_dist = M[c2].distance;
                goal = c2;
            }
        }

        if(shortest_dist == -1)
            return c;
        else
        {
            coord previous = M[goal].previous;
            while(previous != c)
            {
                goal = previous;
                previous = M[goal].previous;
            }
            return goal;
        }
    }

    coord step_unit(coord c, set<coord> *all_units)
    {
        map<coord, int> *friends, *opponents;
        char my_letter, opponent_letter;
        int attack_power;
        switch(grid_value(c))
        {
        case 'E':
            friends = &elves;
            opponents = &goblins;
            my_letter = 'E';
            opponent_letter = 'G';
            attack_power = elf_attack_power;
            break;
        case 'G':
            friends = &goblins;
            opponents = &elves;
            my_letter = 'G';
            opponent_letter = 'E';
            attack_power = goblin_attack_power;
            break;
        default:
            throw invalid_argument("Coordinate is neither elf nor goblin!");
        }

        if(opponents->empty())
        {
            game_over = true;
            game_over_full_rounds = current_round;
            return c;
        }

        bool already_there = false;
        set<coord> goals;
        for(pair<coord, int> const &p : *opponents)
        {
            if(adjacent(c, p.first))
            {
                already_there = true;
                break;
            }
            for(coord c2 : free_adjacent_cells(p.first))
                goals.insert(c2);
        }

        coord c2;
        if(already_there)
            c2 = c;
        else
        {
            c2 = next_position(c, goals);
            if(c2 != c)
            {
                grid_value(c) = '.';
                grid_value(c2) = my_letter;
                (*friends)[c2] = (*friends)[c];
                friends->erase(c);
            }
        }

        coord weak_opp_coord(-1,-1);
        int weak_opp_HP = 300;
        for(coord c3 : adjacent_cells(c2))
            if(grid_value(c3) == opponent_letter && (*opponents)[c3]<weak_opp_HP)
            {
                weak_opp_coord = c3;
                weak_opp_HP = (*opponents)[c3];
            }
        if(weak_opp_HP<300)
            if(((*opponents)[weak_opp_coord] -= attack_power) <= 0)
            {
                opponents->erase(weak_opp_coord);
                all_units->erase(weak_opp_coord);
                grid_value(weak_opp_coord) = '.';
            }
    }

    void step_battle()
    {
        set<coord> all_units;
        for(auto const &p : elves)
            all_units.insert(p.first);
        for(auto const &p : goblins)
            all_units.insert(p.first);

        for(coord c : all_units)
            if(grid_value(c) != '.')
                step_unit(c, &all_units);

        ++current_round;
    }

    void step_all_rounds()
    {
        while(!game_over)
            step_battle();
    }

    int battle_outcome()
    {
        int all_HP = 0;
        for(pair<coord, int> const &p : elves)
            all_HP += p.second;
        for(pair<coord, int> const &p : goblins)
            all_HP += p.second;
        return game_over_full_rounds * all_HP;
    }
};

int main()
{
    ifstream in;
    int elf_attack_power=3, goblin_attack_power=3, start_elves_num, end_elves_num, outcome;

    battle B(elf_attack_power, goblin_attack_power);

	// reading input
	in.open("input.txt");
	B.read_input(in);
    in.close();

    B.start_battle();
    B.step_all_rounds();
    cout << "Part One: " << B.battle_outcome() << endl;

    do
    {
        ++elf_attack_power;
        battle B(elf_attack_power, goblin_attack_power);

        // reading input
        in.open("input.txt");
        B.read_input(in);
        in.close();

        B.start_battle();
        start_elves_num = B.elves.size();
        B.step_all_rounds();
        end_elves_num = B.elves.size();
        outcome = B.battle_outcome();
    }
    while(start_elves_num > end_elves_num);

    cout << "Part Two: " << outcome << endl;

    return 0;
}
