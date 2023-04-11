#include<vector>

#ifndef Movegen
#define Movegen
using namespace std;

namespace Movegen{

    struct Move
    {
        int row;
        int column;
        int piece;
    };
    static vector<Movegen::Move> generateAllMoves(int board[8][8], int player);
    /*
    std::vector<Move> generatePawnMoves(int column, int row, int color);
    std::vector<Move> generateKnightMoves(int column, int row, int color);
    std::vector<Move> generateRookMoves(int column, int row, int color);    
    std::vector<Move> generateQueenMoves(int column, int row, int color);
    std::vector<Move> generateKingMoves(int column, int row, int color);
    */
}

#endif