#ifndef R_H
#define R_H

#include <string>

class BattleField;

class Robot
{
protected:
    BattleField &bf;
    std::string name;
    int xaxis;
    int yaxis;
    int lives;
    char symbol;

public:
    Robot(BattleField &obj, std::string n, int x, int y);
    ~Robot();

    void setsymbol(char s);
    void reduce();
    std::string getname() const;
    int getx() const;
    int gety() const;
    int getlives() const;
    char getsymbol() const;
};

class Shooting : virtual public Robot
{
public:
    Shooting(BattleField &obj, std::string n, int x, int y);

    void shoot(int x, int y);
};

class Moving : virtual public Robot
{
public:
    Moving(BattleField &obj, std::string n, int x, int y);

    void move();
};

class Stepping : virtual public Robot
{
public:
    Stepping(BattleField &obj, std::string n, int x, int y);

    void step();
};

class Looking : virtual public Robot
{
public:
    Looking(BattleField &obj, std::string n, int x, int y);

    void look(int x, int y);
};

class RoboCop : public Moving, public Shooting, public Looking
{
public:
    RoboCop(BattleField &obj, std::string n, int x, int y);
};

class Terminator : public Stepping, public Looking
{
public:
    Terminator(BattleField &obj, std::string n, int x, int y);
};

class TerminatorRoboCop : public Stepping, public Shooting, public Looking
{
public:
    TerminatorRoboCop(BattleField &obj, std::string n, int x, int y);
};
#endif