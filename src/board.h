#include <string>
#include <unordered_map>
#ifndef board_h
#define board_h

namespace Board{

struct board
{
    int board[8][8];
    int player;
    std::unordered_map<char, bool> castles;
    
    int enpassantColumn;
    int enpassantRow;
};
Board::board parseFen(std::string& fen);

}    

#endif