#ifndef sudoku_board_h
#define sudoku_board_h

#include<vector> //moze niepotrzebny
#include<set>
#include<memory>

class Field{
    public:
    int value;
    bool isset;
    std::set<int> possible_values;
    Field();
};

class SmallSquare{
    public:
    std::shared_ptr<Field> small_square[3][3];
    SmallSquare(std::shared_ptr<Field> arr_of_fields[3][3]);
    void solve_possibilities();
    private:
    void insert_value_if_one_digit_not_used(std::set<int> digits_not_used);
    void insert_possibilities_or_value(std::set<int> digits_not_used);
    void intersection_of_possibilities(std::shared_ptr<Field> item, std::set<int> digits_not_used);
    void insert_value_if_one_possibility(std::shared_ptr<Field> item, std::set<int> intersection_of_possibilities);
};

class RowOrColumn{
    public:
    std::shared_ptr<Field> row_or_column[9];
    RowOrColumn(std::shared_ptr<Field> arr_of_fields[9]);
    void solve_possibilities();
    private:
    void insert_value_if_one_digit_not_used(std::set<int> digits_not_used);
    void insert_possibilities_or_value(std::set<int> digits_not_used);
    void intersection_of_possibilities(std::shared_ptr<Field> item, std::set<int> digits_not_used);
    void insert_value_if_one_possibility(std::shared_ptr<Field> item, std::set<int> intersection_of_possibilities);
};

class Sudoku{
    public:
    std::shared_ptr<Field> sudoku[9][9];
    std::shared_ptr<RowOrColumn> rows[9];
    std::shared_ptr<RowOrColumn> columns[9];
    std::shared_ptr<SmallSquare> small_squares[3][3];
    Sudoku();
    void show_sudoku();
    void show_possibilities();
    void get_data_from_arr(int* sudoku_arr);
    bool is_solved();
    void solve_sudoku();
    void check_sudoku();
};


#endif