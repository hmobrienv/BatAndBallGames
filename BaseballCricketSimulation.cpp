/* Hugh O'Brien
 * CS520
 * Assignment #1
 * Compiles with CC
 */
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

void BatAndBallGames::Display() {
    cout << "Team One: " << teamOneScore << endl;
    cout << "Team Two: " << teamTwoScore << endl;
    
};

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

Baseball::Baseball()
{
    srand(time(NULL));
    playersPerTeam = 9;
    lengthOfGame = 9;
    teamOneScore = teamTwoScore = 0;
    numberOfOuts = numberOfRunnersLeftOnBase = 0;
    teamOnOffense = "Away";
    currentInning = 1;
    gameOver = false;
}

bool Baseball::SimulateAtBat() {
    if (currentInning >= lengthOfGame && teamTwoScore != teamOneScore)
    {
        if (teamOnOffense.compare("Home") == 0 && teamTwoScore > teamOneScore)
        {
            cout << "Team Two Wins" << endl;
            gameOver = true;
            teamOnOffense = "Game Over";
            return false;
        }
        if (teamOnOffense.compare("Away") == 0 && teamOneScore > teamTwoScore && currentInning > lengthOfGame) {
            cout << "Team One Wins" << endl;
            // win condition checked in following inning for away team
            // real inning is previous.
            currentInning--;
            gameOver = true;
            teamOnOffense = "Game Over";
            return false;
        }
    }
    
    int totalScored = 0;
    int randomNumber = rand() % 100 + 1;
    
    // Simulate At-Bat
    if (randomNumber < 75) {
        // cout << "Batter out" << endl;
        numberOfOuts++;
    }
    else if (randomNumber < 95) {
        // cout << "Base-Hit" << endl;
        if (numberOfRunnersLeftOnBase < 3)
            numberOfRunnersLeftOnBase++;
        if (numberOfRunnersLeftOnBase > 2) {
            totalScored++;
        }
    }
    else
    {
        // cout << "Home-Run" << endl;
        totalScored = numberOfRunnersLeftOnBase + 1;
        numberOfRunnersLeftOnBase = 0;
    }
    
    // Tallying runs scored.
    if ((teamOnOffense.compare("Away") == 0) && (totalScored != 0)) {
        teamOneScore += totalScored;
    } else if ((teamOnOffense.compare("Home") == 0) && (totalScored != 0)){
        teamTwoScore += totalScored;
        
        // Checking if home team has win conditions.
        if ((currentInning >= 9) && (teamTwoScore > teamOneScore)) {
            cout << "Walk-Off win" << endl;
            gameOver = true;
            return false;
        }
    }
    
    // If inning is over, end inning switch teams.
    if (numberOfOuts == 3) {
        numberOfOuts = 0;
        numberOfRunnersLeftOnBase = 0;
        if (teamOnOffense.compare("Away") == 0)
            teamOnOffense = "Home";
        else
        {
            teamOnOffense = "Away";
            currentInning++;
        }
        
        return false; // End Of Inning, used for simulating half innings.
    }
    return true;
}

void Baseball::SimulateHalfInning()
{
    if (!gameOver)
        while(SimulateAtBat());
    
}

void Baseball::Display()
{
    cout << endl;
    cout << "Inning: " << currentInning << endl;
    BatAndBallGames::Display();
    cout << "Team Batting: " << teamOnOffense << endl;
    cout << endl;
}

void Baseball::HallOfFame()
{
    cout << "Hall Of Fame" << endl;
    // Showing last 10 hall of fame players to be inducted
    string hallOfFamePlayers[] =
    {"2015 - P John Smoltz - Atlanta Braves",
        "2015 - P Pedro Martinez - Boston Red Sox",
        "2015 - P Randy Johnson - Arizona Diamondbacks",
        "2015 - 2B Craig Biggio - Houston Astro",
        "2014 - MGR Joe Torre - New York Yankees",
        "2014 - DH Frank Thomas - Chicago White Sox",
        "2014 - P Greg Maddux - Atlanta Braves",
        "2014 - MGR Tony La Russa - St. Louis Cardinals",
        "2014 - P Tom Glavine - Atlanta Braves",
        "2014 - MGR Bobby Cox - Atlanta Braves",
        "end"};
    
    for (int i = 0; hallOfFamePlayers[i] != "end"; i++) {
        cout << hallOfFamePlayers[i] << endl;
    }
    
    cout << endl;
}

void Baseball::RulesSummary() {
    string str;
    ifstream file;
    file.open ("BaseballRules.txt");
    if (file.is_open()) {
        while (getline(file, str)) {
            cout << str << endl;
        }
        
        cout << endl;
    } else {
        cout << "Error Opening File." << endl;
    }
    cout << endl;
    file.close();
}

void Baseball::SimulateGame()
{
    while(!gameOver)
        SimulateHalfInning();
}

/* Beginning of Cricket Implementation */
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

