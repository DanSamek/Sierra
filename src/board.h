#include <string>
#include <unordered_map>
#ifndef board_h
#define board_h

namespace Board{

class board
{
public:
    int* board;
    bool player;
    std::unordered_map<char, bool> castles;
    std::string enpassant;
};
void parseFen(std::string& fen);

}    

#endif