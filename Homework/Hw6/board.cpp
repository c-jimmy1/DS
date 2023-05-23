#include <iostream>
#include <vector>

#include "board.h"


// CONSTRUCTORS 
Board::Board(unsigned int row_num, unsigned int col_num) {
    row = row_num;
    col = col_num;
    std::vector <std::vector <char>> temp_vec(row_num, std::vector<char>(col_num, '*'));
    board = temp_vec;
}

// ACCESSORS
unsigned int Board::getRow() const {
    return row;
}
unsigned int Board::getCol() const {
    return col;
}
char Board::getChar(unsigned int input_row, unsigned int input_col) const {
    return board[input_row][input_col];
}

void Board::printBoard(std::ostream& outfile) const {
    outfile << "Board:" << std::endl;
    for (unsigned int i = 0; i < board.size(); i++) {
        outfile << "  ";
        for (unsigned int j = 0; j < board[0].size(); j++) {
            outfile << board[i][j];
        }
        outfile << "\n";
    }
}

// MODIFIERS
void Board::setChar(unsigned int row_num, unsigned int col_num, char letter) {
    board[row_num][col_num] = letter;
}