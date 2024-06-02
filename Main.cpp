#include "Bf.h"
#include "R.h"
#include "Sim.h"
#include <iostream>
using namespace std;

int main()
{
    // Assuming a battlefield size and a set of robots are created and initialized here
    int battlefieldLength = 10;
    int battlefieldHeight = 10;
    BattleField bf(battlefieldLength, battlefieldHeight);

    // Create an array of robots
    int numRobots = 3;
    Robot *robots[numRobots];

    // Initialize robots with different types and positions
    robots[0] = new RoboCop(bf, "Robocop", 1, 3);
    robots[1] = new Terminator(bf, "Terminator", 6, 2);
    robots[2] = new BlueThunder(bf, "Bluethunder", 3, 9);

    // Simulate the battle for a number of turns
    int numTurns = 50;
    simulateBattle(bf, robots, numRobots, battlefieldLength, battlefieldHeight, numTurns);

    // Clean up
    for (int i = 0; i < numRobots; ++i)
    {
        delete robots[i];
    }

    return 0;
}

/* cmd command line compile

g++ -g Main.cpp Bf.cpp R.cpp Sim.cpp -o a.exe
.\a

*/