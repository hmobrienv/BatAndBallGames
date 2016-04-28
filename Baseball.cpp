#include "Baseball.h"

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

