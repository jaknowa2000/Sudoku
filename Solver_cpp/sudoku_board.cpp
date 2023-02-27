#include<iostream>
#include<vector>
#include<set>
#include<unordered_set>
#include<memory> //inteligentne wskazniki
#include<typeinfo> //pomocne
#include<algorithm>
//#include<ranges>
//#include<iterator>

#include "sudoku_board.h"


class InvalidSolution : public std::exception {
    public:
char const * what () {
        return "The algorithm calculated wrong solution";
    }
};

Field::Field(){
    value = 0;
    isset = false;
    possible_values = {};
}

//////////////////////////////////////
// TO DO LIST:
// zeby nie dawac public klasy skojarzone //jutro!!
// zrobic opisy ?(na pewno rozbic na mniejsze!)
// walidacja czy ma 81 elementow
// zrobic testy
// test czy insert dziala
// zrobic cmake //jutro!!
// sprawdzic metode przejscia
//////////////////////////////////////

SmallSquare::SmallSquare(std::shared_ptr<Field> arr_of_fields[3][3]){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            small_square[i][j] = arr_of_fields[i][j];
        }
    }
};

void SmallSquare::solve_possibilities(){
    std::set<int> digits_not_used = {1,2,3,4,5,6,7,8,9};
    for(auto& row : small_square){
        for(auto& item : row){
            if(item->isset) digits_not_used.erase(item->value);
        }
    }
    if(digits_not_used.size() == 1) {
        insert_value_if_one_digit_not_used(digits_not_used);
        return;
    }
    insert_possibilities_or_value(digits_not_used);
};

void SmallSquare::insert_value_if_one_digit_not_used(std::set<int>& digit_not_used){
    for(auto& row : small_square){
        for(auto& item : row){
            if(!(item->isset)){
                item->value = *digit_not_used.begin();
                item->isset = true;
                return;
            }
        }
    }
};

void SmallSquare::insert_possibilities_or_value(std::set<int>& digits_not_used){
    for(auto& row : small_square){
        for(auto& item : row){
            if(!(item->isset)){
                if(item->possible_values.size() == 0) item->possible_values = digits_not_used;
                else intersection_of_possibilities(item, digits_not_used);
            }
        }
    }
};

void SmallSquare::intersection_of_possibilities(std::shared_ptr<Field> item, std::set<int>& digits_not_used){
    std::set<int> intersection_of_possibilities = {};
    std::set_intersection(item->possible_values.begin(), item->possible_values.end(), digits_not_used.begin(), digits_not_used.end(), std::inserter(intersection_of_possibilities, intersection_of_possibilities.begin()));
    if(intersection_of_possibilities.size() == 1) insert_value_if_one_possibility(item, intersection_of_possibilities);
    else item->possible_values = intersection_of_possibilities;
};

void SmallSquare::insert_value_if_one_possibility(std::shared_ptr<Field> item, std::set<int>& intersection_of_possibilities){
    item->value = *intersection_of_possibilities.begin();
    item->isset = true;
};

RowOrColumn::RowOrColumn(std::shared_ptr<Field> arr_of_fields[9]){
    for(int i=0; i<9; i++){
        row_or_column[i] = arr_of_fields[i];
    }
};

void RowOrColumn::solve_possibilities(){
    std::set<int> digits_not_used = {1,2,3,4,5,6,7,8,9};
    for(auto& item : row_or_column){
        if(item->isset) digits_not_used.erase(item->value);
    }
    if(digits_not_used.size() == 1) {
        insert_value_if_one_digit_not_used(digits_not_used);
        return;
    }
    insert_possibilities_or_value(digits_not_used);
};

void RowOrColumn::insert_value_if_one_digit_not_used(std::set<int>& digit_not_used){
    for(auto& item : row_or_column){
        if(!(item->isset)){
            item->value = *digit_not_used.begin();
            item->isset = true;
            return;
        }
    }
};

void RowOrColumn::insert_possibilities_or_value(std::set<int>& digits_not_used){
    for(auto& item : row_or_column){
        if(!(item->isset)){
            if(item->possible_values.size() == 0) item->possible_values = digits_not_used;
            else intersection_of_possibilities(item, digits_not_used);
        }
    }
};

void RowOrColumn::intersection_of_possibilities(std::shared_ptr<Field> item, std::set<int>& digits_not_used){
    std::set<int> intersection_of_possibilities = {};
    std::set_intersection(item->possible_values.begin(), item->possible_values.end(), digits_not_used.begin(), digits_not_used.end(), std::inserter(intersection_of_possibilities, intersection_of_possibilities.begin()));
    if(intersection_of_possibilities.size() == 1) insert_value_if_one_possibility(item, intersection_of_possibilities);
    else item->possible_values = intersection_of_possibilities;
};

void RowOrColumn::insert_value_if_one_possibility(std::shared_ptr<Field> item, std::set<int>& intersection_of_possibilities){
    item->value = *intersection_of_possibilities.begin();
    item->isset = true;
};


Sudoku::Sudoku(){
    for(auto& row : sudoku){
        for(auto& item : row){
            item = std::make_shared<Field>();
        }
    }
    for(int i=0; i<9; i++){
        rows[i] = std::make_shared<RowOrColumn>(sudoku[i]);
        std::shared_ptr<Field> temp_column[9];
        for(int j=0; j<9; j++){
            temp_column[j] = sudoku[j][i];
        }
        columns[i] = std::make_shared<RowOrColumn>(temp_column);
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            std::shared_ptr<Field> temp_small_square[3][3];
            for(int k=0; k<3; k++){
                for(int l=0; l<3; l++){
                    temp_small_square[k][l] = sudoku[i*3+k][j*3+l];
                }
            }
            small_squares[i][j] = std::make_shared<SmallSquare>(temp_small_square);
        }
    }
};

