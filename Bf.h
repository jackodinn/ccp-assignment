#ifndef BF_H
#define BF_H

#include "R.h"
#include <string>

class BattleField
{
private:
    Robot ***obj;
    int length;
    int height;

public:
    BattleField(int x, int y);
    ~BattleField();

    bool range(int x, int y) const;
    std::string invalid() const;
    std::string norobot() const;
    void set(Robot *robot, int x, int y);
    void autoset(int x, int y);
    void remove(int x, int y);
    void terminate(int x, int y);
    void display() const;

    Robot *getobj(int x, int y) const;
    int getlength() const;
    int getheight() const;
};

#endif