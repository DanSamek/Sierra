#include<vector>
#include<iostream>
#include<unordered_map>

#include "movegen.h"
#include "board.h"
using namespace std;

#define BLACK -1
#define WHITE 1

bool isValidMove(int &column, int &row, int &player, int board[][8]);
bool isPieceCapture(int &column, int &row, int &player,int board[][8]);
bool isValidMovePawn(int &column, int &row, int &player, int board[][8]);
vector<Movegen::Move> generateSlidingMoves(int &column, int &row, int &player, int board[][8], int value);
vector<Movegen::Move> generatePawnMoves(int &column, int &row, int &player, int board[][8], int &enPassantColumn, int &enPassantRow);
vector<Movegen::Move> generateKingCastles(int player, std::unordered_map<char, bool> castles, int board[][8]);

// how pieces moves
const unordered_map<int, vector<int>> pieceMoves = {
    {1,{1,-1}},
    {2, {2,1,2,-1,1,2,1,-2,-1,2,-1,-2,-2,1,-2,-1} },
    {3, {1,1,-1,-1,1,-1,-1,1}},
    {4, {1,0,0,1,-1,0,0,-1}},
    {5, {1,1,-1,-1,1,-1,-1,1,1,0,0,1,-1,0,0,-1}}
};

const char castlesChars[] = {'Q','K'};

// generate all moves for current player
vector<Movegen::Move> generateAllMoves(Board::board &board, int player){
    vector<Movegen::Move> moves;
    vector<Movegen::Move> gm;
    for(int c = 0; c< 8;c++){
        for(int r = 0; r< 8;r++){
            // empty space, no piece here
            if(board.board[c][r] == 0) continue;

            if(board.board[c][r] == player * 1)
            {
                gm = Movegen::generatePawnMoves(c,r,player, board.board, board.enpassantColumn, board.enpassantRow);
                moves.insert(moves.end(),gm.begin(),gm.end());   
            }
            if(board.board[c][r] == player * 2)
            {
                // knight
                gm = Movegen::generateSlidingMoves(c,r,player, board.board, 2);
                moves.insert(moves.end(),gm.begin(),gm.end());
            }
            if(board.board[c][r] == player * 3)
            { 
                // bishop
                gm = Movegen::generateSlidingMoves(c,r,player, board.board, 3);
                moves.insert(moves.end(),gm.begin(),gm.end());
            }
            if(board.board[c][r] == player * 4)
            {
                // rook
                gm  = Movegen::generateSlidingMoves(c,r,player, board.board, 4);
                moves.insert(moves.end(),gm.begin(),gm.end());
            }
            if(board.board[c][r] == player * 5)
            {
                gm = Movegen::generateSlidingMoves(c,r,player, board.board, 5);
                moves.insert(moves.end(),gm.begin(),gm.end());
                gm = Movegen::generateSlidingMoves(c,r,player, board.board, 7);
                moves.insert(moves.end(),gm.begin(),gm.end());
            }
            if(board.board[c][r] ==  player * 7)
            {
                gm = Movegen::generateSlidingMoves(c,r,player, board.board, 7);
                moves.insert(moves.end(),gm.begin(),gm.end());
            }
        }
    }    
    
    bool mb = false;
    for (size_t c = 0; c < 8; c++){
        for (size_t r = 0; r < 8; r++){
            for(auto m: moves){
                if(m.column == c && m.row == r) {
                    std::cout << "\033[1;31mX \033[0m";
                    mb = true;
                    break;
                }
            }
            if(!mb) std::cout << board.board[c][r] << " ";
            mb = false;
        }
        std::cout << "\n";
    }   
    
    return moves;
}

bool isValidMove(int &column, int &row, int &player, int board[][8]){
    if(player == -1) return column < 8 && column >= 0 && row >= 0 && row < 8 && board[column][row] >= 0;
    if(player == 1) return  column < 8 && column >= 0 && row >= 0 && row < 8 && board[column][row] <= 0;
}

bool isValidMovePawn(int &column, int &row, int &player, int board[][8]){
    return column < 8 && column >= 0 && row >= 0 && row < 8 && board[column][row] == 0;
}

bool isPieceCapture(int &column, int &row, int &player, int board[][8]){
    if(player == -1) return board[column][row] > 0;
    if(player == 1) return board[column][row] < 0;
}

// for rook, queen, bishop, knight and king
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
            if(value == 7 || value == 2 ) break;
            if(isPieceCapture(currColumn, currRow, player, board)) break;
            currColumn += ms[i];
            currRow += ms[i+1];
        }
    }
    return moves;
}

vector<Movegen::Move> generatePawnMoves(int &column, int &row, int &player, int board[][8], int &enPassantColumn, int &enPassantRow){
    vector<Movegen::Move> moves;
    // check normal moves
    int currRow;
    int currColumn;
    for(int i = 1; i < 3;i++){
        currColumn = column - (player * i);
        if(!isValidMovePawn(currColumn, row, player, board)) break;
        Move m {row, currColumn, row, column };
        moves.push_back(m);
        // only first move double 
        if((player == 1 && column != 6 ) || (player == -1 && column != 1 )) break;
    }    

    // check captures + en-passant
    vector<int> ms;
    ms = pieceMoves.at(1);
    for(auto mss: ms){
        currColumn = column - player;
        currRow = row + mss;
        if(!isPieceCapture(currColumn, currRow, player, board) && (currColumn != enPassantColumn || currRow != enPassantRow)) continue;
        Move m {currRow, currColumn, row, column };
        moves.push_back(m);
    }
    return moves;
}


vector<Movegen::Move> generateKingCastles(int player, std::unordered_map<char, bool> castles, int board[][8]){
    // -1 -> lowercase
    // 1 -> uppercase (default)
    for(auto c: castlesChars){
        // not in FEN
        if(!castles.at(player == 1 ? c : tolower(c))) continue;

        // Oh can i do it, are any pieces in that way to rook(?)
        // todo

    }
}