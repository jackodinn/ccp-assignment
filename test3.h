#ifndef TEST3_H
#define TEST3_H
#include <iostream>
using namespace std;

class Battlefield
{
protected:
    int width;
    int height;
    char** grid; // grid<vector<vector(char)>>

public:
    Battlefield(int m, int n);
    void display();
    void updatePosition(int oldX, int old, int newX, int newY, char symbol);
    bool isOccupied(int x, int y);
    bool isInBounds(int x, int y);
    int getwidth();
    int getheight();
    
};

class Robot { // robot take turns, start from look, thn move and lastly fire
protected:
    int posX;
    int posY;
    string name;
    char symbol;
    Battlefield battlefield;
    int lives;
public:
    Robot(int x, int y, string name, char symbol, Battlefield* battlefiled);
    virtual void look(int x, int y) = 0;
    virtual void move() = 0;
    virtual void fire(int x, int y) = 0;
    void takeTurn();
};

class RoboCop {
private:
    int kills;
public:
    RoboCop(int x, int y, string name, char symbol, Battlefield* battlefield);
    virtual void look(int x, int y);
    virtual void move();
    virtual void fire(int x, int y);
};

class Terminator {
private:
    int kills;
public:
    Terminator(int x, int y, string name, char symbol, Battlefield* battlefield);
    virtual void look(int x, int y);
    virtual void move();
    virtual void fire(int x, int y);
};

class TerminatorRoboCop {
// inherit from robocop and terminator
private:
    int kills;
public:
    TerminatorRoboCop(int x, int y, string name, char symbol, Battlefield* battlefield);
    virtual void look(int x, int y);
    virtual void move();
    virtual void fire(int x, int y);
};

class BlueThunder {
private:
    int kills;
    int fireDirection;
public:
    BlueThunder(int x, int y, string name, char symbol, Battlefield* battlefield);
    virtual void look(int x, int y);
    virtual void move();
    virtual void fire(int x, int y);
};

class MadBot {
private:
    int kills;
public:
    MadBot(int x, int y, string name, char symbol, Battlefield* battlefield);
    virtual void look(int x, int y);
    virtual void move();
    virtual void fire(int x, int y);
};

class RoboTank {
private:
    int kills;
public:
    RoboTank(int x, int y, string name, char symbol, Battlefield* battlefield);
    virtual void look(int x, int y);
    virtual void move();
    virtual void fire(int x, int y);
};

class UltimateRobot {
// inherit from terminatorrobocop
public:
    UltimateRobot(int x, int y, string name, char symbol, Battlefield* battlefield);
    void takeTurn();
};

/* file 
read battlefield dimension
set(m, n)
read step
set steps
read robots:
- for each robots:
    - set type, name, position
    - if position is random, generate random position

*/

/* main solution loop
load configuration form file
initialize battlefield with dimension m*n
initialize robots based on configuration
for each step (from 1 to 300):
- display step number
- for each robot:
    - robot takes turn
- display battlefield
end simulation

*/

#endif