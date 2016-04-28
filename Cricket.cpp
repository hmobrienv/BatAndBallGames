#include "Cricket.h"

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

