#ifndef sudoku_board_h
#define sudoku_board_h

#include <vector>
#include <memory>

class Field{
    public:
    int value;
    bool isset;
    std::vector<int> possible_values;
    // protected: rather not
    Field();
};

class SmallSquare{
    //tu utworzyc
    public:
    std::shared_ptr<Field> small_square[3][3];
    SmallSquare(std::shared_ptr<Field> arr_of_fields[3][3]);
};

class RowOrColumn{
    public:
    std::shared_ptr<Field> row_or_column[9];
    RowOrColumn(std::shared_ptr<Field> arr_of_fields[9]);
};

#endif