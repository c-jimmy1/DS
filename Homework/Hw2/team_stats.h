#ifndef __team_stats_h__
#define __team_stats_h__
#include <string>
#include <vector>

class team_Stats {
public:
    // CONSTRUCTORS 
    team_Stats();
    team_Stats(const std::string& team);

    // ACCESSORS
    std::string getteam() const;
    int getwins() const;
    int getlosses() const;
    int getties() const;
    int getgoals() const;
    int getpenalties() const;
    float getpercentage() const;
    std::vector <std::string> getdates() const;
    
    // MODIFIERS
    void addwins();
    void addlosses();
    void addties();
    void addgoals(int player_goals);
    void addpenalties(int player_penalties);
    void calcwinpercentage();
    void makedates(std::string date);

private: //REPRESENTATION (member variables)
    std::string names;
    int wins;
    int losses;
    int ties;
    int goals;
    int penalties;
    float percentage;
    std::vector <std::string> alldates;
};
bool isgreaterthan(const team_Stats& t1, const team_Stats& t2);
#endif