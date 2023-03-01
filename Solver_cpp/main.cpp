#include<iostream>

#include "sudoku_board.h"

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
    sudoku1->get_data_from_arr(example_sudoku_tab);
    sudoku1->show_sudoku();
    sudoku1->solve_sudoku();
    sudoku1->show_sudoku();
    sudoku1->check_sudoku();
    return 0;
}