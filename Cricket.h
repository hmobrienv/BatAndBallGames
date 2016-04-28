#include "BatAndBallGames.h"

class Cricket: BatAndBallGames {
public:
    Cricket();
    int SimulateOver();
    bool SimulateInnings();
    virtual void Display();
    virtual void RulesSummary();
    virtual void HallOfFame();
    virtual void SimulateGame();
    
    
private:
    int numberOfOvers;
    int numberOfBattersRemaining;
    int wentFirst;
    int currentInnings;
};

