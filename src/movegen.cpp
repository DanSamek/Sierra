#include<vector>
#include<iostream>
#include<unordered_map>

#include "movegen.h"
using namespace std;

#define BLACK -1
#define WHITE 1

bool isValidMove(int &column, int &row, int &player, int board[][8]);
bool isPieceCapture(int &column, int &row, int &player,int board[][8]);
vector<Movegen::Move> generateSlidingMoves(int &column, int &row, int &player, int board[][8], int value);
vector<Movegen::Move> generateKnightMoves(int &column, int &row, int &player, int board[][8]);
vector<Movegen::Move> generatePawnMoves(int &column, int &row, int &player, int board[][8], int &enPassantColumn, int &enPassantRow);

// how pieces moves
const unordered_map<int, vector<int>> pieceMoves = {
    {3, {1,1,-1,-1,1,-1,-1,1}},
    {4, {1,0,0,1,-1,0,0,-1}},
    {5, {1,1,-1,-1,1,-1,-1,1,1,0,0,1,-1,0,0,-1}},
};

// generate all moves for current player
vector<Movegen::Move> generateAllMoves(int board[8][8], int player){    
    vector<Movegen::Move> moves;
    vector<Movegen::Move> gm;
    for(int c = 0; c< 8;c++){
        for(int r = 0; r< 8;r++){
            // empty space, no piece here
            if(board[c][r] == 0) continue;

            if(board[c][r] == player * 1)
            {
                // pawns
            }
            if(board[c][r] == player * 2)
            {
                // knight
            }
            if(board[c][r] == player * 3)
            { 
                // bishop
                gm = Movegen::generateSlidingMoves(c,r,player, board, 3);
                moves.insert(moves.end(),gm.begin(),gm.end());
            }
            if(board[c][r] == player * 4)
            {
                // rook
                gm  = Movegen::generateSlidingMoves(c,r,player, board, 4);
                moves.insert(moves.end(),gm.begin(),gm.end());
            }
            if(board[c][r] == player * 5)
            {
                gm = Movegen::generateSlidingMoves(c,r,player, board, 5);
                moves.insert(moves.end(),gm.begin(),gm.end());
                gm = Movegen::generateSlidingMoves(c,r,player, board, 7);
                moves.insert(moves.end(),gm.begin(),gm.end());
            }
            if(board[c][r] ==  player * 7)
            {
                gm = Movegen::generateSlidingMoves(c,r,player, board, 7);
                moves.insert(moves.end(),gm.begin(),gm.end());
            }
        }
    }    
    /*
    for(auto m: moves){
        for (size_t c = 0; c < 8; c++){
            for (size_t r = 0; r < 8; r++){
                if(m.column == c && m.row == r) {
                    std::cout << "\033[1;31mX \033[0m";
                    continue;
                }
                std::cout << board[c][r] << " ";
        }   
        std::cout << "\n";
        }
    }
    */
    return moves;
}


bool isValidMove(int &column, int &row, int &player, int board[][8]){
    if(player == -1) return column < 8 && column >= 0 && row >= 0 && row < 8 && board[column][row] >= 0;
    if(player == 1) return  column < 8 && column >= 0 && row >= 0 && row < 8 && board[column][row] <= 0;
}

bool isPieceCapture(int &column, int &row, int &player, int board[][8]){
    if(player == -1) return board[column][row] > 0;
    if(player == 1) return board[column][row] < 0;
}

// for rook, queen, bishop and king
vector<Movegen::Move> generateSlidingMoves(int &column, int &row, int &player, int board[][8], int value){
    vector<Movegen::Move> moves;
    vector<int> ms;
    if(value == 7) ms = pieceMoves.at(5);
    else ms = pieceMoves.at(value);
    for(int i = 0; i < ms.size();i+=2){
        int currColumn = column + ms[i];
        int currRow = row + ms[i+1];
        while(isValidMove(currColumn, currRow, player, board)){
            Move m {currRow, currColumn, row, column};
            moves.push_back(m);
            // only first move from all sides for king
            if(value == 7) break;
            if(isPieceCapture(currColumn, currRow, player, board)) break;
            currColumn += ms[i];
            currRow += ms[i+1];
        }
    }
    return moves;
}

vector<Movegen::Move> generatePawnMoves(int &column, int &row, int &player, int board[][8], int &enPassantColumn, int &enPassantRow){
    vector<Movegen::Move> moves;

    return moves;
}

vector<Movegen::Move> generateKnightMoves(int &column, int &row, int &player, int board[][8]){
    vector<Movegen::Move> moves;

    return moves;
}
