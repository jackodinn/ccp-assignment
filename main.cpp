#include <iostream>
#include <string>
# include <cstdlib>
#include <ctime>
using namespace std;

class Robot
{
    protected:
        int robotPositionX, robotPositionY; // know the location
        int lives; // robot have how many lives
        string name;
        string type; // robot type(strategy)

    public:
        Robot(string name, int x, int y) : name(name), robotPositionX(x), robotPositionY(y), lives(3) {}

        virtual ~Robot() {}

        int getX() const // show position x
        {
            return robotPositionX;
        }
        int getY() const // show position y
        {
            return robotPositionY;
        }
        string getName() const // show name
        {
            return name;
        }
        string getType() const // show type
        {
            return type;
        }
        bool isAlive() const
        {
            return lives > 0;
        }
        int getLives() const // show lives
        {
            return lives;
        }
        int hit() // deduct lives
        {
            if (lives > 0)
            {
                lives--;
            }
        }
};

class MovingRobot : public virtual Robot
{
    public:
        MovingRobot(string name, int x, int y) : Robot(name, x, y)
        {

        }
        void move() // change robot location
        {
            string moveCommand;
            if (moveCommand == "up")
            {
                robotPositionY += 1;
            }
            else if (moveCommand == "up right")
            {
                robotPositionX += 1;
                robotPositionY += 1;
            }
            else if (moveCommand == "right")
            {
                robotPositionX += 1;
            }
            else if (moveCommand == "down right")
            {
                robotPositionX += 1;
                robotPositionY -= 1;
            }
            else if (moveCommand == "down")
            {
                robotPositionY -= 1;
            }
            else if (moveCommand == "down left")
            {
                robotPositionX -= 1;
                robotPositionY -= 1;
            }
            else if (moveCommand == "left")
            {
                robotPositionX -= 1;
            }
            else if (moveCommand == "up left")
            {
                robotPositionX -= 1;
                robotPositionY - 1;
            }
        }
};

class ShootingRobot : public virtual Robot
{
    public:
        ShootingRobot(string name, int x, int y) : Robot(name, x, y)
        {

        }
        virtual void fire() = 0;
};

class SeeingRobot : public virtual Robot
{
    public:
        SeeingRobot(string name, int x, int y) : Robot(name, x, y)
        {

        }
        virtual void look() = 0;
};

class SteppingRobot : public virtual Robot
{
    public:
        SteppingRobot(string name, int x, int y) : Robot(name, x, y)
        {

        }
        void stepping()
        {

        }
};

// define robot type

class RoboCop : public MovingRobot, public ShootingRobot
{
    public:
        RoboCop(string name, int x, int y) : Robot(name, x, y), MovingRobot(name, x, y), ShootingRobot(name, x, y)
        {
            type = "RoboCop";
        }
        void move();
        void fire() override
        {
            int battlefieldWidth = 40; // determine battlefield width
            int battlefieldHeight = 50; // determine battlefield height
            int shotFired = 0; // robot fired time

            while (shotFired < 3)
            {
                int targetX = rand() % battlefieldWidth;
                int targetY = rand() % battlefieldHeight;

                if ((targetX != robotPositionX && targetY != robotPositionY) && (targetX + targetY <=10))
                {
                    cout << "RobotCop" << name << "fired at (" << targetX << ", " << targetY << ")" << endl;
                    shotFired++; 
                }
            }
        }
};

class Terminator : public MovingRobot, public SeeingRobot, public SteppingRobot
{
    public:
        Terminator(string name, int x, int y) : Robot(name, x, y), MovingRobot(name, x, y), SeeingRobot(name, x, y), SteppingRobot(name, x, y)
        {
            type = "Terminator";
        }
        void move();
        void look() override
        {

        }
        void stepping();
};

class TerminatorRoboCop : public MovingRobot, public SeeingRobot, public ShootingRobot, public SteppingRobot
{
    public:
        TerminatorRoboCop(string name, int x, int y) : Robot(name, x, y), MovingRobot(name, x, y), SeeingRobot(name, x, y), ShootingRobot(name, x, y), SteppingRobot(name, x, y)
        {
            type = "TerminatorRoboCop";
        }
        void move();
        void look() override
        {

        }
        void fire() override
        {
            int battlefieldWidth = 40; // determine battlefield width
            int battlefieldHeight = 50; // determine battlefield height
            int shotFired = 0; // robot fired time

            while (shotFired < 3)
            {
                int targetX = rand() % battlefieldWidth;
                int targetY = rand() % battlefieldHeight;

                if ((targetX != robotPositionX && targetY != robotPositionY) && (targetX + targetY <=10))
                {
                    cout << "RobotCop" << name << "fired at (" << targetX << ", " << targetY << ")" << endl;
                    shotFired++; 
                }
            }
        }
        void stepping();
};

