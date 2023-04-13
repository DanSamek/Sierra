#include<vector>

#ifndef Movegen
#define Movegen
using namespace std;

namespace Movegen{

    struct Move
    {
        int row;
        int column;
        int prevRow;
        int prevColumn;
    };
    static vector<Movegen::Move> generateAllMoves(int board[8][8], int player);
    static vector<Movegen::Move> generateSlidingMoves(int &column, int &row, int &player, int board[][8], int value);
    static vector<Movegen::Move> generatePawnMoves(int &column, int &row, int &player, int board[][8], int &enPassantColumn, int &enPassantRow);
}

#endif