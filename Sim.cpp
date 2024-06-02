#include "Sim.h"
#include "R.h"
#include "Bf.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

void simulateBattle(BattleField &bf, Robot *robots[], int numRobots, int battlefieldLength, int battlefieldHeight, int numTurns)
{
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    for (int turn = 0; turn < numTurns; ++turn)
    {
        cout << "Turn " << turn + 1 << ":\n";

        for (int i = 0; i < numRobots; ++i)
        {
            Robot *robot = robots[i];

            if (RoboCop *robocop = dynamic_cast<RoboCop *>(robot))
            {
                if (robocop->getlives() > 0)
                {
                    robocop->look(0, 0);
                    robocop->move();
                    robocop->shoot();
                    robocop->shoot();
                    robocop->shoot();

                    if (robocop->getkills() >= 3)
                    {
                        robots[i] = new TerminatorRoboCop(bf, robocop->getname(), robocop->getx(), robocop->gety());
                        delete robocop; // Clean up the old RoboCop instance
                        cout << robots[i]->getname() << " has upgraded to TerminatorRoboCop!!" << endl;
                    }
                }
            }
            else if (Terminator *terminator = dynamic_cast<Terminator *>(robot))
            {
                if (terminator->getlives() > 0)
                {
                    terminator->look(0, 0);
                    terminator->step();

                    if (terminator->getkills() >= 3)
                    {
                        robots[i] = new TerminatorRoboCop(bf, terminator->getname(), terminator->getx(), terminator->gety());
                        delete terminator; // Clean up the old RoboCop instance
                        cout << robots[i]->getname() << " has upgraded to TerminatorRoboCop!!" << endl;
                    }
                }
            }
            else if (TerminatorRoboCop *terminatorRoboCop = dynamic_cast<TerminatorRoboCop *>(robot))
            {
                if (terminatorRoboCop->getlives() > 0)
                {
                    terminatorRoboCop->look(0, 0);
                    terminatorRoboCop->step();
                    terminatorRoboCop->shoot();
                    terminatorRoboCop->shoot();
                    terminatorRoboCop->shoot();

                    if (terminatorRoboCop->getkills() >= 3)
                    {
                        robots[i] = new UltimateRobot(bf, terminatorRoboCop->getname(), terminatorRoboCop->getx(), terminatorRoboCop->gety());
                        delete terminatorRoboCop; // Clean up the old RoboCop instance
                        cout << robots[i]->getname() << " has upgraded to UltimateRobot!!" << endl;
                    }
                }
            }
            else if (BlueThunder *bluethunder = dynamic_cast<BlueThunder *>(robot))
            {
                if (bluethunder->getlives() > 0)
                {
                    bluethunder->clockshoot();

                    if (bluethunder->getkills() >= 3)
                    {
                        robots[i] = new Madbot(bf, bluethunder->getname(), bluethunder->getx(), bluethunder->gety());
                        delete bluethunder; // Clean up the old RoboCop instance
                        cout << robots[i]->getname() << " has upgraded to Madbot!!" << endl;
                    }
                }
            }
            else if (Madbot *madbot = dynamic_cast<Madbot *>(robot))
            {
                if (madbot->getlives() > 0)
                {
                    madbot->randshoot();

                    if (madbot->getkills() >= 3)
                    {
                        robots[i] = new RoboTank(bf, madbot->getname(), madbot->getx(), madbot->gety());
                        delete madbot; // Clean up the old RoboCop instance
                        cout << robots[i]->getname() << " has upgraded to RoboTank!!" << endl;
                    }
                }
            }
            else if (RoboTank *robotank = dynamic_cast<RoboTank *>(robot))
            {
                if (robotank->getlives() > 0)
                {
                    robotank->randshootpro();

                    if (robotank->getkills() >= 3)
                    {
                        robots[i] = new UltimateRobot(bf, robotank->getname(), robotank->getx(), robotank->gety());
                        delete robotank; // Clean up the old RoboCop instance
                        cout << robots[i]->getname() << " has upgraded to RoboTank!!" << endl;
                    }
                }
            }
            else if (UltimateRobot *ultimaterobot = dynamic_cast<UltimateRobot *>(robot))
            {
                if (ultimaterobot->getlives() > 0)
                {
                    ultimaterobot->look(0, 0);
                    ultimaterobot->step();
                    ultimaterobot->randshootpro();
                    ultimaterobot->randshootpro();
                    ultimaterobot->randshootpro();
                }
            }
        }

        // Display the battlefield after each turn
        bf.display();
        cout << endl;
    }
}
