#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include "team_stats.h"
#include "player_stats.h"

// PARSING FOR TEAMS AND PLAYERS
// PARAMETERS: Passing in allstats (strings), allteams (strings), allplayers (strings), teamObjects (objects), playerObjects (objects)
void parsing(const std::vector <std::string>& allstats, std::vector <std::string>& allteams, std::vector <std::string>& allplayers, std::vector <team_Stats>& teamObjects, std::vector <player_Stats>& playerObjects) {
    for (int i  = 0; i < (int)allstats.size(); i++) {

        // GETTING ALL TEAM NAMES
        if (allstats[i] == "FINAL") {
            // THIS FILTERS OUT THE DUPLICATES
            if (std::find(allteams.begin(), allteams.end(), allstats[i+1]) == allteams.end()) { 
                allteams.push_back(allstats[i+1]); // adds team 1
                
            }
            if (std::find(allteams.begin(), allteams.end(), allstats[i+3]) == allteams.end()) { 
                    allteams.push_back(allstats[i+3]); // ADDS TEAM 2
                }
        }

        // GETTING ALL PLAYER NAMES
        if (allstats[i] == "penalty" || allstats[i] == "goal") {
            // FILTER IN PLAYERS BECAUSE ONLY PLAYERS HAVE "_" (underscores), the purpose is to filter out "BENCH"
            if (allstats[i+1].find("_") != std::string::npos) { 
                if (std::find(allplayers.begin(), allplayers.end(), allstats[i+1]) == allplayers.end()) {
                   allplayers.push_back(allstats[i+1]);
                }
            }   
        }

        // PARSING ASSISTS TO GET ALL PLAYER NAMES
        if (allstats[i] == "(") {
            int temp_index = i + 1;
            while (allstats[temp_index] != ")") {
                if (std::find(allplayers.begin(), allplayers.end(), allstats[temp_index]) == allplayers.end()) {
                    allplayers.push_back(allstats[temp_index]);
                }
                temp_index++;
                i = temp_index;
            }
        }
    }

    // CREATING A VECTOR OF TEAM OBJECTS
    for (int x = 0; x < (int)allteams.size(); x++) {
        team_Stats team1(allteams[x]);
        teamObjects.push_back(team1);
    }
    
    // CREATING A VECTOR OF PLAYER OBJECTS
    for (int x = 0; x < (int)allplayers.size(); x++) {
        player_Stats player1(allplayers[x]);
        playerObjects.push_back(player1);
    }

    // PARSING THROUGH FOR PLAYER STATS
    for (int i = 0; i < (int)allstats.size(); i++) {
        for (int j = 0; j < (int)playerObjects.size(); j++) {
            if (allstats[i] == "goal" && playerObjects[j].getplayer() == allstats[i+1]) {
                playerObjects[j].addgoals();
                playerObjects[j].setteam(allstats[i-1]); // i-1 is the index of the team name
            }
            if (allstats[i] == "penalty" && playerObjects[j].getplayer() == allstats[i+1]) {
                playerObjects[j].addpenalties();
                playerObjects[j].setteam(allstats[i-1]);
            }
            
            // ADDING ASSISTS TO EACH PLAYER
            if (allstats[i] == "(") {
                int temp_index = i + 1;
                while (allstats[temp_index] != ")") {
                    if (allstats[temp_index] == playerObjects[j].getplayer()) { // Makes sure the player is the same
                        playerObjects[j].addassists();
                        playerObjects[j].setteam(allstats[i-3]);
                    }
                    temp_index++;
                }
            }
        }
    }
    return;
}