Cricket::Cricket() {
    srand(time(NULL));
    playersPerTeam = 11;
    teamOneScore = teamTwoScore = 0;
    lengthOfGame = 2;
    currentInnings = 0;
    numberOfOvers = 0;
    numberOfBattersRemaining = 11;
    gameOver = false;
    
    // Picking which team went first.
    int random = rand() % 100 + 1;
    if (random < 50) {
        wentFirst = TEAM_ONE;
        teamOnOffense = "One";
    }
    else {
        wentFirst = TEAM_TWO;
        teamOnOffense = "Two";
    }
}

int Cricket::SimulateOver() {
    
    // Error-checking if game is being played only through Overs
    if (currentInnings <= lengthOfGame) {
        if (numberOfBattersRemaining < 2 && numberOfOvers > 19) {
            if (teamOnOffense.compare("One")  == 0)
                teamOnOffense = "Two";
            else
                teamOnOffense = "One";
            
            currentInnings++;
        }
    }
    
    int totalScored = 0;
    int randomNum = rand() % 1000 + 1;
    int numberOfBallsPitched = 0;
    
    
    // Simulate balls pitched, break out if batter is called out
    while (numberOfBallsPitched < 6) {
        
        // Checking if win conditions were met.
        if (currentInnings == lengthOfGame) {
            if (((teamOneScore + totalScored) > teamTwoScore) && wentFirst == TEAM_TWO
                && teamOnOffense.compare("One") == 0) {
                // Team has gained win conditions
                gameOver = true;
                return totalScored;
            }
            if (((teamTwoScore + totalScored) > teamOneScore) && wentFirst == TEAM_ONE
                && teamOnOffense.compare("Two") == 0) {
                // Team has gained win conditions
                gameOver = true;
                return totalScored;
            }
        }
        
        if (randomNum < 300) {
            // Batter out 30%
            numberOfBattersRemaining--;
            return totalScored;
        } else if (randomNum < 500) {
            // 20% 1-run
            totalScored += 1;
        } else if (randomNum < 800) {
            // 30% 2-run
            totalScored += 2;
        } else if (randomNum < 900) {
            // 10% 3-run
            totalScored += 3;
        } else if (randomNum < 920) {
            // 2% 4-run
            totalScored += 4;
        } else if (randomNum < 950) {
            // 3% 5-run
            totalScored += 5;
        } else {
            // 5% 6-run
            totalScored += 6;
        }
        
        numberOfBallsPitched++;
    }
    return totalScored;
}

bool Cricket::SimulateInnings() {
    if(gameOver)
        return false;
    
    numberOfBattersRemaining = 11;
    numberOfOvers = 0;
    
    // Simulating at-bats for current innings
    while (numberOfBattersRemaining > 1 && numberOfOvers < 20 && currentInnings <= lengthOfGame) {
        if (teamOnOffense.compare("One") == 0)
            teamOneScore += SimulateOver();
        if (teamOnOffense.compare ("Two") == 0)
            teamTwoScore += SimulateOver();
        
        // Win-conditions were met for team batting last. gameOver flag set in SimulateOvers()
        if (gameOver)
            return false;
        
        numberOfOvers++;
    }
    
    if (teamOnOffense == "One") {
        teamOnOffense = "Two";
    } else {
        teamOnOffense = "One";
    }
    
    // Checking if the game is in the last inning
    if(currentInnings+1 > lengthOfGame) {
        gameOver = true;
        return false;
    }
    
    currentInnings++;
    return true;
}

void Cricket::Display() {
    cout << "Team Batting First: " << ((wentFirst == TEAM_ONE) ? "Team One" : "Team Two") << endl;
    cout << "Current Innings: " << currentInnings << endl;
    BatAndBallGames::Display();
    
    cout << endl;
}

void Cricket::RulesSummary() {
    string str;
    ifstream file;
    file.open ("CricketRules.txt");
    if (file.is_open()) {
        while (getline(file, str)) {
            cout << str << endl;
        }
        
        cout << endl;
    } else {
        cout << "Error Opening File." << endl;
    }
    cout << endl;
    file.close();
}

void Cricket::HallOfFame() {
    // Showing last 10 hall of fame players to be inducted
    string hallOfFamePlayers[] =
    {"2015 - Martin Crowe - New Zealand",
        "2015 - Wes Hall - West Indies",
        "2015 - Anil Kumble - India",
        "2015 - Betty Wilson - Australia",
        "2013 - Adam Gilchrist - Australia",
        "2013 - Debbie Hockley - New Zealand",
        "2013 - Bob Simpson - Australia",
        "2013 - Shane Warne - Australia",
        "2013 - Waqar Younis - Pakistan",
        "2012 - Enid Bakewell - England",
        "end"};
    
    for (int i = 0; hallOfFamePlayers[i] != "end"; i++) {
        cout << hallOfFamePlayers[i] << endl;
    }
    
    cout << endl;
}

void Cricket::SimulateGame() {
    while(!gameOver)
        SimulateInnings();
}


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
