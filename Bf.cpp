#include "Bf.h"
#include "R.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
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

string BattleField::invalid() const
{
    return "Invalid coordinate, out of range.\n";
}

void BattleField::set(Robot *robot, int x, int y)
{
    if (range(x, y))
    {
        obj[y][x] = robot;
        obj[y][x]->setxy(x, y);
    }
    else
        cout << invalid();
}

void BattleField::respawn(int x, int y)
{
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
    cout << endl << "RESPAWN ALERT  -  " << obj[newy][newx]->getname() << " has respawned at (" << newx << ", " << newy << ")." << endl;
}

void BattleField::remove(int x, int y)
{
    if (!range(x, y))
    {
        cout << invalid();
        return;
    }
    if (obj[y][x] == nullptr)
        throw "Shoot: No robot";
    obj[y][x]->reduce();
    if (obj[y][x]->getlives() <= 0)
        terminate(x, y);
    else
        respawn(x, y);
}

void BattleField::terminate(int x, int y)
{
    if (range(x, y))
    {
        obj[y][x] = nullptr;
    }
    else
        cout << invalid();
}

void BattleField::display() const
{
    cout << "    ";
    for (int i = 0; i < length; i++) // display the field upperline
    {
        if (i != length - 1) // not last unit more lines
            cout << "___";
        else // last unit one line given only
            cout << "_";
    }
    cout << endl;
    for (int i = height - 1; i >= 0; i--) // outer loop start from the most height
    {
        if (i < 10)             // if 1 signifcant figure more spaces before opening
            cout << i << "  |"; // display numbering of height
        else
            cout << i << " |";
        for (int j = 0; j < length; j++) // inner loop start from least length
        {
            if (j != length - 1) // not last unit more spaces given
            {
                if (obj[i][j] != nullptr) // validate whether the unit has robot object
                    cout << obj[i][j]->getsymbol() << "  ";
                else
                    cout << " " << "  ";
            }
            else // last unit no space given
            {
                if (obj[i][j] != nullptr) // validate again
                    cout << obj[i][j]->getsymbol();
                else
                    cout << " ";
            }
        }
        cout << "|" << endl; // last row unit closing
    }
    cout << "   |";                  // skip the beginning number display spaces
    for (int i = 0; i < length; i++) // display field lowerline
    {
        if (i != length - 1) // if not last unit more lines
            cout << "___";
        else // last unit less lines with closing
            cout << "_|";
    }
    cout << endl
         << "    ";
    for (int i = 0; i < length; i++) // display the numbering of length
    {
        if (i < 10) // if 1 significant figure more spaces given
            cout << i << "  ";
        else
            cout << i << " ";
    }
    cout << endl;
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