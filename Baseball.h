#include "BatAndBallGames.h"

class Baseball: BatAndBallGames {
public:
    Baseball();
    //~Baseball();
    void SimulateHalfInning();
    bool SimulateAtBat();
    virtual void Display();
    virtual void RulesSummary();
    virtual void HallOfFame();
    virtual void SimulateGame();
    
    
private:
    int numberOfOuts;
    int numberOfRunnersLeftOnBase;
    int currentInning;
};

