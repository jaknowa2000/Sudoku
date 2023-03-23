#ifndef sudoku_board_h
#define sudoku_board_h

#include<vector> //moze niepotrzebny
#include<set>
#include<array>
#include<memory>
#include<unordered_set>

extern "C"{

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
    void insert_value_if_one_digit_not_used(std::set<int>& digits_not_used);
    void insert_possibilities_or_value(std::set<int>& digits_not_used);
    void intersection_of_possibilities(std::shared_ptr<Field> item, std::set<int>& digits_not_used);
    void insert_value_if_one_possibility(std::shared_ptr<Field> item, std::set<int>& intersection_of_possibilities);
};

class RowOrColumn{
    public:
    std::shared_ptr<Field> row_or_column[9];
    RowOrColumn(std::shared_ptr<Field> arr_of_fields[9]);
    void solve_possibilities();
    private:
    void insert_value_if_one_digit_not_used(std::set<int>& digits_not_used);
    void insert_possibilities_or_value(std::set<int>& digits_not_used);
    void intersection_of_possibilities(std::shared_ptr<Field> item, std::set<int>& digits_not_used);
    void insert_value_if_one_possibility(std::shared_ptr<Field> item, std::set<int>& intersection_of_possibilities);
};

class Sudoku{
    public: //moze private
    std::shared_ptr<Field> sudoku[9][9];
    std::shared_ptr<RowOrColumn> rows[9];
    std::shared_ptr<RowOrColumn> columns[9];
    std::shared_ptr<SmallSquare> small_squares[3][3];
    void show_possibilities();
    bool is_solved();
    void check_tab_size(int* sudoku_tab); //zastanowic sie nad typem
    void check_small_squares(std::unordered_set<int>& reference_digits, std::unordered_set<int>& digits_used);
    void check_rows_or_columns(std::unordered_set<int>& reference_digits, std::unordered_set<int>& digits_used, std::shared_ptr<RowOrColumn> (&rows_or_columns)[9]);
    public:
    Sudoku();
    void show_sudoku();
    void get_data_from_arr(std::array<int, 81>& sudoku_tab);
    void solve_sudoku();
    void check_sudoku();
    std::array<int, 81> return_solved_sudoku();
};

std::array<int, 81> fun_solve_sudoku(std::array<int, 81>& sudoku_board_values);

int dudu();
}

#endif