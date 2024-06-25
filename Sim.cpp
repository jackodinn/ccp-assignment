#include "Sim.h"
#include "R.h"
#include "Bf.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void calcTurns(int turns)
{
    ofstream file;
    file.open("battlefieldlog.txt", ios::app);
    std::cout << "Turn " << turns << endl
              << endl;
    file << endl
         << "Turn  " << turns << endl
         << endl;
    file.close();
}

void evolveRobocop(string name)
{
    ofstream file;
    file.open("battlefieldlog.txt", ios::app);
    file << "EVOLVE ALERT  -  " << name << " has upgraded to TerminatorRoboCop!!" << endl;
    file.close();
    std::cout << "EVOLVE ALERT  -  " << name << " has upgraded to TerminatorRoboCop!!" << endl;
}

void evolveTerminator(string name)
{
    ofstream file;
    file.open("battlefieldlog.txt", ios::app);
    file << "EVOLVE ALERT  -  " << name << " has upgraded to TerminatorRoboCop!!" << endl;
    file.close();
    std::cout << "EVOLVE ALERT  -  " << name << " has upgraded to TerminatorRoboCop!!" << endl;
}

void evolveTerminatorRobocop(string name)
{
    ofstream file;
    file.open("battlefieldlog.txt", ios::app);
    file << "EVOLVE ALERT  -  " << name << " has upgraded to UltimateRobot!!" << endl;
    file.close();
    std::cout << "EVOLVE ALERT  -  " << name << " has upgraded to UltimateRobot!!" << endl;
}

void evolveBluethunder(string name)
{
    ofstream file;
    file.open("battlefieldlog.txt", ios::app);
    file << "EVOLVE ALERT  -  " << name << " has upgraded to Madbot!!" << endl;
    file.close();
    std::cout << "EVOLVE ALERT  -  " << name << " has upgraded to Madbot!!" << endl;
}

void evolveMadbot(string name)
{
    ofstream file;
    file.open("battlefieldlog.txt", ios::app);
    file << "EVOLVE ALERT  -  " << name << " has upgraded to RoboTank!!" << endl;
    file.close();
    std::cout << "EVOLVE ALERT  -  " << name << " has upgraded to RoboTank!!" << endl;
}

void evolveRobotank(string name)
{
    ofstream file;
    file.open("battlefieldlog.txt", ios::app);
    file << "EVOLVE ALERT  -  " << name << " has upgraded to UltimateRobot!!" << endl;
    file.close();
    std::cout << "EVOLVE ALERT  -  " << name << " has upgraded to UltimateRobot!!" << endl;
}

void simulateBattle(BattleField &bf, Robot *robots[], int numRobots, int battlefieldLength, int battlefieldHeight, int numTurns)
{
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation
    int turns;
    for (turns = 1; turns <= numTurns; turns++)
    {

        calcTurns(turns);

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

                    if (robocop->getkills() >= 1)
                    {
                        string name = robocop->getname();
                        evolveRobocop(name);
                        robots[i] = new TerminatorRoboCop(bf, robocop->getname(), robocop->getx(), robocop->gety());
                        delete robocop;
                        bf.updateRobot(robots[i]);
                    }
                }
            }
            else if (Terminator *terminator = dynamic_cast<Terminator *>(robot))
            {
                if (terminator->getlives() > 0)
                {
                    terminator->look(0, 0);
                    terminator->step();

                    if (terminator->getkills() >= 1)
                    {
                        string name = terminator->getname();
                        evolveTerminator(name);
                        robots[i] = new TerminatorRoboCop(bf, terminator->getname(), terminator->getx(), terminator->gety());
                        delete terminator;
                        bf.updateRobot(robots[i]);
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

                    if (terminatorRoboCop->getkills() >= 1)
                    {
                        string name = terminatorRoboCop->getname();
                        evolveTerminatorRobocop(name);
                        robots[i] = new UltimateRobot(bf, terminatorRoboCop->getname(), terminatorRoboCop->getx(), terminatorRoboCop->gety());
                        delete terminatorRoboCop;
                        bf.updateRobot(robots[i]);
                    }
                }
            }
            else if (BlueThunder *bluethunder = dynamic_cast<BlueThunder *>(robot))
            {
                if (bluethunder->getlives() > 0)
                {
                    bluethunder->clockshoot();

                    if (bluethunder->getkills() >= 1)
                    {
                        string name = bluethunder->getname();
                        evolveBluethunder(name);
                        robots[i] = new Madbot(bf, bluethunder->getname(), bluethunder->getx(), bluethunder->gety());
                        delete bluethunder;
                        bf.updateRobot(robots[i]);
                    }
                }
            }
            else if (Madbot *madbot = dynamic_cast<Madbot *>(robot))
            {
                if (madbot->getlives() > 0)
                {
                    madbot->randshoot();

                    if (madbot->getkills() >= 1)
                    {
                        string name = madbot->getname();
                        evolveMadbot(name);
                        robots[i] = new RoboTank(bf, madbot->getname(), madbot->getx(), madbot->gety());
                        delete madbot;
                        bf.updateRobot(robots[i]);
                    }
                }
            }
            else if (RoboTank *robotank = dynamic_cast<RoboTank *>(robot))
            {
                if (robotank->getlives() > 0)
                {
                    robotank->randshootpro();

                    if (robotank->getkills() >= 1)
                    {
                        string name = robotank->getname();
                        evolveRobotank(name);
                        robots[i] = new UltimateRobot(bf, robotank->getname(), robotank->getx(), robotank->gety());
                        delete robotank;
                        bf.updateRobot(robots[i]);
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
        bf.display(cout);
        ofstream bffile;
        bffile.open("battlefield.txt");
        bf.display(bffile);
        bffile.close();
        cout << endl;
    }
}
