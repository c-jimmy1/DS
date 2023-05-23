#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include "fighter.h"
//You may add additional typedefs, includes, etc. up here

//This is the only array you are allowed to have in your program.
const std::set <std::string> move_names = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

//Feel free to put forward declarations here

// PARSING THE DECLARATION FILE AND PUTTING MOVES INTO CLASS OBJECTS, AND CREATING MAPS OF FIGHTER NAMES AND IT'S OBJECTS.
void parsingDeclaration(std::ifstream &dbfile, std::map <std::string, Fighter> &all_fighters) {
	std::string fighter_name, character_title, move1, move2, move3, move4, move5, move6, move7;
	int jab, forwardtilt, uptilt, downtilt, forwardsmash, upsmash, downsmash;

	// READING THE TITLE LINE INTO TEMP VARIABLES
	dbfile >> character_title >> move1 >> move2 >> move3 >> move4 >> move5 >> move6 >> move7; 

	// PARSING THE FIGHTER INFORMATION
	while (dbfile >> fighter_name >> jab >> forwardtilt >> uptilt >> downtilt >> forwardsmash >> upsmash >> downsmash) {
		// CONSTRUCTS EACH FIGHTER WHILE READING THE FILE AND INSERTS INTO A MAP
		Fighter character(fighter_name, jab, forwardtilt, uptilt, downtilt, forwardsmash, upsmash, downsmash);
		character.addMoves();
		all_fighters.insert(std::pair <const std::string, Fighter> (fighter_name, character));
	}
}

// HELPER FUNCTION FOR HANDLING -Q REQUESTS. THIS FUNCTION IS CALLED IN PARSINGQUERY FUNCTION
void qQuery(std::ofstream &outfile, const std::set <std::string> &move_names, std::string character, 
			std::string request, std::map <std::string, Fighter> &all_fighters) {

	std::map<std::string, int> allMoves = all_fighters.find(character)->second.getAll();

	// CHECK IF THE CHARACTER IS VALID
	if (character == all_fighters.find(character)->first) {
		if (request == "all") {
			// IF THE USER REQUESTS ALL, ITERATE THROUGH ALL THE MOVES AND WRITE IT TO THE FILE
			std::map<std::string, int>::iterator allitr;
			for (allitr = allMoves.begin(); allitr != allMoves.end(); allitr++) {
				outfile << character << " " << allitr->first << ": " << allitr->second << std::endl;
				
			}
			outfile << "\n";
		}
		// IF THE REQUEST IS A SPECIFIC MOVE I USE .FIND TO GET THE MOVE AND FRAME SPEED
		else if (request == *move_names.find(request)) { // dereferencing the iterator pointing to the request
			if (request == allMoves.find(request)->first) {
				outfile << character << " " << allMoves.find(request)->first << ": " << allMoves.find(request)->second << std::endl;
				outfile << "\n";
			}
		}
		// IF THE REQUESTED MOVE ISN'T PART OF THE MOVE LIST/IT'S INVALID
		else {
			outfile << "Invalid move name: " << request << std::endl;
			outfile << "\n";
		}
	}
	else {
		outfile << "Invalid character name: " << character << std::endl;
		outfile << "\n";
	}
}

// HELPER FUNCTION FOR HANDLING -F REQUESTS. THIS FUNCTION IS CALLED IN PARSINGQUERY FUNCTION.
void fQuery(std::ofstream &outfile, const std::set <std::string> &move_names, std::string move, 
			int limit, std::map <std::string, Fighter> &all_fighters) {
	std::set <Fighter> all_fastest;
	std::map <std::string, Fighter>::iterator fighter_itr;
	// CHECK IF THE MOVE IS A VALID MOVE, IF IT'S NOT PRINT INVALID MOVE
	if (move == *move_names.find(move)) {
		outfile << "-f " << move << " " << limit << std::endl;

		// ITERATING THROUGH ALL FIGHTERS TO SET THE REQUESTED MOVE'S SPEED AND ADD IT TO A SET SO IT CAN SORT ITSELF
		for (fighter_itr = all_fighters.begin(); fighter_itr != all_fighters.end(); fighter_itr++) {
			fighter_itr->second.setCurrent(move);
			all_fastest.insert(fighter_itr->second);
		}
		
		// WRITING CHARACTERS WITH THE FASTEST FRAMES TO THE FILE BY LOOPING THROUGH THE SET
		std::set <Fighter>::iterator fastest_itr;
		int counter = 0;
		for (fastest_itr = all_fastest.begin(); fastest_itr != all_fastest.end(); fastest_itr++) {
			// STOP WRITING IF THE LIMIT OF FIGHTERS ARE MET
			if (counter == limit) {
				break;
			}
			outfile << fastest_itr->getName() << " " << fastest_itr->getCurrent() << std::endl;
			counter++;
		}
		outfile << "\n";
	}
	else {
		outfile << "Invalid move name: " << move << std::endl;
		outfile << "\n";
	}
}

