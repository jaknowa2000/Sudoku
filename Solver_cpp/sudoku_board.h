#ifndef sudoku_board_h
#define sudoku_board_h

#include <vector>
#include <memory>

class Field{
    public:
    int value;
    bool isset;
    std::vector<int> possible_values;
    Field();
};

class SmallSquare{
    public:
    std::shared_ptr<Field> small_square[3][3];
    SmallSquare(std::shared_ptr<Field> arr_of_fields[3][3]);
};

class RowOrColumn{
    public:
    std::shared_ptr<Field> row_or_column[9];
    RowOrColumn(std::shared_ptr<Field> arr_of_fields[9]);
};

class Sudoku{
    public:
    std::shared_ptr<Field> sudoku[9][9];
    std::shared_ptr<RowOrColumn> rows[9];
    std::shared_ptr<RowOrColumn> columns[9];
    std::shared_ptr<SmallSquare> small_squares[3][3];
    Sudoku();
    void show_sudoku();
};


#endif