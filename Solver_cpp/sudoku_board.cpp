#include<iostream>
#include<vector>
#include<memory> //inteligentne wskazniki
#include<typeinfo> //pomocne

#include "sudoku_board.h"

Field::Field(){
    value = 0;
    isset = false;
    possible_values = {};
}

//////////////////////////////////////
// TO DO LIST:
// zeby nie dawac public klasy skojarzone
// zrobic opisy 
// sprawdzic czy nie przekazuje w konstruktorach przez wartosc
// walidacja czy ma 81 elementow
//zrobic testy
//////////////////////////////////////

SmallSquare::SmallSquare(std::shared_ptr<Field> arr_of_fields[3][3]){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            small_square[i][j] = arr_of_fields[i][j];
        }
    }
};


RowOrColumn::RowOrColumn(std::shared_ptr<Field> arr_of_fields[9]){
    for(int i=0; i<9; i++){
        row_or_column[i] = arr_of_fields[i];
    }
};

Sudoku::Sudoku(){
    for(auto& row : sudoku){
        for(auto& item : row){
            item = std::make_shared<Field>();
        }
    }
    for(int i=0; i<9; i++){
        rows[i] = std::make_shared<RowOrColumn>(sudoku[i]);
        columns[i] = std::make_shared<RowOrColumn>(sudoku[i]);
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            std::shared_ptr<Field> temp[3][3];
            for(int k=0; k<3; k++){
                for(int l=0; l<3; l++){
                    temp[k][l] = sudoku[i*3+k][j*3+l];
                }
            }
            small_squares[i][j] = std::make_shared<SmallSquare>(temp);
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

/// @brief This method get from table the data of sudoku puzzle to solve.
/// @param sudoku_arr This table has to have 81 values, when value is 0 it meaans that
///the field in sudoku puzzle was empty.
void Sudoku::get_data_from_arr(int* sudoku_arr){
    int index_row = 0, index_column = 0;
    int field = 0;
    for(auto& row : sudoku){
        //std::cout<<"\n"<<index_row<<"\n";
        for(auto& item : row){
            field = sudoku_arr[index_row*9 + index_column];
            //field = sudoku_arr[1];
            if(field != 0){
                //std::cout<<index_column;
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
    int example_sudoku_tab[81] = {0,5,1,3,0,9,0,0,6,
                          0,2,0,8,7,1,3,4,5,
                          0,0,0,2,0,0,0,0,0,
                          2,1,9,7,6,4,0,3,0,
                          0,0,0,1,3,0,0,0,0,
                          7,3,0,0,0,8,0,6,2,
                          5,0,0,4,2,0,0,0,3,
                          0,0,0,9,1,5,0,0,7,
                          1,9,0,0,0,0,2,0,0};
    sudoku1->show_sudoku();
    sudoku1->get_data_from_arr(example_sudoku_tab);
    sudoku1->show_sudoku();
    return 0;
}