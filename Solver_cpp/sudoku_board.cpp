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
class Sudoku{
    public:
    std::shared_ptr<Field> sudoku[9][9];
    std::shared_ptr<RowOrColumn> rows[9];
    std::shared_ptr<RowOrColumn> columns[9];
    std::shared_ptr<SmallSquare> small_squares[3][3];
    //std::shared_ptr<RowOrColumn> small = std::make_shared<RowOrColumn>(arr_of_fields);
    Sudoku();
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

int main(){
    //auto sml1 = std::make_shared<SmallSquare>();
    //auto sml2 = std::make_shared<RowOrColumn>();
    auto sml3 = std::make_shared<Sudoku>();
    /*int* tab[2][2] = {{1,2},{3,4}};
    int* tab2[2];
    std::copy(tab[1], tab[1]+1, tab2);
    std::cout<<tab2[0];
    tab2[0] = 11;
    std::cout<<tab2[0];
    std::cout<<tab[1][0];*/
    return 0;
}