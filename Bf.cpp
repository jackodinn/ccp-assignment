#include "Bf.h"
#include "R.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

BattleField::BattleField(int x, int y) : length(x), height(y)
{
    obj = new Robot **[height];
    for (int i = 0; i < height; i++)
    {
        obj[i] = new Robot *[length];
        for (int j = 0; j < length; j++)
        {
            obj[i][j] = nullptr;
        }
    }
}

BattleField::~BattleField()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < length; j++)
        {
            delete obj[i][j];
        }
        delete[] obj[i];
    }
    delete[] obj;
}

bool BattleField::range(int x, int y) const
{
    return (x >= 0 && x < length && y >= 0 && y < height);
}

string BattleField::invalid() const // needs a prompt for output into text file purposes
{
    return "Invalid coordinate, out of range.\n";
}

void BattleField::set(Robot *robot, int x, int y)
{
    ofstream outfile;
    outfile.open("battlefieldlog.txt", ios::app);
    if (range(x, y))
    {
        obj[y][x] = robot;
        obj[y][x]->setxy(x, y);
    }
    else
    {
        cout << invalid();
        outfile << invalid();
    }
    outfile.close();
}

void BattleField::respawn(int x, int y)
{
    ofstream outfile;
    outfile.open("battlefieldlog.txt", ios::app);
    auto temp = obj[y][x];
    int newx;
    int newy;
    do
    {
        newx = rand() % length;
        newy = rand() % height;
    } while (!range(newx, newy) || obj[newy][newx] != nullptr);
    set(obj[y][x], newx, newy);
    terminate(x, y);
    cout << endl
         << "RESPAWN ALERT  -  " << obj[newy][newx]->getname() << " has respawned at (" << newx << ", " << newy << ")." << endl;
    outfile << "RESPAWN ALERT  -  " << obj[newy][newx]->getname() << " has respawned at (" << newx << ", " << newy << ")." << endl;
    outfile.close();
}

void BattleField::remove(int x, int y)
{
    ofstream outfile;
    outfile.open("battlefieldlog.txt", ios::app);
    if (!range(x, y))
    {
        cout << invalid();
        outfile << invalid();
        return;
    }
    if (obj[y][x] == nullptr)
        throw "Shoot: No robot";
    obj[y][x]->reduce();
    if (obj[y][x]->getlives() <= 0)
        terminate(x, y);
    else
    {
        respawn(x, y);
    }
    outfile.close();
}

void BattleField::terminate(int x, int y)
{
    ofstream outfile;
    outfile.open("battlefieldlog.txt", ios::app);
    if (range(x, y))
    {
        obj[y][x] = nullptr;
    }
    else
    {
        cout << invalid();
        outfile << invalid();
    }
    outfile.close();
}

void BattleField::display(ostream &out) const
{
    out << "    ";
    for (int i = 0; i < length; i++) // display the field upperline
    {
        if (i != length - 1) // not last unit more lines
            out << "___";
        else // last unit one line given only
            out << "_";
    }
    out << endl;
    for (int i = height - 1; i >= 0; i--) // outer loop start from the most height
    {
        if (i < 10)            // if 1 signifcant figure more spaces before opening
            out << i << "  |"; // display numbering of height
        else
            out << i << " |";
        for (int j = 0; j < length; j++) // inner loop start from least length
        {
            if (j != length - 1) // not last unit more spaces given
            {
                if (obj[i][j] != nullptr) // validate whether the unit has robot object
                    out << obj[i][j]->getsymbol() << "  ";
                else
                    out << " " << "  ";
            }
            else // last unit no space given
            {
                if (obj[i][j] != nullptr) // validate again
                    out << obj[i][j]->getsymbol();
                else
                    out << " ";
            }
        }
        out << "|" << endl; // last row unit closing
    }
    out << "   |";                   // skip the beginning number display spaces
    for (int i = 0; i < length; i++) // display field lowerline
    {
        if (i != length - 1) // if not last unit more lines
            out << "___";
        else // last unit less lines with closing
            out << "_|";
    }
    out << endl
        << "    ";
    for (int i = 0; i < length; i++) // display the numbering of length
    {
        if (i < 10) // if 1 significant figure more spaces given
            out << i << "  ";
        else
            out << i << " ";
    }
    out << endl;
}

Robot *BattleField::getobj(int x, int y) const
{
    if (range(x, y))
        return obj[y][x];
    else
        return nullptr;
}

int BattleField::getlength() const
{
    return length;
}

int BattleField::getheight() const
{
    return height;
}

void BattleField::updateRobot(Robot *newRobot)  //update robot, mainly for evolving
{
    // Find and remove the old robot from the grid
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < length; ++j)
        {
            if (obj[i][j] && obj[i][j]->getname() == newRobot->getname())
            {
                obj[i][j] = nullptr; // Remove old robot from the grid
                break;
            }
        }
    }

    // Add the new robot to the grid
    int newX = newRobot->getx();
    int newY = newRobot->gety();
    if (range(newX, newY))
    {
        obj[newY][newX] = newRobot;
    }
    else
    {
        cout << invalid();
        ofstream outfile;
        outfile.open("battlefieldlog.txt", ios::app);
        outfile << invalid();
        outfile.close();
    }
}
