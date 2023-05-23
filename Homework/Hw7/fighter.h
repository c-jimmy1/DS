#ifndef __fighter_h__
#define __fighter_h__
#include <iostream>
#include <map>
#include <set>
class Fighter {
    public:
        // CONSTRUCTORS
        Fighter(const std::string &fightername, int injab, int forwardtilt, int uptilt, int downtilt, int forwardsmash, int upsmash, int downsmash);

        // ACCESSORS
        std::string getName() const;
        std::map <std::string, int> getAll() const;
        int getCurrent() const;
        std::string getQuery() const;


        // MODIFIERS
        void addMoves();
        void setCurrent(std::string move);
        void setQuery(std::string in_query);
    private: // REPRESENTATION
        std::string fighter_name, query;
        std::map <std::string, int> allMoves;
        int jab, forward_tilt, up_tilt, down_tilt, forward_smash, up_smash, down_smash, current;

};
bool operator< (const Fighter& left, const Fighter& right);
#endif