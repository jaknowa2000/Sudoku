#include<iostream>
#include<vector>
#include<memory> //inteligentne wskazniki
#include <typeinfo> //pomocne

#include "sudoku_board.h"

Field::Field(){
    value = 0;
    isset = false;
    possible_values = {};
}

// zeby nie dawac public klasy skojarzone



SmallSquare::SmallSquare(){
    for(auto& row: small_square){
        for(auto& item : row){
            item = std::make_shared<Field>();
        }
    }
};


RowOrColumn::RowOrColumn(){
    for(auto& item : row_or_column){
        item = std::make_shared<Field>();
        std::cout<<item->value;
    }
};

int main(){
    auto sml1 = std::make_shared<SmallSquare>();
    auto sml2 = std::make_shared<RowOrColumn>();
    return 0;
}