class BlueThunder : public ShootingRobot
{
    int fireSequenceIndex;

    public:
        BlueThunder(string name, int x, int y) : Robot(name, x, y), ShootingRobot(name, x, y)
        {
            type = "BlueThunder";
        }
        void fire() override
        {
            static const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
            static const int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

            int targetX = robotPositionX + dx[fireSequenceIndex];
            int targetY = robotPositionY + dy[fireSequenceIndex];

            if (targetX >= 0 && targetX < 40 && targetY >=0 && targetY < 50)
            {
                cout << "BlueThunder " << name << " fires at (" << targetX << ", " << targetY << ")" << endl;
            }

            fireSequenceIndex = (fireSequenceIndex + 1) & 8;
        }
};

class Madbot : public ShootingRobot, public SeeingRobot
{
    int fireSequenceIndex;
    
    public:
        Madbot(string name, int x, int y) : Robot(name, x, y), ShootingRobot(name, x, y), SeeingRobot(name, x, y)
        {
            type = "Madbot";
        }
        void look() override
        {

        }
        void fire() override
        {
            static const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
            static const int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

            int targetX = robotPositionX + dx[fireSequenceIndex];
            int targetY = robotPositionY + dy[fireSequenceIndex];

            if (targetX >= 0 && targetX < 40 && targetY >=0 && targetY < 50)
            {
                cout << "BlueThunder " << name << " fires at (" << targetX << ", " << targetY << ")" << endl;
            }

            fireSequenceIndex = (fireSequenceIndex + 1) & 8;
        }
};

class RoboTank : public ShootingRobot, public SeeingRobot
{
    public:
        RoboTank(string name, int x, int y) : Robot(name, x, y), ShootingRobot(name, x, y), SeeingRobot(name, x, y)
        {
            type = "RoboTank";
        }
        void look() override
        {

        }
        void fire() override
        {

        }
};

class UltimateRobot : public MovingRobot, public SteppingRobot, public SeeingRobot, public ShootingRobot
{
    public:
        UltimateRobot(string name, int x, int y) : Robot(name, x, y), MovingRobot(name, x, y), SteppingRobot(name, x, y), SeeingRobot(name, x, y), ShootingRobot(name, x, y)
        {
            type = "UltimateRobot";
        }
        void move();
        void stepping();
        void look() override
        {

        }
        void fire() override
        {
            int battlefieldWidth = 40; // determine battlefield width
            int battlefieldHeight = 50; // determine battlefield height
            int shotFired = 0; // robot fired time

            while (shotFired < 3)
            {
                int targetX = rand() % battlefieldWidth;
                int targetY = rand() % battlefieldHeight;

                if (targetX != robotPositionX && targetY != robotPositionY)
                {
                    cout << "RobotCop" << name << "fired at (" << targetX << ", " << targetY << ")" << endl;
                    shotFired++; 
                }
            }
        }
};

// battelefield
class Battlefield
{
    int num_robots;
    char** grid;
    int width, height;
    Robot* robots[num_robots];
    int robotCount;

    public:
        Battlefield(int w, int h) : width(w), height(h), robotCount(0)
        {
            grid - new char*[height];
            for (int i = 0; i < height; ++i)
            {
                grid[i] = new char[width];
                for (int j = 0; j < width; ++j)
                {
                    grid[i][j] = '.';
                }
            }
        }

        ~Battlefield()
        {
            for (int i = 0; i < height; ++i)
            {
                delete[] grid[i];
            }
            delete[] grid;
        }

        void addRobot(Robot* robot)
        {
            if (robotCount < num_robots)
            {
                robot[robotCount++] = robot;
            }
        }

        void display()
        {
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    cout << endl;
                }
            }
        }

        void simulate(int steps)
        {
            for (int step = 0; step < steps; ++step)
            {
                for (int i = 0; i < robotCount; ++i)
                {
                    Robot* robot = robots[i];
                    if (robot->isAlive())
                    {
                        robot->look();
                        robot->move();
                        robot->fire();
                    }
                }
            }
        }
};
