#include "board.h"
#include"movegen.h"
#include <unordered_map>
#include <string>
#include <iostream>

std::unordered_map<char, int8_t> pieceIDs = {
    {'P', 1}, {'N', 2}, {'B', 3}, {'R', 4}, {'Q', 5}, {'K', 7}, {'p', -1}, {'n', -2}, {'b', -3}, {'r', -4},{'q', -5},{'k', -7},
};

std::unordered_map<char, bool> castles = {
    {'K', false},{'Q', false},{'q', false},{'k', false}
};

const std::unordered_map<char, int> boardAlphabet = {
    {'a', 0},{'b', 1},{'c', 2},{'d', 3},{'e', 4},{'f', 5},{'g', 6},{'h', 7},
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
Board::board Board::parseFen(std::string& fenPosition){
    std::unordered_map<char,int8_t>::const_iterator bv;
    Board::board board;
    for(int i = 0; i < 8; i++) for(int y = 0; y < 8;y++) board.board[i][y] = -1;

    int row = 0;
    int column = 0;
    // Base part for FEN
    int fIndex = -1;
    for(auto p: fenPosition){
        if(board.board[7][7] != -1) break;
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
            // parse int to board
            int x = static_cast<int>(p - '0');
            for (size_t i = 0; i < x; i++)
            {
                board.board[column][row] = 0;
                row++;
            }
            continue;
        }
        board.board[column][row] = bv->second;
        row++;
    }

    // parse items after board pos
    fIndex += 2;
    for(fIndex; fIndex < fenPosition.length(); fIndex++){
        if(fenPosition[fIndex] == ' ') continue;
        // which player
        if(fenPosition[fIndex] == 'w' ) board.player = 1;
        if(fenPosition[fIndex] == 'b' ) board.player = -1;
        if(castles.find(fenPosition[fIndex]) != castles.end()) castles[fenPosition[fIndex]] = true;
        if(fenPosition[fIndex] == 'w' || fenPosition[fIndex] == 'b' ||
        fenPosition[fIndex] == '-' || castles.find(fenPosition[fIndex]) != castles.end()) continue;
        // hello enpassant
        if(static_cast<int>(fenPosition[fIndex]) >= 81)
        {
            board.enpassantRow = boardAlphabet.at(fenPosition[fIndex]);
            board.enpassantColumn =  8 - static_cast<int>(fenPosition[fIndex + 1] - '0');
            fIndex++;
        }
    }
    return board;
}