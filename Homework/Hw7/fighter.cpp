#include "fighter.h"

// CONSTRUCTORS
Fighter::Fighter(const std::string &fightername, int injab, int forwardtilt, int uptilt, int downtilt, int forwardsmash, int upsmash, int downsmash) {
    fighter_name = fightername;
    jab = injab;
    forward_tilt = forwardtilt;
    up_tilt = uptilt;
    down_tilt = downtilt;
    forward_smash = forwardsmash;
    up_smash = upsmash;
    down_smash = downsmash;
    std::map <std::string, int> temp;
    allMoves = temp;
}

// ACCESSORS
std::string Fighter::getName() const {
    return fighter_name;
}
std::map <std::string, int> Fighter::getAll() const {
    return allMoves;
}
int Fighter::getCurrent() const {
    return current;
}
std::string Fighter::getQuery() const {
    return query;
}

// MODIFIERS

// THIS METHOD ADDS ALL THE MOVES TO A MAP
void Fighter::addMoves() {
    allMoves.insert(std::pair <const std::string, int> ("jab", jab));
    allMoves.insert(std::pair <const std::string, int> ("forward-tilt", forward_tilt));
    allMoves.insert(std::pair <const std::string, int> ("up-tilt", up_tilt));
    allMoves.insert(std::pair <const std::string, int> ("down-tilt", down_tilt));
    allMoves.insert(std::pair <const std::string, int> ("forward-smash", forward_smash));
    allMoves.insert(std::pair <const std::string, int> ("up-smash", up_smash));
    allMoves.insert(std::pair <const std::string, int> ("down-smash", down_smash));
}

// THIS METHOD SETS THE REQUESTED MOVE'S FRAME SPEED
void Fighter::setCurrent(std::string move) {
    current = allMoves.find(move)->second;
}

void Fighter::setQuery(std::string in_query) {
    query = in_query;
}

bool operator< (const Fighter& left, const Fighter& right) {
    // IF -S IS REQUESTED SORT IT BY GREATEST TO LEAST
    if (left.getQuery() == "-s" && right.getQuery() == "-s") {
        if (left.getCurrent() > right.getCurrent()) {
        return true;
        }
        // SORTING BY NAME ALPHABETICALLY IF THE FRAMES ARE EQUAL
        else if (left.getCurrent() == right.getCurrent()) {
            return left.getName() < right.getName();
        }
        else {
            return false;
        }
    }
    // ELSE SORTED BY LEAST TO GREATEST
    else {
        if (left.getCurrent() < right.getCurrent()) {
            return true;
        }
        // SORTING BY NAME ALPHABETICALLY IF THE FRAMES ARE EQUAL
        else if (left.getCurrent() == right.getCurrent()) {
            return left.getName() < right.getName();
        }
        else {
            return false;
        }
    }
}
