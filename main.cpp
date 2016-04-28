#include "BatAndBallGames.h"
#include "Baseball.h"
#include "Cricket.h"

int main() {
    Baseball newGame;
    
    newGame.Display();
    newGame.RulesSummary();
    newGame.HallOfFame();
    newGame.SimulateGame(); // Calls SimulateHalfInning, which calls SimulateAtBat
    newGame.Display();
    
    
    Cricket match;
    match.Display();
    match.RulesSummary();
    match.HallOfFame();
    match.SimulateGame(); // Calls simulateInnings, calls SimulateOver
    match.Display();
    
    //Wont Compile
    //cout << "Trying to initialize with abstract class" << endl;
    //BatAndBallGames abstract;
    //abstract.SimulateGame();
    
    return 0;
}
