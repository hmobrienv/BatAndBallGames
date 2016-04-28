/* Hugh O'Brien
 * CS520
 * Assignment #1
 */

#ifndef BATANDBALLGAMES_H
#define BATANDBALLGAMES_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;

#define TEAM_ONE 1
#define TEAM_TWO 2

// A Simple Simulation of Cricket using an Abstract
// Bat and Ball games base class in C++
// C++ implementation contains minor improvements over Java

class BatAndBallGames {
public:
    int playersPerTeam;
    int lengthOfGame;
    int teamOneScore; // Away team
    int teamTwoScore; // Home team
    string teamOnOffense;
    bool gameOver;
    
    virtual void Display();
    virtual void RulesSummary() = 0;
    virtual void HallOfFame() = 0;
    virtual void SimulateGame() = 0;
};


#endif /* BATANDBALLGAMES_H */
