#ifndef sudoku_board_h
#define sudoku_board_h

#include <vector>


class Field{
    int value;
    bool isset;
    std::vector<int> possible_values;
    protected:
    Field();
};

#endif