// HELPER FUNCTION FOR HANDLING -S REQUESTS. THIS FUNCTION IS CALLED IN PARSINGQUERY FUNCTION.
void sQuery(std::ofstream &outfile, const std::set <std::string> &move_names, std::string move, 
			int limit, std::map <std::string, Fighter> &all_fighters) {
	std::set <Fighter> all_slowest;
	std::map <std::string, Fighter>::iterator fighter_itr;

	// CHECK IF THE MOVE IS A VALID MOVE, IF IT'S NOT PRINT INVALID MOVE
	if (move == *move_names.find(move)) {
		outfile << "-s " << move << " " << limit << std::endl;

		// ITERATING THROUGH ALL FIGHTERS TO SET THE REQUESTED MOVE'S SPEED AND ADD IT TO A SET SO IT CAN SORT ITSELF
		for (fighter_itr = all_fighters.begin(); fighter_itr != all_fighters.end(); fighter_itr++) {
			fighter_itr->second.setCurrent(move);
			// SETTING THE QUERY TO -S SO THE OPERATOR OVERLOADER WILL SORT IT FROM GREATEST TO LEAST
			fighter_itr->second.setQuery("-s");
			all_slowest.insert(fighter_itr->second);
		}
		
		// WRITING CHARACTERS WITH THE FASTEST FRAMES TO THE FILE BY LOOPING THROUGH THE SET
		std::set <Fighter>::iterator slowest_itr;
		int counter = 0;
		for (slowest_itr = all_slowest.begin(); slowest_itr != all_slowest.end(); slowest_itr++) {
			// STOP WRITING IF THE LIMIT OF FIGHTERS ARE MET
			if (counter == limit) {
				break;
			}
			outfile << slowest_itr->getName() << " " << slowest_itr->getCurrent() << std::endl;
			counter++;
		}
		outfile << "\n";
	}
	else {
		outfile << "Invalid move name: " << move << std::endl;
		outfile << "\n";
	}
}

// HELPER FUNCTION FOR HANDLING -D REQUESTS. THIS FUNCTION IS CALLED IN PARSINGQUERY FUNCTION.
void dQuery(std::ofstream &outfile, const std::set <std::string> &move_names, std::string move, 
			int frame, std::map <std::string, Fighter> &all_fighters) {
	std::map <std::string, Fighter>::iterator fighter_itr;
	// CHECK IF THE MOVE IS A VALID MOVE, IF IT'S NOT PRINT INVALID MOVE
	if (move == *move_names.find(move)) {
		outfile << "-d " << move << " " << frame << std::endl;
		
		/* LOOPING THROUGH ALL THE FIGHTERS AND OUTPUTTING A CHARACTER ONLY 
		IF THE MOVE FOR THE FIGHTER MEETS THE FRAME REQUIREMENT */
		for (fighter_itr = all_fighters.begin(); fighter_itr != all_fighters.end(); fighter_itr++) {
			std::map <std::string, int> allMoves = fighter_itr->second.getAll();
			if (allMoves.find(move)->second == frame) {
				outfile << fighter_itr->first << std::endl;
			}
		}
		outfile << "\n";
	} 
	else {
		outfile << "Invalid move name: " << move << std::endl;
		outfile << "\n";
	}
}

// PARSING THROUGH THE QUERY REQUESTS AND CALLING THE CORRESPONDING FUNCTIONS
void parsingQuery(std::ifstream &infile, std::ofstream &outfile, const std::set <std::string> &move_names, 
				std::map <std::string, Fighter> &all_fighters) {
	
	std::string name;
	while (infile >> name) {
		// EACH IF ELSE STATEMENT READS THE COMMANDS AND THEN CALLS THE FUNCTION NEEDED TO COMPLETE THE REQUEST
		if (name == "-q") {
			std::string character;
			std::string request;
			infile >> character >> request;
			qQuery(outfile, move_names, character, request, all_fighters);
		}
		else if (name == "-f") {
			std::string move;
			int limit;
			infile >> move >> limit;
			fQuery(outfile, move_names, move, limit, all_fighters);
		}
		else if (name == "-s") {
			std::string move;
			int limit;
			infile >> move >> limit;
			sQuery(outfile, move_names, move, limit, all_fighters);

		}
		else if (name == "-d") {
			std::string move;
			int frame;
			infile >> move >> frame;
			dQuery(outfile, move_names, move, frame, all_fighters);
		}
	}
}

int main(int argc, char** argv){
	// Argument parsing
	if(argc != 4){
		std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
		return -1;
	}

	std::ifstream dbfile(argv[1]);
	if(!dbfile){
		std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
	}

	std::ifstream infile(argv[2]);
	if(!infile){
		std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
	}

	std::ofstream outfile(argv[3]);
	if(!outfile){
		std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
	}

	///////Fill in the rest of main below:
	std::map <std::string, Fighter> all_fighters;
	parsingDeclaration(dbfile, all_fighters);
	parsingQuery(infile, outfile, move_names, all_fighters);

	return 0;
}
