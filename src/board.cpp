#include "board.h"
#include <unordered_map>
#include <string>
#include <iostream>

std::unordered_map<char, uint8_t> pieceIDs = {
    {'P', 1}, {'N', 2}, {'B', 3}, {'R', 4}, {'Q', 5}, {'K', 7}, {'p', 17}, {'n', 18}, {'b', 19}, {'r', 20},{'q', 21},{'k', 23},
};

std::unordered_map<char, bool> castles = {
    {'K', false},{'Q', false},{'q', false},{'k', false}
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
    for(int i = 0; i < 8; i++) for(int y = 0; y < 8;y++) b[i][y] = -1;

    int row = 0;
    int column = 0;
    // Base part for FEN
    int fIndex = -1;
    for(auto p: fenPosition){
        // try find value in map
        bv = pieceIDs.find(p);
        fIndex++;
        // not succ
        if(bv == pieceIDs.end()){
            if(p == '/'){
                column++;
                row = 0;
                continue;
            } 
            else{
                int x = static_cast<int>(p - '0');
                for (size_t i = 0; i < x; i++)
                {
                    b[column][row] = 0;
                    row++;
                }
                continue;
            }
            row++;
            continue;
        }
        b[column][row] = bv->second;
        row++;
        if(b[7][7] != -1) break;
    }

    // parse items after board pos
    fIndex += 2;
    for(fIndex; fIndex < fenPosition.length(); fIndex++){
        if(fenPosition[fIndex] == ' ') continue;
        if(fenPosition[fIndex] == 'w' ) board.player = true;
        if(fenPosition[fIndex] == 'b' ) board.player = false;
        if(castles.find(fenPosition[fIndex]) != castles.end()) castles[fenPosition[fIndex]] = true;
        if(fenPosition[fIndex] == 'w' || fenPosition[fIndex] == 'b' ||
        fenPosition[fIndex] == '-' || castles.find(fenPosition[fIndex]) != castles.end()) continue;
        // hello enpassant
        if(static_cast<int>(fenPosition[fIndex]) >= 81)
        {
            board.enpassant += fenPosition[fIndex];
            board.enpassant += fenPosition[++fIndex];
            fIndex++;
        }
    }
    // just for test    
    for (size_t i = 0; i < 8; i++){
        for (size_t x = 0; x < 8; x++){
            std::cout << b[i][x] << " ";
        }   
        std::cout << "\n";
    }
    
}