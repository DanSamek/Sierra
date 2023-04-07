#include "board.h"
#include <unordered_map>
#include <string>
#include <iostream>

std::unordered_map<char, uint8_t> boardValues = {
    // white uppercase, black lowercase
    {'P', 1},
    {'N', 2},
    {'B', 3},
    {'R', 4},
    {'Q', 5},
    {'K', 7},
    {'p', 17},
    {'n', 18},
    {'b', 19},
    {'r', 20},
    {'q', 21},
    {'k', 23},
};

/*
    a b c d e f g h 
 8  0 1 2 3 4 5 6 7
 7  1
 6  2
 5  3
 4  4
 3  5
 2  6
 1  7
*/

void Board::parseFen(std::string& fenPosition){
    std::unordered_map<char,uint8_t>::const_iterator bv;
    Board::board board;
    int b[8][8];
    int row = 0;
    int column = 0;
    for(auto p: fenPosition){
        // try find value in map
        bv = boardValues.find(p);
        // not succ
        if(bv == boardValues.end()){
            if(p == '/'){
                column++;
                row = 0;
                continue;
            } 
            else if(p == '-') board.enPassand = false;
            else{
                int x = static_cast<int>(p);
                for (size_t i = 0; i < x; i++)
                {
                    b[column][row] = 0;
                    row++;
                }
            }
            row++;
            continue;
        }
        b[column][row] = bv->second;
        row++;
    }
    // just for test
    for (size_t i = 0; i < 8; i++){
        for (size_t x = 0; x < 8; x++){
            std::cout << b[i][x] << " ";
        }   
        std::cout << "\n";
    }
}
