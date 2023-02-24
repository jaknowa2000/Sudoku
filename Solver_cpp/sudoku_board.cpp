#include<iostream>
#include<vector>
#include<array>
#include<memory> //inteligentne wskazniki
#include <typeinfo> //pomocne

#include "sudoku_board.h"

Field::Field(){
    value = 0;
    isset = false;
    possible_values = {};
}

// zeby nie dawac public klasy skojarzone
// zrobic opisy 

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
    std::cout<<"---------------------------------------"<<"\n";
    int index_row, index_column = 0;
    for(auto& row : sudoku){
        index_row++;
        for(auto& item : row){
            if(index_column % 3 == 0)std::cout<<"|";
            if(item->isset == true) std::cout<<item->value<<" | ";
            else std::cout<<" X |";
            index_column++;
        }
        if(index_row % 3 == 0)std::cout<<"\n---------------------------------------";
        std::cout<<"\n";
    }
};

int main(){
    auto sudoku1 = std::make_shared<Sudoku>();
    sudoku1->show_sudoku();
    return 0;
}