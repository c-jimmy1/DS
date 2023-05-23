#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>
#include "board.h"

// This method parses the input file and gathers the board column count and row count. It also gets the positive words and negative words based on "+" or "-" signs
void parsing( std::ifstream& puzzlefile, std::vector<std::string>& positive_words, std::vector<std::string> negative_words, unsigned int& b_row, unsigned int& b_col) {
    std::vector <std::string> allwords;
    std::string word;
    while (puzzlefile >> word) {
        allwords.push_back(word);
    }

    // loop through all the words in the vector to check which words are which
    for (unsigned int i = 0; i < allwords.size(); i++) {
        if (i == 0) {
            b_col = std::stoi(allwords[i]);
        }
        else if (i == 1) {
            b_row = std::stoi(allwords[i]);
        }
        else if (allwords[i] == "+") {
            positive_words.push_back(allwords[i+1]);
        }
        else if (allwords[i] == "-") {
            negative_words.push_back(allwords[i+1]);
        }
    }
    
}

// Recursive search to search and place in each letter into the board one by one
void recurSearch(std::vector <std::string> positive_words, std::vector <std::string> negative_words,
                 std::vector <Board> &allboards, Board curr_board, unsigned int r_index, unsigned int c_index) {
    unsigned int cols = curr_board.getCol();

    // BASE CASE, IF THERE ARE NO MORE POSITIVE WORDS LEFT ADD THE CURRENT BOARD TO THE VECTOR OF SOLUTIONS
    if (positive_words.size() == 0) {
        allboards.push_back(curr_board);
        return;
    }
    // Horizontal
    // CHECK THAT THE SIZE WILL FIT HORIZONTALLY
    if (positive_words[0].size() <= cols) {
        // CHECK IF THERE IS AN EMPTY SPOT TO TAKE
        if (curr_board.getChar(r_index, c_index) == '*') {
            // SETTING THE CHARACTER, ERASING THE CHARACTER FROM THE STRING IN POSITIVE WORDS AND RECURSIVELY GOING TO THE NEXT SPOT
            curr_board.setChar(r_index, c_index, positive_words[0][0]);
            positive_words[0].erase(positive_words[0].begin());
            recurSearch(positive_words, negative_words, allboards, curr_board, r_index, c_index + 1);
        }
        // CHECKING IF THERE ARE NO MORE POSITIVE WORDS LEFT
        else if (positive_words[0].size() == 0) {
            // ERASE THE WORD
            positive_words.erase(positive_words.begin());
            // CHECK IF THE WORD WILL FIT IN THE SAME ROW AS THE PREVIOUS WORD
            if (positive_words[0].size() + c_index <= cols) {
                recurSearch(positive_words, negative_words, allboards, curr_board, r_index, c_index + 1);
            }
            // IF IT DOESNT FIT MOVE TO THE NEXT ROW
            else {
                c_index = 0;
                recurSearch(positive_words, negative_words, allboards, curr_board, r_index + 1, c_index);
            }
        }
        // IF THE NEW LETTER MATCHES THE LAST LETTER OF THE PREVIOUS WORD ERASE THE LETTER FROM THE POSITIVE WORD STRING
        else if (curr_board.getChar(r_index, c_index) == positive_words[0][0] && curr_board.getChar(r_index, c_index) != '*') {
            positive_words[0].erase(positive_words[0].begin());

        }
    }
    return;
}

int main(int argc, char*argv[]) {
    // INTIALIZING READING/WRITING FILES
    std::ifstream puzzlefile(argv[1]);
    std::ofstream outfile(argv[2]);
    
    // COMMAND LINE ARGUEMENTS ERROR CHECKING
    if (!puzzlefile.good()) {
        std::cerr << "Bad inputted puzzle file" << std::endl;
	}
    if (!outfile.good()) {
        std::cerr << "Bad output file" << std::endl;
	}
    if (argc != 4) {
        std::cerr << "incorrect number of arguments" << std::endl;
    }

    unsigned int b_row, b_col;
    std::vector <std::string> positive_words;
    std::vector <std::string> negative_words;
    parsing(puzzlefile, positive_words, negative_words, b_row, b_col);

    std::vector <Board> allboards;
    Board curr_board(b_row, b_col);
    unsigned int r_index = 0, c_index = 0;

    // RUNNING ALL SOLUTIONS OR ONE SOLUTION BASED ON USER INPUT
    if ((std::string)argv[3] == "all_solutions") {
        recurSearch(positive_words, negative_words, allboards, curr_board, r_index, c_index);
        for (unsigned int i = 0; i < allboards.size(); i++) {
            allboards[i].printBoard(outfile);
        }
    }
    else if ((std::string)argv[3] == "one_solution") {
        recurSearch(positive_words, negative_words, allboards, curr_board, r_index, c_index);
        for (unsigned int i = 0; i < allboards.size(); i++) {
            allboards[i].printBoard(outfile);
        }
    }
    else {
        std::cerr << "Invalid type of solution requested. Please use one_solution or all_solutions" << std::endl;
    }
}
