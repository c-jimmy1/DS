#ifndef __player_stats_h__
#define __player_stats_h__
#include <string>

class player_Stats {
public:
    // CONSTRUCTORS
    player_Stats();
    player_Stats(std::string player);

    // ACCESSORS
    std::string getplayer() const;
    std::string getteam() const;
    int getgoals() const;
    int getassists() const;
    int getpenalties() const;
    
    // MODIFIERS
    void setteam(std::string team_name);
    void addgoals();
    void addassists();
    void addpenalties();

private: // REPRESENTATION
    std::string players;
    std::string team;
    int goals;
    int assists;
    int penalties;
};
bool isgreaterthan2(const player_Stats& p1, const player_Stats& p2);

#endif