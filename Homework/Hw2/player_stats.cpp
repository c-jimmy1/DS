#include "player_stats.h"
#include <iostream>
#include <string>

player_Stats::player_Stats() { //constructor
    players = "";
    team = "";
    goals = 0;
    assists = 0;
    penalties = 0;
}

player_Stats::player_Stats(std::string player) { //constructor
    players = player;
    team = "";
    goals = 0;
    assists = 0;
    penalties = 0;
}

// ACCESSORS
std::string player_Stats::getplayer() const {
    return players;
}
std::string player_Stats::getteam() const {
    return team;
}
int player_Stats::getgoals() const {
    return goals;
}
int player_Stats::getassists() const {
    return assists;
}
int player_Stats::getpenalties() const {
    return penalties;
}

// MODIFIERS
void player_Stats::setteam(std::string team_name) {
    team = team_name;
}
void player_Stats::addgoals() {
    goals += 1;
}
void player_Stats::addassists() {
    assists += 1;
}
void player_Stats::addpenalties() {
    penalties +=1;
}

// IDEA TAKEN FROM TIME.CPP LAB ISEARLIERTHAN METHOD, COMPARISON METHOD
bool isgreaterthan2(const player_Stats& p1, const player_Stats& p2) {
    if (p1.getgoals() + p1.getassists() > p2.getgoals() + p2.getassists()){
        return true;
    }
    else if (p1.getgoals() + p1.getassists() < p2.getgoals() + p2.getassists()){
        return false;
    }
    else{
        if (p1.getpenalties() < p2.getpenalties()) {
            return true;
        }
        else if (p1.getpenalties() > p2.getpenalties()) {
            return false;
        }
        else {
            if (p1.getplayer() < p2.getplayer()) {
                return true;
            }
            return false;
        }
    }
}