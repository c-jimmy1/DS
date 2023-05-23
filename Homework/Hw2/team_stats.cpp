#include "team_stats.h"
#include <iostream>
#include <string>
#include <vector>

team_Stats::team_Stats() { //constructor
    names = "";
    wins = 0;
    losses = 0;
    ties = 0;
    goals = 0;
    penalties = 0;
    percentage = 0;
    alldates.clear();

}
team_Stats::team_Stats(const std::string& teams) {
    names = teams;
    wins = 0;
    losses = 0;
    ties = 0;
    goals = 0;
    penalties = 0;
    percentage = 0;
    alldates.clear();
}

// ACCESSORS
std::string team_Stats::getteam() const {
    return names;
}
int team_Stats::getwins() const {
    return wins;
}
int team_Stats::getlosses() const {
    return losses;
}
int team_Stats::getties() const {
    return ties;
}
int team_Stats::getgoals() const {
    return goals;
}
int team_Stats::getpenalties() const {
    return penalties;
}
float team_Stats::getpercentage() const {
    return percentage;
}
std::vector <std::string> team_Stats::getdates() const {
    return alldates;
}

// MODIFIERS
void team_Stats::addwins() {
    wins += 1;
}
void team_Stats::addlosses() {
    losses += 1;
}
void team_Stats::addties() {
    ties += 1;
}
void team_Stats::addgoals(int player_goals) {
    goals += player_goals; 
}
void team_Stats::addpenalties(int player_penalties) {
    penalties += player_penalties;
}
void team_Stats::calcwinpercentage() {
    percentage = (wins + (0.5*ties)) / (wins + losses + ties);
}
void team_Stats::makedates(std::string date) {
    alldates.push_back(date);
}


// IDEA TAKEN FROM TIME.CPP LAB ISEARLIERTHAN METHOD , COMPARISON METHOD
bool isgreaterthan(const team_Stats& t1, const team_Stats& t2) {
    if (t1.getpercentage() > t2.getpercentage()) {
        return true;
    }
    else if (t1.getpercentage() < t2.getpercentage()) {
        return false;
    }
    else {
        if (t1.getgoals() > t2.getgoals()) {
            return true;
        }
        else if (t1.getgoals() < t2.getgoals()) {
            return false;
        }
        else {
            if (t1.getteam() > t2.getteam()) {
                return true;
            }
            return false;
        }
    }
}