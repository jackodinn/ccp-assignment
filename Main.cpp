#include "Bf.h"
#include "R.h"
#include "Sim.h"
#include <iostream>
#include <ostream>
using namespace std;

int main()
{
    ofstream file;
    file.open("battlefieldlog.txt", ios::trunc);
    // Assuming a battlefield size and a set of robots are created and initialized here
    int battlefieldLength = 5;
    int battlefieldHeight = 5;
    BattleField bf(battlefieldLength, battlefieldHeight);

    // Create an array of robots
    int numRobots = 3;
    Robot *robots[numRobots];

    // Initialize robots with different types and positions
    robots[0] = new RoboCop(bf, "Robot 1 - Robocop", 1, 3);
    robots[1] = new Terminator(bf, "Robot 2 - Terminator", 4, 2);
    robots[2] = new BlueThunder(bf, "Robot 3 - Bluethunder", 3, 0);
    

    // Simulate the battle for a number of turns
    int numTurns = 10;
    simulateBattle(bf, robots, numRobots, battlefieldLength, battlefieldHeight, numTurns);
    // Clean up
    for (int i = 0; i < numRobots; ++i)
    {
        delete robots[i];
    }

    return 0;
}

/* cmd command line compile

g++ -g Main.cpp Bf.cpp R.cpp Sim.cpp -o main.exe
.\a

*/
