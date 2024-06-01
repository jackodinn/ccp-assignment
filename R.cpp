#include "R.h"
#include "Bf.h"
#include <ctime>
#include <iostream>
using namespace std;

Robot::Robot(BattleField &obj, string n, int x, int y) : bf(obj), name(n), xaxis(x), yaxis(y), lives(3), symbol('0')
{
    bf.set(this, xaxis, yaxis);
}

Robot::~Robot()
{
    bf.terminate(xaxis, yaxis);
}

void Robot::setsymbol(char s)
{
    symbol = s;
}

void Robot::reduce()
{
    lives--;
}

string Robot::getname() const
{
    return name;
}

int Robot::getx() const
{
    return xaxis;
}

int Robot::gety() const
{
    return yaxis;
}

int Robot::getlives() const
{
    return lives;
}

char Robot::getsymbol() const
{
    return symbol;
}

Shooting::Shooting(BattleField &obj, string n, int x, int y) : Robot(obj, n, x, y)
{
    setsymbol('S');
}

void Shooting::shoot(int x, int y)
{
    try
    {
        cout << getname() << " has shoot at position (" << x << ", " << y << ")." << endl;
        bf.remove(x, y);
        cout << "Robot at position (" << x << ", " << y << ") has been shooted."<< endl;
    }
    catch (...)
    {
        cout << getname() << " has shoot at empty space." << endl;
    }
}

Moving::Moving(BattleField &obj, string n, int x, int y) : Robot(obj, n, x, y)
{
    setsymbol('M');
}

void Moving::move()
{
    int newX;
    int newY;
    do
    {
        newX = getx();
        newY = gety();
        int moves = rand() % 8;
        switch (moves)
        {
        case 0:
            newY++;
            break;
        case 1:
            newX--;
            break;
        case 2:
            newY--;
            break;
        case 3:
            newX++;
            break;
        case 4:
            newX--;
            newY++;
            break;
        case 5:
            newX++;
            newY++;
            break;
        case 6:
            newX--;
            newY--;
            break;
        case 7:
            newX++;
            newY--;
            break;
        }
    } while (!bf.range(newX, newY) || bf.getobj(newX, newY) != nullptr);
    bf.terminate(xaxis, yaxis);
    xaxis = newX;
    yaxis = newY;
    bf.set(this, xaxis, yaxis);
    cout << getname() << " has moved to position (" << xaxis << ", " << yaxis << ")." << endl;
}

Stepping::Stepping(BattleField &obj, string n, int x, int y) : Robot(obj, n, x, y)
{
    setsymbol('s');
}

void Stepping::step()
{
    int newX;
    int newY;
    do
    {
        newX = getx();
        newY = gety();
        int moves = rand() % 8;
        switch (moves)
        {
        case 0:
            newY++;
            break;
        case 1:
            newX--;
            break;
        case 2:
            newY--;
            break;
        case 3:
            newX++;
            break;
        case 4:
            newX--;
            newY++;
            break;
        case 5:
            newX++;
            newY++;
            break;
        case 6:
            newX--;
            newY--;
            break;
        case 7:
            newX++;
            newY--;
            break;
        }
    } while (!bf.range(newX, newY));
    bool step = false;
    if (bf.getobj(newX, newY) != nullptr)
        step = true;
    try
    {
        bf.remove(newX, newY);
    }
    catch (...)
    {
    }
    bf.terminate(xaxis, yaxis);
    xaxis = newX;
    yaxis = newY;
    bf.set(this, xaxis, yaxis);
    if (step)
        cout << getname() << " has stepped robot at position (" << xaxis << ", " << yaxis << ")." << endl;
    else
        cout << getname() << " has moved to position (" << xaxis << ", " << yaxis << ")." << endl;
}

Looking::Looking(BattleField &obj, string n, int x, int y) : Robot(obj, n, x, y)
{
    setsymbol('L');
}

void Looking::look(int x, int y)
{
    int enemy = 0;
    int rangex = xaxis + x;
    int rangey = yaxis + y;
    if (bf.range(rangex, rangey))
        cout << getname() << " has looked into position (" << rangex << ", " << rangey << ")." << endl;
    else
        return;
    for (int i = rangey - 1; i <= rangey + 1; i++)
    {
        for (int j = rangex - 1; j <= rangex + 1; j++)
        {
            if (bf.range(j, i) && (i != xaxis && j != yaxis))
            {
                if (bf.getobj(j, i) != nullptr)
                    enemy++;
            }
        }
    }
    if (enemy != 0)
        cout << "The position nearby contains " << enemy << " robot(s)." << endl;
    else
        cout << "The position nearby does not contain any robot(s)." << endl;
}

RoboCop::RoboCop(BattleField &obj, string n, int x, int y) : Robot(obj, n, x, y), Moving(obj, n, x, y), Shooting(obj, n, x, y), Looking(obj, n, x, y)
{
    setsymbol('r');
}

Terminator::Terminator(BattleField &obj, std::string n, int x, int y) : Robot(obj, n, x, y), Stepping(obj, n, x, y), Looking(obj, n, x, y)
{
    setsymbol('t');
}

TerminatorRoboCop::TerminatorRoboCop(BattleField &obj, std::string n, int x, int y) : Robot(obj, n, x, y), Shooting(obj, n, x, y), Stepping(obj, n, x, y), Looking(obj, n, x, y)
{
    setsymbol('T');
}