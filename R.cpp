#include "R.h"
#include "Bf.h"
#include <ctime>
#include <iostream>
using namespace std;

Robot::Robot(BattleField &obj, string n, int x, int y) : bf(obj), name(n), lives(3), symbol('0'), kills(0)
{
    setxy(x, y);
    bf.set(this, xaxis, yaxis);
}

Robot::~Robot()
{
    bf.terminate(xaxis, yaxis);
}

void Robot::setxy(int x, int y)
{
    xaxis = x;
    yaxis = y;
}

void Robot::setsymbol(char s)
{
    symbol = s;
}

void Robot::reduce()
{
    lives--;
}

void Robot::increkill()
{
    kills++;
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

int Robot::getkills() const
{
    return kills;
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
        if (bf.getobj(x, y) != nullptr)
        {
            increkill();
            cout << "Robot at position (" << x << ", " << y << ") has been shooted." << endl;
        }
        bf.remove(x, y);
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

void Stepping::step(int x, int y)
{
    try
    {
        if (bf.getobj(x, y) != nullptr)
        {
            cout << getname() << " has stepped on a robot at position (" << x << ", " << y << ")." << endl;
        }
        bf.remove(x, y);
    }
    catch (...)
    {
        cout << getname() << " has moved to position (" << x << ", " << y << ")." << endl;
    }
    bf.terminate(xaxis, yaxis);
    xaxis = x;
    yaxis = y;
    bf.set(this, xaxis, yaxis);
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
    if (!bf.range(rangex, rangey))
    {
        cout << bf.invalid();
        return;
    }
    cout << getname() << " has looked into position (" << rangex << ", " << rangey << ")." << endl;
    for (int i = rangey - 1; i <= rangey + 1; i++)
    {
        for (int j = rangex - 1; j <= rangex + 1; j++)
        {
            if (bf.range(j, i) && !(i == yaxis && j == xaxis))
            {
                if (bf.getobj(j, i) != nullptr)
                {
                    enemy++;
                    setdetxy(j, i);
                }
            }
        }
    }
    if (enemy != 0)
    {
        cout << "The position nearby contains " << enemy << " robot(s)." << endl;
        setdetect(1);
    }
    else
    {
        cout << "The position nearby does not contain any robot(s)." << endl;
        setdetect(0);
    }
}

void Looking::setdetect(bool b)
{
    detect = b;
}

void Looking::setdetxy(int x, int y)
{
    detectx = x;
    detecty = y;
}

bool Looking::getdetect() const
{
    return detect;
}

int Looking::getdetectx() const
{
    return detectx;
}

int Looking::getdetecty() const
{
    return detecty;
}

RoboCop::RoboCop(BattleField &obj, string n, int x, int y) : Robot(obj, n, x, y), Moving(obj, n, x, y), Shooting(obj, n, x, y), Looking(obj, n, x, y)
{
    setsymbol('r');
}

void RoboCop::shoot()
{
    int x;
    int y;
    do
    {
        x = rand() % bf.getlength();
        y = rand() % bf.getheight();
    } while (!bf.range(x, y) || (x == xaxis && y == yaxis) || abs(x) + abs(y) > 10);
    Shooting::shoot(x, y);
}

Terminator::Terminator(BattleField &obj, std::string n, int x, int y) : Robot(obj, n, x, y), Stepping(obj, n, x, y), Looking(obj, n, x, y)
{
    setsymbol('t');
}

void Terminator::step()
{
    int newX;
    int newY;
    if (getdetect())
    {
        newX = getdetectx();
        newY = getdetecty();
    }
    else
    {
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
    }
    Stepping::step(newX, newY);
}

TerminatorRoboCop::TerminatorRoboCop(BattleField &obj, std::string n, int x, int y) : Robot(obj, n, x, y), RoboCop(obj, n, x, y), Terminator(obj, n, x, y)
{
    setsymbol('T');
}

void TerminatorRoboCop::look(int x, int y)
{
    RoboCop::look(x, y);
}

BlueThunder::BlueThunder(BattleField &obj, std::string n, int x, int y) : Robot(obj, n, x, y), Shooting(obj, n, x, y)
{
    setsymbol('b');
}

void BlueThunder::clockshoot()
{
    static int i = 0;
    int shootx;
    int shooty;
    do
    {
        shootx = xaxis;
        shooty = yaxis;
        if (i == 0)
        {
            shooty += 1;
            i++;
        }
        else if (i == 1)
        {
            shootx += 1;
            shooty += 1;
            i++;
        }
        else if (i == 2)
        {
            shootx += 1;
            i++;
        }
        else if (i == 3)
        {
            shootx += 1;
            shooty -= 1;
            i++;
        }
        else if (i == 4)
        {
            shooty -= 1;
            i++;
        }
        else if (i == 5)
        {
            shootx -= 1;
            shooty -= 1;
            i++;
        }
        else if (i == 6)
        {
            shootx -= 1;
            i++;
        }
        else if (i == 7)
        {
            shootx -= 1;
            shooty += 1;
            i = 0;
        }
    } while (!bf.range(shootx, shooty));
    shoot(shootx, shooty);
};

Madbot::Madbot(BattleField &obj, std::string n, int x, int y) : Robot(obj, n, x, y), Shooting(obj, n, x, y)
{
    setsymbol('M');
}

void Madbot::randshoot()
{
    int x;
    int y;
    do
    {
        x = (rand() % 3) - 1;
        y = (rand() % 3) - 1;
    } while ((x == 0 && y == 0) || !bf.range(xaxis + x, yaxis + y));
    shoot(xaxis + x, yaxis + y);
}

RoboTank::RoboTank(BattleField &obj, std::string n, int x, int y) : Robot(obj, n, x, y), Shooting(obj, n, x, y)
{
    setsymbol('R');
}

void RoboTank ::randshootpro()
{
    int x;
    int y;
    do
    {
        x = rand() % bf.getlength();
        y = rand() % bf.getheight();
    } while ((x == xaxis && y == yaxis) || !bf.range(x, y));
    shoot(x, y);
}

UltimateRobot::UltimateRobot(BattleField &obj, std::string n, int x, int y) : Robot(obj, n, x, y), TerminatorRoboCop(obj, n, x, y), RoboTank(obj, n, x, y)
{
    setsymbol('U');
}

