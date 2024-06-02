#ifndef SIM_H
#define SIM_H

#include "Bf.h" // Assuming the BattleField class definition
#include "R.h" // Assuming the Robot class definition

void simulateBattle(BattleField &bf, Robot* robots[], int numRobots, int battlefieldLength, int battlefieldHeight, int numTurns);

#endif // SIMULATION_H
