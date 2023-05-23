#ifndef __board_h__
#define __board_h__

class Board {
    public:
    // CONSTRUCTORS
    Board(unsigned int row_num, unsigned int col_num);

    // ACCESSORS
    unsigned int getRow() const;
    unsigned int getCol() const;
    char getChar(unsigned int input_row, unsigned int input_col) const;
    void printBoard(std::ostream& outfile) const;


    // MODIFIERS
    void setChar(unsigned int row_num, unsigned int col_num, char letter);
    private: // REPRESENTATION
    unsigned int row;
    unsigned int col;
    std::vector <std::vector <char>> board;
};

#endif