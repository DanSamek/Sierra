#include<vector>
#include<iostream>

#include "movegen.h"
using namespace std;

#define BLACK -1
#define WHITE 1

bool isValidMove(int &column, int &row, int &player, int board[][8]);
bool isPieceCapture(int &column, int &row, int &player,int board[][8]);
vector<Movegen::Move> generateBishopMoves(int &column, int &row, int &player, int board[][8]);

vector<Movegen::Move> generateAllMoves(int board[8][8], int player){
    vector<Movegen::Move> moves;
    vector<Movegen::Move> gm;
    for(int i = 0; i< 8;i++){
        for(int y = 0; y< 8;y++){
            if(board[i][y] == 0) continue;
            // generate moves
            if(board[i][y] == player * 1)
            {
                // pawns
            }
            if(board[i][y] == player * 2)
            {
                // knight
            }
            // bishop
            if(board[i][y] == player * 3)
            { 
                gm = generateBishopMoves(y, i, player,board);
                moves.insert(moves.end(),begin(gm),end(gm));
            }
            if(board[i][y] == player * 4)
            {
                // rook
            }
            if(board[i][y] == player * 5)
            {
                // Queen
            }
            if(board[i][y] ==  player * 7)
            {
                // King
            }
        }
    }    
    for(auto m: moves){
        for (size_t i = 0; i < 8; i++){
            for (size_t x = 0; x < 8; x++){
                if(m.column == i && m.row == x) {
                    std::cout << "B ";
                    continue;
                }
                std::cout << board[i][x] << " ";
        }   
        std::cout << "\n";
    }
    }
    return moves;
}


bool isValidMove(int &column, int &row, int &player, int board[][8]){
    // captures also
    if(player == -1) return column < 8 && column >= 0 && row >= 0 && row < 8 && board[column][row] >= 0;
    // captures also
    if(player == 1) return  column < 8 && column >= 0 && row >= 0 && row < 8 && board[column][row] <= 0;
}

bool isPieceCapture(int &column, int &row, int &player,int board[][8]){
    if(player == -1) return board[column][row] > 0;
    if(player == 1) return board[column][row] < 0;
}

vector<Movegen::Move> generateBishopMoves(int &column, int &row, int &player, int board[][8]){
    vector<Movegen::Move> moves;
    int dx[] = {1, -1, 1, -1};
    int dy[] = {1, -1, -1, 1};
    for(int i = 0; i < 4;i++){
        int cx = column + dx[i];
        int cy = row + dy[i];
        while(isValidMove(cx, cy, player, board)){
            Move m {cx, cy, player * 3};
            moves.push_back(m);
            if(isPieceCapture(cx, cy, player, board)) break;
            cx += dx[i];
            cy += dy[i];
        }
    }
    return moves;
}
