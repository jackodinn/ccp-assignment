#ifndef SIM_H
#define SIM_H

#include "Bf.h" // Assuming the BattleField class definition
#include "R.h" // Assuming the Robot class definition
#include <ostream>
#include <fstream>
#include <string>

void calcTurns(int turns);
void evolveRobocop(std::string name);
void evolveTerminator(std::string name);
void evolveTerminatorRobocop(std::string name);
void evolveBluethunder(std::string name);
void evolveMadbot(std::string name);
void evolveRobotank(std::string name);
void simulateBattle(BattleField &bf, Robot* robots[], int numRobots, int battlefieldLength, int battlefieldHeight, int numTurns);

#endif // SIMULATION_H