void Sudoku::show_sudoku(){
    std::cout<<"             SUDOKU BOARD\n";
    std::cout<<"---------------------------------------"<<"\n";
    int index_row = 0, index_column = 0;
    for(auto& row : sudoku){
        index_row++;
        for(auto& item : row){
            if(index_column % 3 == 0)std::cout<<"|";
            if(item->isset == true) std::cout<<" "<<item->value<<" |";
            else std::cout<<"   |";
            index_column++;
        }
        if(index_row % 3 == 0)std::cout<<"\n---------------------------------------";
        std::cout<<"\n";
    }
    std::cout<<"\n";
};

void Sudoku::show_possibilities(){
    std::cout<<"             SUDOKU POSSIBILITIES\n";
    std::cout<<"----------------------------------------------------------------------------------------------"<<"\n";
    int index_row = 0, index_column = 0;
    for(auto& row : sudoku){
        index_row++;
        for(auto& item : row){
            if(index_column % 3 == 0)std::cout<<"| ";
            if(item->isset == false){
                if(item->possible_values.size() == 0) std::cout<<" {} |";
                else{
                    std::cout<<"{";
                    for(auto& val : item->possible_values){
                        std::cout<<val<<" ";
                    }
                    std::cout<<"} |";
                }
            }
            else std::cout<<" X |";
            index_column++;
        }
        if(index_row % 3 == 0)std::cout<<"\n----------------------------------------------------------------------------------------------";
        std::cout<<"\n";
    }
    std::cout<<"\n";
};

bool Sudoku::is_solved(){
    for(auto& row : sudoku){
        for(auto& item : row){
            if(item->isset == false) return false;
        }
    }
    return true;
};

void Sudoku::solve_sudoku(){
    while(!(is_solved())){
        for(auto& row : small_squares){
            for(auto& small_square : row){
                small_square->solve_possibilities();
            }
        }
        //show_possibilities();
        for(auto& row : rows){
            row->solve_possibilities();
        }
        //show_possibilities();
        for(auto& column : columns){
            column->solve_possibilities();
        }//show_possibilities();
        //show_sudoku();
        //show_possibilities();
    }
};

void Sudoku::check_sudoku(){
    std::unordered_set<int> reference_digits = {1,2,3,4,5,6,7,8,9};
    std::unordered_set<int> digits_used = {};
    for(auto& row : small_squares){
        for(auto& small_square : row){
            for(auto& row_small_square : small_square.get()->small_square){
                for(auto& item : row_small_square){
                    digits_used.insert(item->value);
                }
            }
            if(!(digits_used == reference_digits)) throw InvalidSolution();
            digits_used.clear();
        }
    }
    for(auto& row : rows){
        for(auto& item : row.get()->row_or_column){
            digits_used.insert(item->value);
        }
        if(!(digits_used == reference_digits)) throw InvalidSolution();
        digits_used.clear();
    }
    for(auto& row : columns){
        for(auto& item : row.get()->row_or_column){
            digits_used.insert(item->value);
        }
        if(!(digits_used == reference_digits)) throw InvalidSolution();
        digits_used.clear();
    }
};

/// @brief This method get from table the data of sudoku puzzle to solve.
/// @param sudoku_arr This table has to have 81 values, when value is 0 it meaans that
///the field in sudoku puzzle was empty.
void Sudoku::get_data_from_arr(int* sudoku_arr){
    int index_row = 0, index_column = 0;
    int field = 0;
    for(auto& row : sudoku){
        for(auto& item : row){
            field = sudoku_arr[index_row*9 + index_column];
            if(field != 0){
                item->value = field;
                item->isset = true; 
            }
            index_column++;
        }
        index_column = 0;
        index_row++;
    }
};

int main(){
    auto sudoku1 = std::make_shared<Sudoku>();
    int start_example_sudoku_tab[81] = {5,0,3,9,0,0,0,7,0,
                                        8,0,2,6,1,0,5,0,9,
                                        6,0,0,0,5,7,8,0,1,
                                        0,2,6,0,7,0,4,1,5,
                                        0,5,0,0,2,0,7,0,3,
                                        3,0,7,0,6,0,0,0,8,
                                        0,0,0,7,0,0,0,9,0,
                                        0,6,9,0,0,2,0,5,7,
                                        0,0,5,0,0,6,0,0,4};
    int example_sudoku_tab[81] = {0,0,3,5,6,8,0,0,0,
                                  0,0,7,3,0,0,0,1,0,
                                  0,0,0,0,9,7,0,0,6,
                                  4,7,0,0,0,5,2,0,0,
                                  1,0,0,0,0,0,8,0,5,
                                  0,0,0,0,0,0,4,0,7,
                                  0,2,0,0,0,0,0,4,3,
                                  0,4,0,9,2,6,1,0,0,
                                  8,9,0,0,0,3,0,0,0};
    sudoku1->show_sudoku();
    //sudoku1->show_possibilities();
    sudoku1->get_data_from_arr(example_sudoku_tab);
    sudoku1->show_sudoku();
    sudoku1->solve_sudoku();
    sudoku1->show_sudoku();
    sudoku1->check_sudoku();
    return 0;
}