// PARAMETERS: Passing in allstats (strings), allteams (strings), allplayers (strings), teamObjects (objects), playerObjects (objects)
void add_stats(const std::vector <std::string>& allstats, std::vector <std::string>& allteams, std::vector <std::string>& allplayers, std::vector <team_Stats>& teamObjects, std::vector <player_Stats>& playerObjects) {
    // PARSING THROUGH FOR TEAM STATS
    for (int i = 0; i < (int)allstats.size(); i++) {
        if (allstats[i] == "FINAL") {
            for (int j = 0; j < (int)teamObjects.size(); j++) {
                // i+1 is the first team's name, i+2 is that team's score
                // i+3 is the second team's name, i+3 is that team's score
                if (allstats[i+1] == teamObjects[j].getteam() && allstats[i+2] > allstats[i+4]) {
                    teamObjects[j].addwins();
                }
                if (allstats[i+3] == teamObjects[j].getteam() && allstats[i+2] > allstats[i+4]) {
                    teamObjects[j].addlosses();
                }
                if (allstats[i+3] == teamObjects[j].getteam() && allstats[i+2] < allstats[i+4]) {
                    teamObjects[j].addwins();
                }
                if (allstats[i+1] == teamObjects[j].getteam() && allstats[i+2] < allstats[i+4]) {
                    teamObjects[j].addlosses();
                }
                if (allstats[i+1] == teamObjects[j].getteam() && allstats[i+2] == allstats[i+4]) {
                    teamObjects[j].addties();
                }
                if (allstats[i+3] == teamObjects[j].getteam() && allstats[i+2] == allstats[i+4]) {
                    teamObjects[j].addties();
                }
                teamObjects[j].calcwinpercentage(); // Calls the method that calculates win percentage
            }
        }
    }

    // ADDING UP ALL GOALS AND PENALTIES FROM PLAYER STATS FOR TEAM STATS
    for (int i = 0; i < (int)teamObjects.size(); i++) {
        for (int j = 0; j < (int)playerObjects.size(); j++) {
            if (teamObjects[i].getteam() == playerObjects[j].getteam()) {
                teamObjects[i].addgoals(playerObjects[j].getgoals());
                teamObjects[i].addpenalties(playerObjects[j].getpenalties());
            }
        }
    }
    
    // ADDING PENALTIES FOR BENCH TO TEAM STATS
    for (int i = 0; i < (int)allstats.size(); i++) {
        for (int j = 0; j < (int)teamObjects.size(); j++) {
            if (allstats[i] == "BENCH" && teamObjects[j].getteam() == allstats[i-2]) {
                teamObjects[j].addpenalties(1);
            }
        }
    }
    return;
}

// CREATING CUSTOM STATS
void custom_stats(const std::vector <std::string>& allstats, std::vector <team_Stats>& teamObjects) {
    for (int i = 0; i < (int)allstats.size(); i++) {
        for (int j = 0; j < (int)teamObjects.size(); j++) {
            if (allstats[i] == "PERIOD" && allstats[i+1] == "1") {
                if (teamObjects[j].getteam() == allstats[i-3]){ // i-3 is the first team
                    // i-6 is the month, i-5 is the day, i-4 is the year
                    teamObjects[j].makedates(allstats[i-6] + " " + allstats[i-5] + " " + allstats[i-4] + "\n");
                }
                if (teamObjects[j].getteam() == allstats[i-1]){ // i-1 is the second team
                    // i-6 is the month, i-5 is the day, i-4 is the year
                    teamObjects[j].makedates(allstats[i-6] + " " + allstats[i-5] + " " + allstats[i-4] + "\n");
                }
            }
        }
    }
}

