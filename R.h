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
    int kills;

public:
    Robot(BattleField &obj, std::string n, int x, int y);
    Robot &operator=(const Robot &other);
    virtual ~Robot();

    void setsymbol(char s);
    void setxy(int x, int y);
    void reduce();
    void increkill();
    std::string getname() const;
    int getx() const;
    int gety() const;
    int getlives() const;
    char getsymbol() const;
    int getkills() const;
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

    void step(int x, int y);
};

class Looking : virtual public Robot
{
protected:
    bool detect;
    int detectx;
    int detecty;

public:
    Looking(BattleField &obj, std::string n, int x, int y);

    void look(int x, int y);
    void setdetect(bool x);
    void setdetxy(int x, int y);
    bool getdetect() const;
    int getdetectx() const;
    int getdetecty() const;
};

class RoboCop : public Moving, public Shooting, public Looking
{
public:
    RoboCop(BattleField &obj, std::string n, int x, int y);
    RoboCop& operator=(const RoboCop &other);

    void shoot();
};

class Terminator : public Stepping, public Looking
{
public:
    Terminator(BattleField &obj, std::string n, int x, int y);
    Terminator &operator=(const Terminator &other);
    void step();
};

class TerminatorRoboCop : public RoboCop, public Terminator
{
public:
    TerminatorRoboCop(BattleField &obj, std::string n, int x, int y);
    TerminatorRoboCop &operator=(const TerminatorRoboCop &other);
    void look(int x, int y);
};

class BlueThunder : public Shooting
{
public:
    BlueThunder(BattleField &obj, std::string n, int x, int y);
    BlueThunder &operator=(const BlueThunder &other);
    void clockshoot();
};

class Madbot : public Shooting
{
public:
    Madbot(BattleField &obj, std::string n, int x, int y);
    Madbot &operator=(const Madbot &other);
    void randshoot();
};

class RoboTank : public Shooting
{
public:
    RoboTank(BattleField &obj, std::string n, int x, int y);
    RoboTank &operator=(const RoboTank &other);
    void randshootpro();
};

class UltimateRobot : public TerminatorRoboCop, public RoboTank
{
public:
    UltimateRobot(BattleField &obj, std::string n, int x, int y);
    UltimateRobot &operator=(const UltimateRobot &other);
};
#endif