int main(int argc, char*argv[]) {
    std::ifstream statsfile(argv[1]);
    std::ofstream outfile(argv[2]);

    // CHECKS FOR INPUT FILE ERROR
    if (!statsfile.good()) { 
        std::cerr << "bad input file" << std::endl;
	}
    // CHECK FOR OUTPUT FILE ERROR
    if (!outfile.good()) { 
        std::cerr << "bad output file" << std::endl;
    }
    // CHECK FOR CORRECT NUMBER OF ARGUMENTS
    if (argc != 4) { 
        std::cerr << "incorrect number of arguments" << std::endl;
    }

    // PARSING ALL STRINGS FROM THE FILE TO A VECTOR
    std::string n = "";
    std::vector <std::string> allstats;
	while (statsfile >> n) { 
		allstats.push_back(n);
	}

    std::vector <std::string> allteams;
    std::vector <std::string> allplayers;

    std::vector <team_Stats> teamObjects;
    std::vector <player_Stats> playerObjects;

    // CALLING FUNCTION TO PARSE FILE AND CREATE OBJECTS
    parsing(allstats, allteams, allplayers, teamObjects, playerObjects);
    add_stats(allstats, allteams, allplayers, teamObjects, playerObjects);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
    custom_stats(allstats, teamObjects);

    std::sort(teamObjects.begin(), teamObjects.end(), isgreaterthan);
    std::sort(playerObjects.begin(), playerObjects.end(), isgreaterthan2);

        
    // WRITING TO A FILE    
    if ((std::string)argv[3] == "--team_stats") {
        // OUTPUTTING FIRST ROW
        outfile << std::setw(16) << std::left << "Team Name" << std::setw(4) << "W" << std::setw(4)<< "L" << std::setw(4) << "T"; 
        outfile << std::setw(7) << "Win%" << std::setw(7) << "Goals" << std::setw(11) << "Penalties" << std::endl; 
        for (int i = 0; i < (int)teamObjects.size(); i++) {
            // OUTPUTTING THE TEAM STATS
            outfile << std::setw(13) << std::left << teamObjects[i].getteam() << std::setw(4) << std::right << teamObjects[i].getwins();
            outfile << std::setw(4) << std::right << teamObjects[i].getlosses() << std::setw(4) << std::right << teamObjects[i].getties();
            outfile << std::setw(7) << std::right << std::fixed << std::setprecision(2) << teamObjects[i].getpercentage() << std::setw(8);
            outfile << std::right << teamObjects[i].getgoals() << std::setw(11) << std::right << teamObjects[i].getpenalties() << std::endl;
        }
    } 

    else if ((std::string)argv[3] == "--player_stats") {
        // OUTPUTTING FIRST ROW
        outfile << std::setw(23) << std::left << "Player Name" << std::setw(15) << "Team" << std::setw(7) << "Goals" << std::setw(9);
        outfile << "Assists" << std::setw(11) << "Penalties" << std::endl;
        for (int i = 0; i < (int)playerObjects.size(); i++) {
            // OUTPUTTING PLAYER STATS
            outfile << std::setw(23) << std::left << playerObjects[i].getplayer() << std::setw(14) << std::left << playerObjects[i].getteam();
            outfile << std::setw(6) << std::right << playerObjects[i].getgoals() << std::setw(9) << std::right << playerObjects[i].getassists(); 
            outfile << std::setw(11) << std::right << playerObjects[i].getpenalties() << std::endl;
        }
    }

    else if ((std::string)argv[3] == "--custom_stats") {
        // OUTPUTTING FIRST ROW
        outfile << std::setw(23) << std::left << "Team Name" << std::setw(15) << "Dates" << std::endl;
        for (int i = 0; i < (int)teamObjects.size(); i++) {
            // OUTPUTTING CUSTOM STATS
            outfile << teamObjects[i].getteam();
            std::vector<std::string> temp = teamObjects[i].getdates();
            for (int x = 0; x < (int)temp.size(); x++) {
                if (x == 0) {
                    int space_length = 23 - teamObjects[i].getteam().size();
                    outfile << std::string(space_length, 32) << temp[x];
                } 
                else {
                    outfile << std::string(23, 32) << temp[x]; // 23 spaces, 32 is the ascii table for " "
                }
            }
            outfile << std::string(45, 45) << std::endl; // 45 dashes, 45 is the ascii table for "-"
        }
    }
    else {
        std::cerr << "Incorrect stats, use either --team_stats, --player_stats, or --custom_stats" << std::endl;
    }
    statsfile.close();
    outfile.close();
}
